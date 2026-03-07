#pragma once
#include "UIBehaviour.hpp"
#include "../MethodHandler.hpp"
#include <IL2CPP.Common/il2cpp_types.hpp>

namespace IL2CPP::Module::Unity {

    class Graphic : public UIBehaviour {
    public:
        using UIBehaviour::UIBehaviour;

        // ---- color (get/set) ----
        [[nodiscard]] Color GetColor() const {
            static auto m = MethodHandler::resolve("UnityEngine.UI.Graphic", "get_color", 0);
            return MethodHandler::invoke<Color>(m, raw());
        }
        void SetColor(const Color& value) {
            static auto m = MethodHandler::resolve("UnityEngine.UI.Graphic", "set_color", 1);
            Color c = value;
            void* params[] = { &c };
            MethodHandler::invoke(m, raw(), params);
        }

        // ---- raycastTarget (get/set) ----
        [[nodiscard]] bool GetRaycastTarget() const {
            static auto m = MethodHandler::resolve("UnityEngine.UI.Graphic", "get_raycastTarget", 0);
            return MethodHandler::invoke<bool>(m, raw());
        }
        void SetRaycastTarget(bool value) {
            static auto m = MethodHandler::resolve("UnityEngine.UI.Graphic", "set_raycastTarget", 1);
            void* params[] = { &value };
            MethodHandler::invoke(m, raw(), params);
        }

        // ---- raycastPadding (get/set) ----
        [[nodiscard]] Vector4 GetRaycastPadding() const {
            static auto m = MethodHandler::resolve("UnityEngine.UI.Graphic", "get_raycastPadding", 0);
            return MethodHandler::invoke<Vector4>(m, raw());
        }
        void SetRaycastPadding(const Vector4& value) {
            static auto m = MethodHandler::resolve("UnityEngine.UI.Graphic", "set_raycastPadding", 1);
            Vector4 v = value;
            void* params[] = { &v };
            MethodHandler::invoke(m, raw(), params);
        }

        // ---- depth (get, read-only) ----
        [[nodiscard]] int GetDepth() const {
            static auto m = MethodHandler::resolve("UnityEngine.UI.Graphic", "get_depth", 0);
            return MethodHandler::invoke<int>(m, raw());
        }

        // ---- rectTransform (get, read-only, raw pointer) ----
        [[nodiscard]] void* GetRectTransformRaw() const {
            static auto m = MethodHandler::resolve("UnityEngine.UI.Graphic", "get_rectTransform", 0);
            return MethodHandler::invoke<void*>(m, raw());
        }

        // ---- canvas (get, read-only, raw pointer) ----
        [[nodiscard]] void* GetCanvasRaw() const {
            static auto m = MethodHandler::resolve("UnityEngine.UI.Graphic", "get_canvas", 0);
            return MethodHandler::invoke<void*>(m, raw());
        }

        // ---- canvasRenderer (get, read-only, raw pointer) ----
        [[nodiscard]] void* GetCanvasRendererRaw() const {
            static auto m = MethodHandler::resolve("UnityEngine.UI.Graphic", "get_canvasRenderer", 0);
            return MethodHandler::invoke<void*>(m, raw());
        }

        // ---- material (get/set, raw pointer) ----
        [[nodiscard]] void* GetMaterial() const {
            static auto m = MethodHandler::resolve("UnityEngine.UI.Graphic", "get_material", 0);
            return MethodHandler::invoke<void*>(m, raw());
        }
        void SetMaterial(void* material) {
            static auto m = MethodHandler::resolve("UnityEngine.UI.Graphic", "set_material", 1);
            void* params[] = { material };
            MethodHandler::invoke(m, raw(), params);
        }

        // ---- defaultMaterial (get, read-only, raw pointer) ----
        [[nodiscard]] void* GetDefaultMaterial() const {
            static auto m = MethodHandler::resolve("UnityEngine.UI.Graphic", "get_defaultMaterial", 0);
            return MethodHandler::invoke<void*>(m, raw());
        }

        // ---- materialForRendering (get, read-only, raw pointer) ----
        [[nodiscard]] void* GetMaterialForRendering() const {
            static auto m = MethodHandler::resolve("UnityEngine.UI.Graphic", "get_materialForRendering", 0);
            return MethodHandler::invoke<void*>(m, raw());
        }

        // ---- mainTexture (get, read-only, raw pointer) ----
        [[nodiscard]] void* GetMainTexture() const {
            static auto m = MethodHandler::resolve("UnityEngine.UI.Graphic", "get_mainTexture", 0);
            return MethodHandler::invoke<void*>(m, raw());
        }

        // ---- SetAllDirty ----
        void SetAllDirty() {
            static auto m = MethodHandler::resolve("UnityEngine.UI.Graphic", "SetAllDirty", 0);
            MethodHandler::invoke(m, raw());
        }

        // ---- SetLayoutDirty ----
        void SetLayoutDirty() {
            static auto m = MethodHandler::resolve("UnityEngine.UI.Graphic", "SetLayoutDirty", 0);
            MethodHandler::invoke(m, raw());
        }

        // ---- SetVerticesDirty ----
        void SetVerticesDirty() {
            static auto m = MethodHandler::resolve("UnityEngine.UI.Graphic", "SetVerticesDirty", 0);
            MethodHandler::invoke(m, raw());
        }

        // ---- SetMaterialDirty ----
        void SetMaterialDirty() {
            static auto m = MethodHandler::resolve("UnityEngine.UI.Graphic", "SetMaterialDirty", 0);
            MethodHandler::invoke(m, raw());
        }

        // ---- Rebuild ----
        void Rebuild(int canvasUpdate) {
            static auto m = MethodHandler::resolve("UnityEngine.UI.Graphic", "Rebuild", 1);
            void* params[] = { &canvasUpdate };
            MethodHandler::invoke(m, raw(), params);
        }

        // ---- SetNativeSize ----
        void SetNativeSize() {
            static auto m = MethodHandler::resolve("UnityEngine.UI.Graphic", "SetNativeSize", 0);
            MethodHandler::invoke(m, raw());
        }

        // ---- CrossFadeAlpha ----
        void CrossFadeAlpha(float alpha, float duration, bool ignoreTimeScale) {
            static auto m = MethodHandler::resolve("UnityEngine.UI.Graphic", "CrossFadeAlpha", 3);
            void* params[] = { &alpha, &duration, &ignoreTimeScale };
            MethodHandler::invoke(m, raw(), params);
        }

        // ---- CrossFadeColor ----
        void CrossFadeColor(const Color& targetColor, float duration, bool ignoreTimeScale, bool useAlpha) {
            static auto m = MethodHandler::resolve("UnityEngine.UI.Graphic", "CrossFadeColor", 4);
            Color c = targetColor;
            void* params[] = { &c, &duration, &ignoreTimeScale, &useAlpha };
            MethodHandler::invoke(m, raw(), params);
        }

        // ---- GraphicUpdateComplete ----
        void GraphicUpdateComplete() {
            static auto m = MethodHandler::resolve("UnityEngine.UI.Graphic", "GraphicUpdateComplete", 0);
            MethodHandler::invoke(m, raw());
        }
    };

} // namespace IL2CPP::Module::Unity
