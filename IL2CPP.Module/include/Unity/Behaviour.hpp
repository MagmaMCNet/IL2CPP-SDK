#pragma once
#include "Component.hpp"
#include "../MethodHandler.hpp"

// ============================================================================
//  IL2CPP.Module::Unity::Behaviour
// ============================================================================

namespace IL2CPP::Module::Unity {

    class Behaviour : public Component {
    public:
        using Component::Component;

        [[nodiscard]] bool GetEnabled() const {
            static auto m = MethodHandler::resolve("UnityEngine.Behaviour", "get_enabled", 0);
            return MethodHandler::invoke<bool>(m, raw());
        }

        void SetEnabled(bool value) {
            static auto m = MethodHandler::resolve("UnityEngine.Behaviour", "set_enabled", 1);
            void* params[] = { &value };
            MethodHandler::invoke(m, raw(), params);
        }

        [[nodiscard]] bool GetIsActiveAndEnabled() const {
            static auto m = MethodHandler::resolve("UnityEngine.Behaviour", "get_isActiveAndEnabled", 0);
            return MethodHandler::invoke<bool>(m, raw());
        }

        // ---- Legacy snake_case aliases (deprecated) ----
        [[deprecated("Use GetEnabled()")]] [[nodiscard]] bool get_enabled() const { return GetEnabled(); }
        [[deprecated("Use SetEnabled()")]] void set_enabled(bool v) { SetEnabled(v); }
        [[deprecated("Use GetIsActiveAndEnabled()")]] [[nodiscard]] bool get_is_active_and_enabled() const { return GetIsActiveAndEnabled(); }
    };

} // namespace IL2CPP::Module::Unity
