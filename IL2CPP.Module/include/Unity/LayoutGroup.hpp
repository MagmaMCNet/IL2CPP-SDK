#pragma once
#include "UIBehaviour.hpp"
#include "../MethodHandler.hpp"

namespace IL2CPP::Module::Unity {

    class LayoutGroup : public UIBehaviour {
    public:
        using UIBehaviour::UIBehaviour;

        // ---- padding (raw RectOffset pointer) ----
        [[nodiscard]] void* GetPadding() const {
            static auto m = MethodHandler::resolve("UnityEngine.UI.LayoutGroup", "get_padding", 0);
            return MethodHandler::invoke<void*>(m, raw());
        }
        void SetPadding(void* value) {
            static auto m = MethodHandler::resolve("UnityEngine.UI.LayoutGroup", "set_padding", 1);
            void* params[] = { value };
            MethodHandler::invoke(m, raw(), params);
        }

        // ---- childAlignment ----
        [[nodiscard]] int GetChildAlignment() const {
            static auto m = MethodHandler::resolve("UnityEngine.UI.LayoutGroup", "get_childAlignment", 0);
            return MethodHandler::invoke<int>(m, raw());
        }
        void SetChildAlignment(int value) {
            static auto m = MethodHandler::resolve("UnityEngine.UI.LayoutGroup", "set_childAlignment", 1);
            void* params[] = { &value };
            MethodHandler::invoke(m, raw(), params);
        }

        // ---- SetLayoutHorizontal / SetLayoutVertical ----
        void SetLayoutHorizontal() {
            static auto m = MethodHandler::resolve("UnityEngine.UI.LayoutGroup", "SetLayoutHorizontal", 0);
            MethodHandler::invoke(m, raw());
        }
        void SetLayoutVertical() {
            static auto m = MethodHandler::resolve("UnityEngine.UI.LayoutGroup", "SetLayoutVertical", 0);
            MethodHandler::invoke(m, raw());
        }
    };

} // namespace IL2CPP::Module::Unity
