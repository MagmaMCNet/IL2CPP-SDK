#pragma once
#include "UIBehaviour.hpp"
#include "../MethodHandler.hpp"

namespace IL2CPP::Module::Unity {

    class ContentSizeFitter : public UIBehaviour {
    public:
        using UIBehaviour::UIBehaviour;

        [[nodiscard]] int GetHorizontalFit() const {
            static auto m = MethodHandler::resolve("UnityEngine.UI.ContentSizeFitter", "get_horizontalFit", 0);
            return MethodHandler::invoke<int>(m, raw());
        }
        void SetHorizontalFit(int value) {
            static auto m = MethodHandler::resolve("UnityEngine.UI.ContentSizeFitter", "set_horizontalFit", 1);
            void* params[] = { &value };
            MethodHandler::invoke(m, raw(), params);
        }

        [[nodiscard]] int GetVerticalFit() const {
            static auto m = MethodHandler::resolve("UnityEngine.UI.ContentSizeFitter", "get_verticalFit", 0);
            return MethodHandler::invoke<int>(m, raw());
        }
        void SetVerticalFit(int value) {
            static auto m = MethodHandler::resolve("UnityEngine.UI.ContentSizeFitter", "set_verticalFit", 1);
            void* params[] = { &value };
            MethodHandler::invoke(m, raw(), params);
        }

        void SetLayoutHorizontal() {
            static auto m = MethodHandler::resolve("UnityEngine.UI.ContentSizeFitter", "SetLayoutHorizontal", 0);
            MethodHandler::invoke(m, raw());
        }
        void SetLayoutVertical() {
            static auto m = MethodHandler::resolve("UnityEngine.UI.ContentSizeFitter", "SetLayoutVertical", 0);
            MethodHandler::invoke(m, raw());
        }
    };

} // namespace IL2CPP::Module::Unity
