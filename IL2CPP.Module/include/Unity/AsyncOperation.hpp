#pragma once
#include "Object.hpp"
#include "../Dispatcher.hpp"
#include "../System/Delegate.hpp"
#include <functional>
#include <memory>
#include <mutex>
#include <optional>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

namespace IL2CPP::Module::Unity {

    class AsyncOperation : public Object {
        template<typename Fn>
        struct CallbackState {
            Fn callback;
            std::shared_ptr<ManagedRoot> operationRoot;
        };

        using StatePtr = std::unique_ptr<void, void(*)(void*)>;

        struct Subscription {
            void* target = nullptr;
            std::shared_ptr<ManagedRoot> operationRoot;
            std::shared_ptr<ManagedRoot> actionRoot;
            StatePtr state{ nullptr, nullptr };
        };

        static std::unordered_map<void*, Subscription>& Subscriptions() {
            static std::unordered_map<void*, Subscription> subscriptions;
            return subscriptions;
        }

        static std::mutex& SubscriptionMutex() {
            static std::mutex mutex;
            return mutex;
        }

        static std::optional<Subscription> TakeSubscription(void* target) {
            std::lock_guard lock(SubscriptionMutex());
            auto& subscriptions = Subscriptions();
            auto it = subscriptions.find(target);
            if (it == subscriptions.end()) return std::nullopt;
            Subscription subscription = std::move(it->second);
            subscriptions.erase(it);
            return subscription;
        }

        template<typename Fn>
        static void InvokeCallback(Fn& callback, AsyncOperation operation) {
            if constexpr (std::is_invocable_v<Fn&, AsyncOperation>) {
                std::invoke(callback, operation);
            } else if constexpr (std::is_invocable_v<Fn&, void*>) {
                std::invoke(callback, operation.raw());
            } else {
                std::invoke(callback);
            }
        }

        template<typename Fn>
        static void __fastcall CompletionThunk(void* target, void* operation, void*) noexcept {
            auto subscription = TakeSubscription(target);
            if (!subscription || !subscription->state) return;
            auto* state = static_cast<CallbackState<Fn>*>(subscription->state.get());
            try {
                InvokeCallback(state->callback, AsyncOperation{ operation });
            } catch (...) {
            }
            (void)state->operationRoot->Reset();
        }

        static bool CancelAllOnMain() {
            std::vector<Subscription> subscriptions;
            {
                std::lock_guard lock(SubscriptionMutex());
                auto& active = Subscriptions();
                subscriptions.reserve(active.size());
                for (auto& [target, subscription] : active) {
                    (void)target;
                    subscriptions.push_back(std::move(subscription));
                }
                active.clear();
            }

            static auto remove = MethodHandler::resolve(
                IL2CPP_STR("UnityEngine.AsyncOperation"), IL2CPP_STR("remove_completed"), 1);
            bool success = true;
            for (auto& subscription : subscriptions) {
                void* operation = subscription.operationRoot->Get();
                void* action = subscription.actionRoot->Get();
                bool removed = false;
                if (remove && operation && action) {
                    void* parameters[] = { action };
                    void* exception = nullptr;
                    remove.invoke(operation, parameters, &exception);
                    removed = exception == nullptr;
                }
                if (removed) {
                    if (subscription.operationRoot) (void)subscription.operationRoot->Reset();
                } else {
                    void* target = subscription.target;
                    std::lock_guard lock(SubscriptionMutex());
                    Subscriptions().emplace(target, std::move(subscription));
                    success = false;
                }
            }
            return success;
        }

        template<typename Fn>
        [[nodiscard]] bool Subscribe(Fn&& fn, std::shared_ptr<ManagedRoot> operationRoot) const {
            static auto add = MethodHandler::resolve(
                IL2CPP_STR("UnityEngine.AsyncOperation"), IL2CPP_STR("add_completed"), 1);
            if (!add) return false;

            auto* exports = GetExports();
            static Class targetClass = Class::find(IL2CPP_STR("System.Object"));
            static Class delegateClass = add.get_param_type(0).get_class();
            if (!exports || !exports->m_objectNew || !targetClass || !delegateClass) return false;

            void* target = reinterpret_cast<void*(IL2CPP_CALLTYPE)(void*)>(
                exports->m_objectNew)(targetClass.raw());
            if (!target) return false;

            using Callback = std::decay_t<Fn>;
            StatePtr state{
                new CallbackState<Callback>{ std::forward<Fn>(fn), operationRoot },
                [](void* p) { delete static_cast<CallbackState<Callback>*>(p); }
            };

            System::Delegate action = System::Delegate::CreateNative(
                delegateClass, reinterpret_cast<void*>(&CompletionThunk<Callback>), target);
            if (!action) return false;

            auto actionRoot = std::make_shared<ManagedRoot>();
            if (!actionRoot->Reset(action.raw())) return false;
            {
                std::lock_guard lock(SubscriptionMutex());
                Subscriptions().emplace(target, Subscription{
                    target, operationRoot, std::move(actionRoot), std::move(state)
                });
            }

            void* parameters[] = { action.raw() };
            void* exception = nullptr;
            add.invoke(raw(), parameters, &exception);
            if (exception) {
                TakeSubscription(target);
                return false;
            }
            return true;
        }

    public:
        using Object::Object;

        [[nodiscard]] bool GetIsDone() const {
            static auto method = MethodHandler::resolve(
                IL2CPP_STR("UnityEngine.AsyncOperation"), IL2CPP_STR("get_isDone"), 0);
            return MethodHandler::invoke<bool>(method, raw());
        }

        [[nodiscard]] float GetProgress() const {
            static auto method = MethodHandler::resolve(
                IL2CPP_STR("UnityEngine.AsyncOperation"), IL2CPP_STR("get_progress"), 0);
            return MethodHandler::invoke<float>(method, raw());
        }

        template<typename Fn>
        [[nodiscard]] bool OnCompleted(Fn&& fn) const {
            if (!raw()) return false;

            auto operationRoot = std::make_shared<ManagedRoot>();
            if (!operationRoot->Reset(raw())) return false;

            using Callback = std::decay_t<Fn>;
            if (Dispatcher::IsMainThread()) {
                return Subscribe(Callback(std::forward<Fn>(fn)), std::move(operationRoot));
            }

            auto callback = std::make_shared<Callback>(std::forward<Fn>(fn));
            auto failed = [operationRoot, callback] {
                try {
                    InvokeCallback(*callback, AsyncOperation{});
                } catch (...) {
                }
                (void)operationRoot->Reset();
            };
            bool accepted = Dispatcher::RunOnMain(
                [operationRoot, callback, failed] {
                    void* operation = operationRoot->Get();
                    bool subscribed = operation && AsyncOperation{ operation }.Subscribe(
                        [callback](AsyncOperation completed) {
                            InvokeCallback(*callback, completed);
                        }, operationRoot);
                    if (!subscribed) failed();
                }, failed);
            if (!accepted) {
                try {
                    InvokeCallback(*callback, AsyncOperation{});
                } catch (...) {
                }
                (void)operationRoot->Reset();
            }
            return accepted;
        }

        /// <summary>Cancels every pending subscription. Never blocks: off the Unity main
        /// thread the cancellation is queued and this returns as soon as it is accepted.</summary>
        /// <returns>True if all subscriptions were cancelled, or the cancellation was queued.</returns>
        [[nodiscard]] static bool CancelAllSubscriptions() {
            if (Dispatcher::IsMainThread()) {
                return CancelAllOnMain();
            }
            return Dispatcher::RunOnMain([] { (void)CancelAllOnMain(); });
        }
    };

} // namespace IL2CPP::Module::Unity
