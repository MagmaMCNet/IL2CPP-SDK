#pragma once
#include "Behaviour.hpp"
#include "../MethodHandler.hpp"
#include <IL2CPP.Common/il2cpp_types.hpp>

// ============================================================================
//  IL2CPP.Module::Unity::Canvas
//
//  Wrapper for UnityEngine.Canvas using MethodHandler for safe invocation.
// ============================================================================

namespace IL2CPP::Module::Unity {

    class Canvas : public Behaviour {
    public:
        using Behaviour::Behaviour;

        // ---- renderMode ----
        [[nodiscard]] int GetRenderMode() const {
            static auto m = MethodHandler::resolve("UnityEngine.Canvas", "get_renderMode", 0);
            return MethodHandler::invoke<int>(m, raw());
        }
        void SetRenderMode(int mode) {
            static auto m = MethodHandler::resolve("UnityEngine.Canvas", "set_renderMode", 1);
            void* params[] = { &mode };
            MethodHandler::invoke(m, raw(), params);
        }

        // ---- sortingOrder ----
        [[nodiscard]] int GetSortingOrder() const {
            static auto m = MethodHandler::resolve("UnityEngine.Canvas", "get_sortingOrder", 0);
            return MethodHandler::invoke<int>(m, raw());
        }
        void SetSortingOrder(int order) {
            static auto m = MethodHandler::resolve("UnityEngine.Canvas", "set_sortingOrder", 1);
            void* params[] = { &order };
            MethodHandler::invoke(m, raw(), params);
        }

        // ---- scaleFactor ----
        [[nodiscard]] float GetScaleFactor() const {
            static auto m = MethodHandler::resolve("UnityEngine.Canvas", "get_scaleFactor", 0);
            return MethodHandler::invoke<float>(m, raw());
        }
        void SetScaleFactor(float factor) {
            static auto m = MethodHandler::resolve("UnityEngine.Canvas", "set_scaleFactor", 1);
            void* params[] = { &factor };
            MethodHandler::invoke(m, raw(), params);
        }

        // ---- overrideSorting ----
        [[nodiscard]] bool GetOverrideSorting() const {
            static auto m = MethodHandler::resolve("UnityEngine.Canvas", "get_overrideSorting", 0);
            return MethodHandler::invoke<bool>(m, raw());
        }
        void SetOverrideSorting(bool value) {
            static auto m = MethodHandler::resolve("UnityEngine.Canvas", "set_overrideSorting", 1);
            void* params[] = { &value };
            MethodHandler::invoke(m, raw(), params);
        }

        // ---- pixelPerfect ----
        [[nodiscard]] bool GetPixelPerfect() const {
            static auto m = MethodHandler::resolve("UnityEngine.Canvas", "get_pixelPerfect", 0);
            return MethodHandler::invoke<bool>(m, raw());
        }
        void SetPixelPerfect(bool value) {
            static auto m = MethodHandler::resolve("UnityEngine.Canvas", "set_pixelPerfect", 1);
            void* params[] = { &value };
            MethodHandler::invoke(m, raw(), params);
        }

        // ---- worldCamera (read-only, returns raw pointer) ----
        [[nodiscard]] void* GetWorldCamera() const {
            static auto m = MethodHandler::resolve("UnityEngine.Canvas", "get_worldCamera", 0);
            return MethodHandler::invoke<void*>(m, raw());
        }

        // ---- rootCanvas (read-only) ----
        [[nodiscard]] Canvas GetRootCanvas() const {
            static auto m = MethodHandler::resolve("UnityEngine.Canvas", "get_rootCanvas", 0);
            return Canvas{ MethodHandler::invoke<void*>(m, raw()) };
        }

        // ---- Static: ForceUpdateCanvases ----
        static void ForceUpdateCanvases() {
            static auto m = MethodHandler::resolve("UnityEngine.Canvas", "ForceUpdateCanvases", 0);
            MethodHandler::invoke(m, nullptr);
        }
    };

} // namespace IL2CPP::Module::Unity
