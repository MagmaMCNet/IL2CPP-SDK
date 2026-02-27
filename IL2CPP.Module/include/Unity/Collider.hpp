#pragma once
#include "Component.hpp"
#include <IL2CPP.Common/il2cpp_shared.hpp>

// ============================================================================
//  IL2CPP.Module::Unity::Collider
// ============================================================================

namespace IL2CPP::Module::Unity {

    class Rigidbody;  // Forward declaration

    class Collider : public Component {
    public:
        using Component::Component;

        [[nodiscard]] bool GetEnabled() const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->collider.m_GetEnabled || !raw()) return false;
            return reinterpret_cast<bool(IL2CPP_CALLTYPE)(void*)>(fn->collider.m_GetEnabled)(raw());
        }

        void SetEnabled(bool value) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->collider.m_SetEnabled || !raw()) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, bool)>(fn->collider.m_SetEnabled)(raw(), value);
        }

        [[nodiscard]] bool GetIsTrigger() const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->collider.m_GetIsTrigger || !raw()) return false;
            return reinterpret_cast<bool(IL2CPP_CALLTYPE)(void*)>(fn->collider.m_GetIsTrigger)(raw());
        }

        void SetIsTrigger(bool value) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->collider.m_SetIsTrigger || !raw()) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, bool)>(fn->collider.m_SetIsTrigger)(raw(), value);
        }

        [[nodiscard]] Rigidbody GetAttachedRigidbody() const;

        // ---- Legacy snake_case aliases (deprecated) ----
        [[deprecated("Use GetEnabled()")]] [[nodiscard]] bool get_enabled() const { return GetEnabled(); }
        [[deprecated("Use SetEnabled()")]] void set_enabled(bool v) { SetEnabled(v); }
        [[deprecated("Use GetIsTrigger()")]] [[nodiscard]] bool get_is_trigger() const { return GetIsTrigger(); }
        [[deprecated("Use SetIsTrigger()")]] void set_is_trigger(bool v) { SetIsTrigger(v); }
        [[deprecated("Use GetAttachedRigidbody()")]] [[nodiscard]] Rigidbody get_attached_rigidbody() const;
    };

} // namespace IL2CPP::Module::Unity
