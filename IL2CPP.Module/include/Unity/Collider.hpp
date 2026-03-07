#pragma once
#include "Component.hpp"
#include "../MethodHandler.hpp"

// ============================================================================
//  IL2CPP.Module::Unity::Collider
// ============================================================================

namespace IL2CPP::Module::Unity {

    class Rigidbody;  // Forward declaration

    class Collider : public Component {
    public:
        using Component::Component;

        [[nodiscard]] bool GetEnabled() const {
            static auto m = MethodHandler::resolve("UnityEngine.Collider", "get_enabled", 0);
            return MethodHandler::invoke<bool>(m, raw());
        }

        void SetEnabled(bool value) {
            static auto m = MethodHandler::resolve("UnityEngine.Collider", "set_enabled", 1);
            void* params[] = { &value };
            MethodHandler::invoke(m, raw(), params);
        }

        [[nodiscard]] bool GetIsTrigger() const {
            static auto m = MethodHandler::resolve("UnityEngine.Collider", "get_isTrigger", 0);
            return MethodHandler::invoke<bool>(m, raw());
        }

        void SetIsTrigger(bool value) {
            static auto m = MethodHandler::resolve("UnityEngine.Collider", "set_isTrigger", 1);
            void* params[] = { &value };
            MethodHandler::invoke(m, raw(), params);
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
