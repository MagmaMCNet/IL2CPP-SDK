#pragma once
#include "Component.hpp"
#include <IL2CPP.Common/il2cpp_shared.hpp>

// ============================================================================
//  IL2CPP.Module::Unity::Behaviour
// ============================================================================

namespace IL2CPP::Module::Unity {

    class Behaviour : public Component {
    public:
        using Component::Component;

        [[nodiscard]] bool GetEnabled() const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->behaviour.m_GetEnabled || !raw()) return false;
            return reinterpret_cast<bool(IL2CPP_CALLTYPE)(void*)>(fn->behaviour.m_GetEnabled)(raw());
        }

        void SetEnabled(bool value) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->behaviour.m_SetEnabled || !raw()) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, bool)>(fn->behaviour.m_SetEnabled)(raw(), value);
        }

        [[nodiscard]] bool GetIsActiveAndEnabled() const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->behaviour.m_GetIsActiveAndEnabled || !raw()) return false;
            return reinterpret_cast<bool(IL2CPP_CALLTYPE)(void*)>(fn->behaviour.m_GetIsActiveAndEnabled)(raw());
        }

        // ---- Legacy snake_case aliases (deprecated) ----
        [[deprecated("Use GetEnabled()")]] [[nodiscard]] bool get_enabled() const { return GetEnabled(); }
        [[deprecated("Use SetEnabled()")]] void set_enabled(bool v) { SetEnabled(v); }
        [[deprecated("Use GetIsActiveAndEnabled()")]] [[nodiscard]] bool get_is_active_and_enabled() const { return GetIsActiveAndEnabled(); }
    };

} // namespace IL2CPP::Module::Unity
