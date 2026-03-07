#pragma once
#include "Behaviour.hpp"
#include "../MethodHandler.hpp"
#include <IL2CPP.Common/il2cpp_shared.hpp>

// ============================================================================
//  IL2CPP.Module::Unity::MonoBehaviour
// ============================================================================

namespace IL2CPP::Module::Unity {

    class MonoBehaviour : public Behaviour {
    public:
        using Behaviour::Behaviour;

        void Invoke(std::string_view methodName, float time) {
            static auto m = MethodHandler::resolve("UnityEngine.MonoBehaviour", "Invoke", 2);
            auto* exports = GetExports();
            if (!exports || !exports->m_stringNew) return;
            void* str = reinterpret_cast<void*(IL2CPP_CALLTYPE)(const char*)>(exports->m_stringNew)(
                std::string(methodName).c_str());
            void* params[] = { str, &time };
            MethodHandler::invoke(m, raw(), params);
        }

        void CancelInvoke() {
            static auto m = MethodHandler::resolve("UnityEngine.MonoBehaviour", "CancelInvoke", 0);
            MethodHandler::invoke(m, raw());
        }

        [[nodiscard]] bool IsInvoking() const {
            static auto m = MethodHandler::resolve("UnityEngine.MonoBehaviour", "IsInvoking", 0);
            return MethodHandler::invoke<bool>(m, raw());
        }

        /// Start a coroutine by method name.
        [[nodiscard]] ManagedObject StartCoroutine(std::string_view method) {
            static auto m = MethodHandler::resolve("UnityEngine.MonoBehaviour", "StartCoroutine", 1);
            auto* exports = GetExports();
            if (!exports || !exports->m_stringNew) return ManagedObject{};
            void* str = reinterpret_cast<void*(IL2CPP_CALLTYPE)(const char*)>(exports->m_stringNew)(
                std::string(method).c_str());
            void* params[] = { str };
            return ManagedObject{ MethodHandler::invoke<void*>(m, raw(), params) };
        }

        // ---- Legacy snake_case aliases (deprecated) ----
        [[deprecated("Use Invoke()")]] void invoke(std::string_view m, float t) { Invoke(m, t); }
        [[deprecated("Use CancelInvoke()")]] void cancel_invoke() { CancelInvoke(); }
        [[deprecated("Use IsInvoking()")]] [[nodiscard]] bool is_invoking() const { return IsInvoking(); }
        [[deprecated("Use StartCoroutine()")]] [[nodiscard]] ManagedObject start_coroutine(std::string_view m) { return StartCoroutine(m); }
    };

} // namespace IL2CPP::Module::Unity
