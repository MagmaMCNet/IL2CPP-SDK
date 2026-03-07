#pragma once
#include "Selectable.hpp"
#include "../MethodHandler.hpp"

namespace IL2CPP::Module::Unity {

    class Toggle : public Selectable {
    public:
        using Selectable::Selectable;

        // ---- isOn (get/set) ----
        [[nodiscard]] bool GetIsOn() const {
            static auto m = MethodHandler::resolve("UnityEngine.UI.Toggle", "get_isOn", 0);
            return MethodHandler::invoke<bool>(m, raw());
        }
        void SetIsOn(bool value) {
            static auto m = MethodHandler::resolve("UnityEngine.UI.Toggle", "set_isOn", 1);
            void* params[] = { &value };
            MethodHandler::invoke(m, raw(), params);
        }

        // ---- SetIsOnWithoutNotify ----
        void SetIsOnWithoutNotify(bool value) {
            static auto m = MethodHandler::resolve("UnityEngine.UI.Toggle", "SetIsOnWithoutNotify", 1);
            void* params[] = { &value };
            MethodHandler::invoke(m, raw(), params);
        }

        // ---- onValueChanged (get, raw pointer to UnityEvent<bool>) ----
        [[nodiscard]] void* GetOnValueChangedRaw() const {
            static auto m = MethodHandler::resolve("UnityEngine.UI.Toggle", "get_onValueChanged", 0);
            return MethodHandler::invoke<void*>(m, raw());
        }
    };

} // namespace IL2CPP::Module::Unity
