#pragma once
#include "Behaviour.hpp"
#include "../MethodHandler.hpp"
#include <IL2CPP.Common/il2cpp_types.hpp>

namespace IL2CPP::Module::Unity {

    class Light : public Behaviour {
    public:
        using Behaviour::Behaviour;

        [[nodiscard]] int GetType() const {
            static auto m = MethodHandler::resolve("UnityEngine.Light", "get_type", 0);
            return MethodHandler::invoke<int>(m, raw());
        }
        void SetType(int value) {
            static auto m = MethodHandler::resolve("UnityEngine.Light", "set_type", 1);
            void* params[] = { &value };
            MethodHandler::invoke(m, raw(), params);
        }

        [[nodiscard]] Color GetColor() const {
            static auto m = MethodHandler::resolve("UnityEngine.Light", "get_color", 0);
            return MethodHandler::invoke<Color>(m, raw());
        }
        void SetColor(const Color& value) {
            static auto m = MethodHandler::resolve("UnityEngine.Light", "set_color", 1);
            Color c = value;
            void* params[] = { &c };
            MethodHandler::invoke(m, raw(), params);
        }

        [[nodiscard]] float GetIntensity() const {
            static auto m = MethodHandler::resolve("UnityEngine.Light", "get_intensity", 0);
            return MethodHandler::invoke<float>(m, raw());
        }
        void SetIntensity(float value) {
            static auto m = MethodHandler::resolve("UnityEngine.Light", "set_intensity", 1);
            void* params[] = { &value };
            MethodHandler::invoke(m, raw(), params);
        }

        [[nodiscard]] float GetRange() const {
            static auto m = MethodHandler::resolve("UnityEngine.Light", "get_range", 0);
            return MethodHandler::invoke<float>(m, raw());
        }
        void SetRange(float value) {
            static auto m = MethodHandler::resolve("UnityEngine.Light", "set_range", 1);
            void* params[] = { &value };
            MethodHandler::invoke(m, raw(), params);
        }

        [[nodiscard]] float GetSpotAngle() const {
            static auto m = MethodHandler::resolve("UnityEngine.Light", "get_spotAngle", 0);
            return MethodHandler::invoke<float>(m, raw());
        }
        void SetSpotAngle(float value) {
            static auto m = MethodHandler::resolve("UnityEngine.Light", "set_spotAngle", 1);
            void* params[] = { &value };
            MethodHandler::invoke(m, raw(), params);
        }

        [[nodiscard]] float GetInnerSpotAngle() const {
            static auto m = MethodHandler::resolve("UnityEngine.Light", "get_innerSpotAngle", 0);
            return MethodHandler::invoke<float>(m, raw());
        }
        void SetInnerSpotAngle(float value) {
            static auto m = MethodHandler::resolve("UnityEngine.Light", "set_innerSpotAngle", 1);
            void* params[] = { &value };
            MethodHandler::invoke(m, raw(), params);
        }

        [[nodiscard]] float GetBounceIntensity() const {
            static auto m = MethodHandler::resolve("UnityEngine.Light", "get_bounceIntensity", 0);
            return MethodHandler::invoke<float>(m, raw());
        }
        void SetBounceIntensity(float value) {
            static auto m = MethodHandler::resolve("UnityEngine.Light", "set_bounceIntensity", 1);
            void* params[] = { &value };
            MethodHandler::invoke(m, raw(), params);
        }

        [[nodiscard]] int GetShadows() const {
            static auto m = MethodHandler::resolve("UnityEngine.Light", "get_shadows", 0);
            return MethodHandler::invoke<int>(m, raw());
        }
        void SetShadows(int value) {
            static auto m = MethodHandler::resolve("UnityEngine.Light", "set_shadows", 1);
            void* params[] = { &value };
            MethodHandler::invoke(m, raw(), params);
        }

        [[nodiscard]] float GetShadowStrength() const {
            static auto m = MethodHandler::resolve("UnityEngine.Light", "get_shadowStrength", 0);
            return MethodHandler::invoke<float>(m, raw());
        }
        void SetShadowStrength(float value) {
            static auto m = MethodHandler::resolve("UnityEngine.Light", "set_shadowStrength", 1);
            void* params[] = { &value };
            MethodHandler::invoke(m, raw(), params);
        }

        [[nodiscard]] int GetRenderMode() const {
            static auto m = MethodHandler::resolve("UnityEngine.Light", "get_renderMode", 0);
            return MethodHandler::invoke<int>(m, raw());
        }
        void SetRenderMode(int value) {
            static auto m = MethodHandler::resolve("UnityEngine.Light", "set_renderMode", 1);
            void* params[] = { &value };
            MethodHandler::invoke(m, raw(), params);
        }

        [[nodiscard]] float GetCookieSize() const {
            static auto m = MethodHandler::resolve("UnityEngine.Light", "get_cookieSize", 0);
            return MethodHandler::invoke<float>(m, raw());
        }
        void SetCookieSize(float value) {
            static auto m = MethodHandler::resolve("UnityEngine.Light", "set_cookieSize", 1);
            void* params[] = { &value };
            MethodHandler::invoke(m, raw(), params);
        }

        [[nodiscard]] void* GetCookie() const {
            static auto m = MethodHandler::resolve("UnityEngine.Light", "get_cookie", 0);
            return MethodHandler::invoke<void*>(m, raw());
        }
        void SetCookie(void* texture) {
            static auto m = MethodHandler::resolve("UnityEngine.Light", "set_cookie", 1);
            void* params[] = { texture };
            MethodHandler::invoke(m, raw(), params);
        }
    };

} // namespace IL2CPP::Module::Unity
