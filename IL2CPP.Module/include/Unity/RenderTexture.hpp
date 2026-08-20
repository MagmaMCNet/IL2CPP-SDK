#pragma once
#include "Object.hpp"
#include "../MethodHandler.hpp"
#include "../Reflection.hpp"
#include <IL2CPP.Common/il2cpp_types.hpp>
#include <cstring>

namespace IL2CPP::Module::Unity {

    class RenderTexture : public Object {
    public:
        using Object::Object;

        static RenderTexture Create(int width, int height, int depth = 24) {
            auto klass = Class::find(IL2CPP_STR("UnityEngine.RenderTexture"));
            if (!klass) return {};
            auto obj = klass.new_object();
            if (!obj) return {};

            static auto ctor = MethodHandler::resolve(IL2CPP_STR("UnityEngine.RenderTexture"), IL2CPP_STR(".ctor"), 3);
            if (!ctor) return {};
            void* params[] = { &width, &height, &depth };
            MethodHandler::invoke(ctor, obj.raw(), params);
            return RenderTexture{obj.raw()};
        }

        /// <summary>Create a render texture with an explicit format.</summary>
        /// <param name="format">RenderTextureFormat; 2 is ARGBHalf.</param>
        static RenderTexture Create(int width, int height, int depth, int format) {
            auto klass = Class::find(IL2CPP_STR("UnityEngine.RenderTexture"));
            if (!klass) return {};
            auto obj = klass.new_object();
            if (!obj) return {};

            // .ctor(int,int,int,RenderTextureFormat) shares its argument count
            // with the GraphicsFormat and DefaultFormat overloads, whose enum
            // values mean something else entirely.
            static Method ctor = [] {
                Class klass = Class::find(IL2CPP_STR("UnityEngine.RenderTexture"));
                if (!klass) return Method{ nullptr };

                for (auto& m : klass.get_methods()) {
                    if (!m || m.param_count() != 4) continue;
                    if (std::strcmp(m.name(), IL2CPP_STR(".ctor")) != 0) continue;

                    Type param = m.get_param_type(3);
                    if (!param.name()) continue;
                    if (std::strcmp(param.name(), IL2CPP_STR("RenderTextureFormat")) != 0) continue;
                    return m;
                }

                return Method{ nullptr };
            }();

            if (ctor) {
                void* params[] = { &width, &height, &depth, &format };
                MethodHandler::invoke(ctor, obj.raw(), params);
                return RenderTexture{ obj.raw() };
            }

            // No RenderTextureFormat overload found: fall back to the plain
            // three-argument constructor rather than handing back nothing.
            static auto simple = MethodHandler::resolve(
                IL2CPP_STR("UnityEngine.RenderTexture"), IL2CPP_STR(".ctor"), 3);
            if (!simple) return {};

            void* params[] = { &width, &height, &depth };
            MethodHandler::invoke(simple, obj.raw(), params);
            return RenderTexture{ obj.raw() };
        }

        /// <summary>Allocate the underlying GPU resource.</summary>
        bool CreateResource() {
            static auto m = MethodHandler::resolve(IL2CPP_STR("UnityEngine.RenderTexture"), IL2CPP_STR("Create"), 0);
            if (!m) return false;
            return MethodHandler::invoke<bool>(m, raw());
        }

        [[nodiscard]] bool IsCreated() const {
            static auto m = MethodHandler::resolve(IL2CPP_STR("UnityEngine.RenderTexture"), IL2CPP_STR("IsCreated"), 0);
            return MethodHandler::invoke<bool>(m, raw());
        }

        /// <summary>Set the sampling filter.</summary>
        /// <param name="mode">0 point, 1 bilinear, 2 trilinear.</param>
        void SetFilterMode(int mode) {
            static auto m = MethodHandler::resolve(IL2CPP_STR("UnityEngine.Texture"), IL2CPP_STR("set_filterMode"), 1);
            void* params[] = { &mode };
            MethodHandler::invoke(m, raw(), params);
        }

        void Release() {
            static auto m = MethodHandler::resolve(IL2CPP_STR("UnityEngine.RenderTexture"), IL2CPP_STR("Release"), 0);
            if (m) MethodHandler::invoke(m, raw());
        }

        [[nodiscard]] int GetWidth() const {
            static auto m = MethodHandler::resolve(IL2CPP_STR("UnityEngine.RenderTexture"), IL2CPP_STR("get_width"), 0);
            return MethodHandler::invoke<int>(m, raw());
        }

        [[nodiscard]] int GetHeight() const {
            static auto m = MethodHandler::resolve(IL2CPP_STR("UnityEngine.RenderTexture"), IL2CPP_STR("get_height"), 0);
            return MethodHandler::invoke<int>(m, raw());
        }

        static void* GetActive() {
            static auto m = MethodHandler::resolve(IL2CPP_STR("UnityEngine.RenderTexture"), IL2CPP_STR("get_active"), 0);
            return MethodHandler::invoke<void*>(m, nullptr);
        }

        static void SetActive(void* rt) {
            static auto m = MethodHandler::resolve(IL2CPP_STR("UnityEngine.RenderTexture"), IL2CPP_STR("set_active"), 1);
            void* params[] = { rt };
            MethodHandler::invoke(m, nullptr, params);
        }
    };

} // namespace IL2CPP::Module::Unity
