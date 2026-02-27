#pragma once
#include "Behaviour.hpp"
#include <IL2CPP.Common/il2cpp_shared.hpp>

// ============================================================================
//  IL2CPP.Module::Unity::MonoBehaviour
// ============================================================================

namespace IL2CPP::Module::Unity {

    class MonoBehaviour : public Behaviour {
    public:
        using Behaviour::Behaviour;

        void Invoke(std::string_view methodName, float time) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->monoBehaviour.m_Invoke || !raw()) return;
            auto* exports = GetExports();
            if (!exports || !exports->m_stringNew) return;
            void* str = reinterpret_cast<void*(IL2CPP_CALLTYPE)(const char*)>(exports->m_stringNew)(
                std::string(methodName).c_str());
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, void*, float)>(fn->monoBehaviour.m_Invoke)(raw(), str, time);
        }

        void CancelInvoke() {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->monoBehaviour.m_CancelInvoke || !raw()) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*)>(fn->monoBehaviour.m_CancelInvoke)(raw());
        }

        [[nodiscard]] bool IsInvoking() const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->monoBehaviour.m_IsInvoking || !raw()) return false;
            return reinterpret_cast<bool(IL2CPP_CALLTYPE)(void*)>(fn->monoBehaviour.m_IsInvoking)(raw());
        }

        /// Start a coroutine by method name.
        [[nodiscard]] ManagedObject StartCoroutine(std::string_view method) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->monoBehaviour.m_StartCoroutine || !raw()) return ManagedObject{};
            auto* exports = GetExports();
            if (!exports || !exports->m_stringNew) return ManagedObject{};
            void* str = reinterpret_cast<void*(IL2CPP_CALLTYPE)(const char*)>(exports->m_stringNew)(
                std::string(method).c_str());
            return ManagedObject{ reinterpret_cast<void*(IL2CPP_CALLTYPE)(void*, void*)>(fn->monoBehaviour.m_StartCoroutine)(raw(), str) };
        }

        // ---- Legacy snake_case aliases (deprecated) ----
        [[deprecated("Use Invoke()")]] void invoke(std::string_view m, float t) { Invoke(m, t); }
        [[deprecated("Use CancelInvoke()")]] void cancel_invoke() { CancelInvoke(); }
        [[deprecated("Use IsInvoking()")]] [[nodiscard]] bool is_invoking() const { return IsInvoking(); }
        [[deprecated("Use StartCoroutine()")]] [[nodiscard]] ManagedObject start_coroutine(std::string_view m) { return StartCoroutine(m); }
    };

} // namespace IL2CPP::Module::Unity
