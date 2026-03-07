#pragma once
#include "Behaviour.hpp"
#include "../MethodHandler.hpp"

// ============================================================================
//  IL2CPP.Module::Unity::CanvasGroup
//
//  Wrapper for UnityEngine.CanvasGroup using MethodHandler for safe invocation.
// ============================================================================

namespace IL2CPP::Module::Unity {

    class CanvasGroup : public Behaviour {
    public:
        using Behaviour::Behaviour;

        // ---- alpha ----
        [[nodiscard]] float GetAlpha() const {
            static auto m = MethodHandler::resolve("UnityEngine.CanvasGroup", "get_alpha", 0);
            return MethodHandler::invoke<float>(m, raw());
        }
        void SetAlpha(float value) {
            static auto m = MethodHandler::resolve("UnityEngine.CanvasGroup", "set_alpha", 1);
            void* params[] = { &value };
            MethodHandler::invoke(m, raw(), params);
        }

        // ---- interactable ----
        [[nodiscard]] bool GetInteractable() const {
            static auto m = MethodHandler::resolve("UnityEngine.CanvasGroup", "get_interactable", 0);
            return MethodHandler::invoke<bool>(m, raw());
        }
        void SetInteractable(bool value) {
            static auto m = MethodHandler::resolve("UnityEngine.CanvasGroup", "set_interactable", 1);
            void* params[] = { &value };
            MethodHandler::invoke(m, raw(), params);
        }

        // ---- blocksRaycasts ----
        [[nodiscard]] bool GetBlocksRaycasts() const {
            static auto m = MethodHandler::resolve("UnityEngine.CanvasGroup", "get_blocksRaycasts", 0);
            return MethodHandler::invoke<bool>(m, raw());
        }
        void SetBlocksRaycasts(bool value) {
            static auto m = MethodHandler::resolve("UnityEngine.CanvasGroup", "set_blocksRaycasts", 1);
            void* params[] = { &value };
            MethodHandler::invoke(m, raw(), params);
        }

        // ---- ignoreParentGroups ----
        [[nodiscard]] bool GetIgnoreParentGroups() const {
            static auto m = MethodHandler::resolve("UnityEngine.CanvasGroup", "get_ignoreParentGroups", 0);
            return MethodHandler::invoke<bool>(m, raw());
        }
        void SetIgnoreParentGroups(bool value) {
            static auto m = MethodHandler::resolve("UnityEngine.CanvasGroup", "set_ignoreParentGroups", 1);
            void* params[] = { &value };
            MethodHandler::invoke(m, raw(), params);
        }
    };

} // namespace IL2CPP::Module::Unity
