#pragma once
#include "Component.hpp"
#include "../MethodHandler.hpp"
#include <IL2CPP.Common/il2cpp_types.hpp>

namespace IL2CPP::Module::Unity {

    class Renderer : public Component {
    public:
        using Component::Component;

        // ---- enabled ----
        [[nodiscard]] bool GetEnabled() const {
            static auto m = MethodHandler::resolve("UnityEngine.Renderer", "get_enabled", 0);
            return MethodHandler::invoke<bool>(m, raw());
        }
        void SetEnabled(bool value) {
            static auto m = MethodHandler::resolve("UnityEngine.Renderer", "set_enabled", 1);
            void* params[] = { &value };
            MethodHandler::invoke(m, raw(), params);
        }

        // ---- material ----
        [[nodiscard]] void* GetMaterial() const {
            static auto m = MethodHandler::resolve("UnityEngine.Renderer", "get_material", 0);
            return MethodHandler::invoke<void*>(m, raw());
        }
        void SetMaterial(void* material) {
            static auto m = MethodHandler::resolve("UnityEngine.Renderer", "set_material", 1);
            void* params[] = { material };
            MethodHandler::invoke(m, raw(), params);
        }

        // ---- sharedMaterial ----
        [[nodiscard]] void* GetSharedMaterial() const {
            static auto m = MethodHandler::resolve("UnityEngine.Renderer", "get_sharedMaterial", 0);
            return MethodHandler::invoke<void*>(m, raw());
        }
        void SetSharedMaterial(void* material) {
            static auto m = MethodHandler::resolve("UnityEngine.Renderer", "set_sharedMaterial", 1);
            void* params[] = { material };
            MethodHandler::invoke(m, raw(), params);
        }

        // ---- bounds ----
        [[nodiscard]] Bounds GetBounds() const {
            static auto m = MethodHandler::resolve("UnityEngine.Renderer", "get_bounds", 0);
            return MethodHandler::invoke<Bounds>(m, raw());
        }

        // ---- sortingOrder ----
        [[nodiscard]] int GetSortingOrder() const {
            static auto m = MethodHandler::resolve("UnityEngine.Renderer", "get_sortingOrder", 0);
            return MethodHandler::invoke<int>(m, raw());
        }
        void SetSortingOrder(int value) {
            static auto m = MethodHandler::resolve("UnityEngine.Renderer", "set_sortingOrder", 1);
            void* params[] = { &value };
            MethodHandler::invoke(m, raw(), params);
        }

        // ---- sortingLayerID ----
        [[nodiscard]] int GetSortingLayerID() const {
            static auto m = MethodHandler::resolve("UnityEngine.Renderer", "get_sortingLayerID", 0);
            return MethodHandler::invoke<int>(m, raw());
        }
        void SetSortingLayerID(int value) {
            static auto m = MethodHandler::resolve("UnityEngine.Renderer", "set_sortingLayerID", 1);
            void* params[] = { &value };
            MethodHandler::invoke(m, raw(), params);
        }

        // ---- isVisible (get-only) ----
        [[nodiscard]] bool GetIsVisible() const {
            static auto m = MethodHandler::resolve("UnityEngine.Renderer", "get_isVisible", 0);
            return MethodHandler::invoke<bool>(m, raw());
        }

        // ---- receiveShadows ----
        [[nodiscard]] bool GetReceiveShadows() const {
            static auto m = MethodHandler::resolve("UnityEngine.Renderer", "get_receiveShadows", 0);
            return MethodHandler::invoke<bool>(m, raw());
        }
        void SetReceiveShadows(bool value) {
            static auto m = MethodHandler::resolve("UnityEngine.Renderer", "set_receiveShadows", 1);
            void* params[] = { &value };
            MethodHandler::invoke(m, raw(), params);
        }

        // ---- shadowCastingMode ----
        [[nodiscard]] int GetShadowCastingMode() const {
            static auto m = MethodHandler::resolve("UnityEngine.Renderer", "get_shadowCastingMode", 0);
            return MethodHandler::invoke<int>(m, raw());
        }
        void SetShadowCastingMode(int value) {
            static auto m = MethodHandler::resolve("UnityEngine.Renderer", "set_shadowCastingMode", 1);
            void* params[] = { &value };
            MethodHandler::invoke(m, raw(), params);
        }

        // ---- GetPropertyBlock / SetPropertyBlock ----
        void GetPropertyBlock(void* properties) const {
            static auto m = MethodHandler::resolve("UnityEngine.Renderer", "GetPropertyBlock", 1);
            void* params[] = { properties };
            MethodHandler::invoke(m, raw(), params);
        }
        void SetPropertyBlock(void* properties) {
            static auto m = MethodHandler::resolve("UnityEngine.Renderer", "SetPropertyBlock", 1);
            void* params[] = { properties };
            MethodHandler::invoke(m, raw(), params);
        }
    };

} // namespace IL2CPP::Module::Unity
