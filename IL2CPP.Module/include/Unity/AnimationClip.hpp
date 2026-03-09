#pragma once
#include "Object.hpp"
#include "../MethodHandler.hpp"
#include <IL2CPP.Common/il2cpp_shared.hpp>
#include <string>
#include <string_view>

namespace IL2CPP::Module::Unity {

    class AnimationClip : public Object {
    public:
        using Object::Object;

        // ---- length ----
        [[nodiscard]] float GetLength() const {
            static auto m = MethodHandler::resolve("UnityEngine.AnimationClip", "get_length", 0);
            return MethodHandler::invoke<float>(m, raw());
        }

        // ---- frameRate ----
        [[nodiscard]] float GetFrameRate() const {
            static auto m = MethodHandler::resolve("UnityEngine.AnimationClip", "get_frameRate", 0);
            return MethodHandler::invoke<float>(m, raw());
        }
        void SetFrameRate(float value) {
            static auto m = MethodHandler::resolve("UnityEngine.AnimationClip", "set_frameRate", 1);
            void* params[] = { &value };
            MethodHandler::invoke(m, raw(), params);
        }

        // ---- wrapMode ----
        [[nodiscard]] int GetWrapMode() const {
            static auto m = MethodHandler::resolve("UnityEngine.AnimationClip", "get_wrapMode", 0);
            return MethodHandler::invoke<int>(m, raw());
        }
        void SetWrapMode(int value) {
            static auto m = MethodHandler::resolve("UnityEngine.AnimationClip", "set_wrapMode", 1);
            void* params[] = { &value };
            MethodHandler::invoke(m, raw(), params);
        }

        // ---- localBounds ----
        [[nodiscard]] Bounds GetLocalBounds() const {
            static auto m = MethodHandler::resolve("UnityEngine.AnimationClip", "get_localBounds", 0);
            return MethodHandler::invoke<Bounds>(m, raw());
        }

        // ---- legacy ----
        [[nodiscard]] bool GetLegacy() const {
            static auto m = MethodHandler::resolve("UnityEngine.AnimationClip", "get_legacy", 0);
            return MethodHandler::invoke<bool>(m, raw());
        }
        void SetLegacy(bool value) {
            static auto m = MethodHandler::resolve("UnityEngine.AnimationClip", "set_legacy", 1);
            void* params[] = { &value };
            MethodHandler::invoke(m, raw(), params);
        }

        // ---- humanMotion (get-only) ----
        [[nodiscard]] bool GetHumanMotion() const {
            static auto m = MethodHandler::resolve("UnityEngine.AnimationClip", "get_humanMotion", 0);
            return MethodHandler::invoke<bool>(m, raw());
        }

        // ---- empty (get-only) ----
        [[nodiscard]] bool GetEmpty() const {
            static auto m = MethodHandler::resolve("UnityEngine.AnimationClip", "get_empty", 0);
            return MethodHandler::invoke<bool>(m, raw());
        }

        // ---- SampleAnimation ----
        void SampleAnimation(void* gameObject, float time) {
            static auto m = MethodHandler::resolve("UnityEngine.AnimationClip", "SampleAnimation", 2);
            void* params[] = { gameObject, &time };
            MethodHandler::invoke(m, raw(), params);
        }
    };

} // namespace IL2CPP::Module::Unity
