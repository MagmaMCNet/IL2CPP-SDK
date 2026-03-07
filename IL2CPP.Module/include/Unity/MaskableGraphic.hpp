#pragma once
#include "Graphic.hpp"
#include "../MethodHandler.hpp"
#include <IL2CPP.Common/il2cpp_types.hpp>

namespace IL2CPP::Module::Unity {

    class MaskableGraphic : public Graphic {
    public:
        using Graphic::Graphic;

        // ---- maskable (get/set) ----
        [[nodiscard]] bool GetMaskable() const {
            static auto m = MethodHandler::resolve("UnityEngine.UI.MaskableGraphic", "get_maskable", 0);
            return MethodHandler::invoke<bool>(m, raw());
        }
        void SetMaskable(bool value) {
            static auto m = MethodHandler::resolve("UnityEngine.UI.MaskableGraphic", "set_maskable", 1);
            void* params[] = { &value };
            MethodHandler::invoke(m, raw(), params);
        }

        // ---- GetModifiedMaterial ----
        [[nodiscard]] void* GetModifiedMaterial(void* baseMaterial) const {
            static auto m = MethodHandler::resolve("UnityEngine.UI.MaskableGraphic", "GetModifiedMaterial", 1);
            void* params[] = { baseMaterial };
            return MethodHandler::invoke<void*>(m, raw(), params);
        }

        // ---- RecalculateClipping ----
        void RecalculateClipping() {
            static auto m = MethodHandler::resolve("UnityEngine.UI.MaskableGraphic", "RecalculateClipping", 0);
            MethodHandler::invoke(m, raw());
        }

        // ---- RecalculateMasking ----
        void RecalculateMasking() {
            static auto m = MethodHandler::resolve("UnityEngine.UI.MaskableGraphic", "RecalculateMasking", 0);
            MethodHandler::invoke(m, raw());
        }

        // ---- SetClipRect ----
        void SetClipRect(const Rect& clipRect, bool validRect) {
            static auto m = MethodHandler::resolve("UnityEngine.UI.MaskableGraphic", "SetClipRect", 2);
            Rect r = clipRect;
            void* params[] = { &r, &validRect };
            MethodHandler::invoke(m, raw(), params);
        }

        // ---- SetClipSoftness ----
        void SetClipSoftness(const Vector2& clipSoftness) {
            static auto m = MethodHandler::resolve("UnityEngine.UI.MaskableGraphic", "SetClipSoftness", 1);
            Vector2 v = clipSoftness;
            void* params[] = { &v };
            MethodHandler::invoke(m, raw(), params);
        }

        // ---- Cull ----
        void Cull(const Rect& clipRect, bool validRect) {
            static auto m = MethodHandler::resolve("UnityEngine.UI.MaskableGraphic", "Cull", 2);
            Rect r = clipRect;
            void* params[] = { &r, &validRect };
            MethodHandler::invoke(m, raw(), params);
        }
    };

} // namespace IL2CPP::Module::Unity
