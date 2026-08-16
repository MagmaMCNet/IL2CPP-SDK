#pragma once
#include "Object.hpp"
#include "Camera.hpp"
#include "../MethodHandler.hpp"
#include "../ManagedObject.hpp"
#include <IL2CPP.Common/il2cpp_types.hpp>
#include <string_view>

namespace IL2CPP::Module::Unity {

    enum class CameraEvent : int {
        BeforeDepthTexture = 0,
        AfterDepthTexture = 1,
        BeforeDepthNormalsTexture = 2,
        AfterDepthNormalsTexture = 3,
        BeforeGBuffer = 4,
        AfterGBuffer = 5,
        BeforeLighting = 6,
        AfterLighting = 7,
        BeforeFinalPass = 8,
        AfterFinalPass = 9,
        BeforeForwardOpaque = 10,
        AfterForwardOpaque = 11,
        BeforeImageEffectsOpaque = 12,
        AfterImageEffectsOpaque = 13,
        BeforeSkybox = 14,
        AfterSkybox = 15,
        BeforeForwardAlpha = 16,
        AfterForwardAlpha = 17,
        BeforeImageEffects = 18,
        AfterImageEffects = 19,
        AfterEverything = 20,
    };

    enum class BuiltinRenderTextureType : int {
        None = 0,
        CurrentActive = 1,
        CameraTarget = 2,
        Depth = 3,
        DepthNormals = 4,
    };

    /// <summary>A recorded list of rendering commands that can be attached to a camera.</summary>
    class CommandBuffer : public ManagedObject {
    public:
        using ManagedObject::ManagedObject;

        /// <summary>Create an empty command buffer.</summary>
        /// <returns>The new buffer, or an empty CommandBuffer on failure.</returns>
        [[nodiscard]] static CommandBuffer New() {
            Class klass = Class::find(IL2CPP_STR("UnityEngine.Rendering.CommandBuffer"));
            if (!klass) return {};

            CommandBuffer buffer{ klass.new_object().raw() };
            if (!buffer) return {};

            static auto ctor = MethodHandler::resolve(
                IL2CPP_STR("UnityEngine.Rendering.CommandBuffer"), IL2CPP_STR(".ctor"), 0);
            if (!ctor) return {};
            MethodHandler::invoke(ctor, buffer.raw());
            return buffer;
        }

        /// <summary>Set the buffer's name, as shown in the frame debugger.</summary>
        void SetName(std::string_view name) {
            static auto m = MethodHandler::resolve(
                IL2CPP_STR("UnityEngine.Rendering.CommandBuffer"), IL2CPP_STR("set_name"), 1);
            auto* e = GetExports();
            if (!e || !e->m_stringNew) return;
            void* str = reinterpret_cast<void*(IL2CPP_CALLTYPE)(const char*)>(
                e->m_stringNew)(std::string(name).c_str());
            void* params[] = { str };
            MethodHandler::invoke(m, raw(), params);
        }

        /// <summary>Discard all recorded commands, keeping the buffer usable.</summary>
        void Clear() {
            static auto m = MethodHandler::resolve(
                IL2CPP_STR("UnityEngine.Rendering.CommandBuffer"), IL2CPP_STR("Clear"), 0);
            MethodHandler::invoke(m, raw());
        }

        /// <summary>Release the native buffer. It cannot be used afterwards.</summary>
        void Release() {
            static auto m = MethodHandler::resolve(
                IL2CPP_STR("UnityEngine.Rendering.CommandBuffer"), IL2CPP_STR("Release"), 0);
            MethodHandler::invoke(m, raw());
        }

        /// <summary>Draw a single renderer with an override material.</summary>
        /// <param name="renderer">The UnityEngine.Renderer to draw.</param>
        /// <param name="material">Material to draw it with, replacing the renderer's own.</param>
        /// <param name="submesh">Submesh index to draw.</param>
        /// <param name="shaderPass">Pass index, or -1 for every pass.</param>
        void DrawRenderer(void* renderer, void* material, int submesh = 0, int shaderPass = -1) {
            static auto m = MethodHandler::resolve(
                IL2CPP_STR("UnityEngine.Rendering.CommandBuffer"), IL2CPP_STR("DrawRenderer"), 4);
            void* params[] = { renderer, material, &submesh, &shaderPass };
            MethodHandler::invoke(m, raw(), params);
        }

        /// <summary>Allocate a temporary render target addressed by a shader property id.</summary>
        /// <param name="nameId">Shader property id from Shader.PropertyToID, used to address the target.</param>
        /// <param name="depthBuffer">Depth bits: 0, 16 or 24.</param>
        /// <param name="filterMode">0 point, 1 bilinear, 2 trilinear.</param>
        /// <param name="format">RenderTextureFormat; 0 is ARGB32.</param>
        void GetTemporaryRT(int nameId, int width, int height, int depthBuffer = 0,
                            int filterMode = 1, int format = 0) {
            static auto m = MethodHandler::resolve(
                IL2CPP_STR("UnityEngine.Rendering.CommandBuffer"), IL2CPP_STR("GetTemporaryRT"), 6);
            void* params[] = { &nameId, &width, &height, &depthBuffer, &filterMode, &format };
            MethodHandler::invoke(m, raw(), params);
        }

        /// <summary>Release a target previously allocated with GetTemporaryRT.</summary>
        /// <param name="nameId">The same shader property id the target was allocated under.</param>
        void ReleaseTemporaryRT(int nameId) {
            static auto m = MethodHandler::resolve(
                IL2CPP_STR("UnityEngine.Rendering.CommandBuffer"), IL2CPP_STR("ReleaseTemporaryRT"), 1);
            void* params[] = { &nameId };
            MethodHandler::invoke(m, raw(), params);
        }

        /// <summary>Direct subsequent draws at a render target.</summary>
        /// <param name="renderTargetIdentifier">A boxed RenderTargetIdentifier, or a RenderTexture.</param>
        void SetRenderTarget(void* renderTargetIdentifier) {
            static auto m = MethodHandler::resolve(
                IL2CPP_STR("UnityEngine.Rendering.CommandBuffer"), IL2CPP_STR("SetRenderTarget"), 1);
            void* params[] = { renderTargetIdentifier };
            MethodHandler::invoke(m, raw(), params);
        }

        /// <summary>Clear the current render target.</summary>
        /// <param name="depth">Depth value to clear to, 1.0 being the far plane.</param>
        void ClearRenderTarget(bool clearDepth, bool clearColor, const Color& background, float depth = 1.0f) {
            static auto m = MethodHandler::resolve(
                IL2CPP_STR("UnityEngine.Rendering.CommandBuffer"), IL2CPP_STR("ClearRenderTarget"), 4);
            Color c = background;
            void* params[] = { &clearDepth, &clearColor, &c, &depth };
            MethodHandler::invoke(m, raw(), params);
        }

        /// <summary>Copy source to destination, optionally through a material.</summary>
        /// <param name="material">Null for a straight copy; otherwise the shader to run.</param>
        /// <param name="pass">Pass index, or -1 for every pass.</param>
        void Blit(void* source, void* destination, void* material = nullptr, int pass = -1) {
            const int argc = material ? 4 : 2;
            static auto simple = MethodHandler::resolve(
                IL2CPP_STR("UnityEngine.Rendering.CommandBuffer"), IL2CPP_STR("Blit"), 2);
            static auto withMaterial = MethodHandler::resolve(
                IL2CPP_STR("UnityEngine.Rendering.CommandBuffer"), IL2CPP_STR("Blit"), 4);

            if (argc == 2) {
                void* params[] = { source, destination };
                MethodHandler::invoke(simple, raw(), params);
                return;
            }

            void* params[] = { source, destination, material, &pass };
            MethodHandler::invoke(withMaterial, raw(), params);
        }

        /// <summary>Bind a texture to a global shader property.</summary>
        /// <param name="nameId">Shader property id from Shader.PropertyToID.</param>
        void SetGlobalTexture(int nameId, void* renderTargetIdentifier) {
            static auto m = MethodHandler::resolve(
                IL2CPP_STR("UnityEngine.Rendering.CommandBuffer"), IL2CPP_STR("SetGlobalTexture"), 2);
            void* params[] = { &nameId, renderTargetIdentifier };
            MethodHandler::invoke(m, raw(), params);
        }

        /// <summary>Set a global shader float.</summary>
        /// <param name="nameId">Shader property id from Shader.PropertyToID.</param>
        void SetGlobalFloat(int nameId, float value) {
            static auto m = MethodHandler::resolve(
                IL2CPP_STR("UnityEngine.Rendering.CommandBuffer"), IL2CPP_STR("SetGlobalFloat"), 2);
            void* params[] = { &nameId, &value };
            MethodHandler::invoke(m, raw(), params);
        }

        /// <summary>Set a global shader vector.</summary>
        /// <param name="nameId">Shader property id from Shader.PropertyToID.</param>
        void SetGlobalVector(int nameId, const Vector4& value) {
            static auto m = MethodHandler::resolve(
                IL2CPP_STR("UnityEngine.Rendering.CommandBuffer"), IL2CPP_STR("SetGlobalVector"), 2);
            Vector4 v = value;
            void* params[] = { &nameId, &v };
            MethodHandler::invoke(m, raw(), params);
        }

        /// <summary>Attach a buffer to a camera so it runs at the given event.</summary>
        /// <param name="evt">Point in the camera's render loop to execute at.</param>
        static void AddToCamera(Camera camera, CameraEvent evt, CommandBuffer buffer) {
            static auto m = MethodHandler::resolve(
                IL2CPP_STR("UnityEngine.Camera"), IL2CPP_STR("AddCommandBuffer"), 2);
            int e = static_cast<int>(evt);
            void* params[] = { &e, buffer.raw() };
            MethodHandler::invoke(m, camera.raw(), params);
        }

        /// <summary>Detach a buffer previously added at the given event.</summary>
        /// <param name="evt">The event the buffer was attached at.</param>
        static void RemoveFromCamera(Camera camera, CameraEvent evt, CommandBuffer buffer) {
            static auto m = MethodHandler::resolve(
                IL2CPP_STR("UnityEngine.Camera"), IL2CPP_STR("RemoveCommandBuffer"), 2);
            int e = static_cast<int>(evt);
            void* params[] = { &e, buffer.raw() };
            MethodHandler::invoke(m, camera.raw(), params);
        }

        /// <summary>Detach every buffer from a camera, at every event.</summary>
        static void RemoveAllFromCamera(Camera camera) {
            static auto m = MethodHandler::resolve(
                IL2CPP_STR("UnityEngine.Camera"), IL2CPP_STR("RemoveAllCommandBuffers"), 0);
            MethodHandler::invoke(m, camera.raw());
        }
    };

} // namespace IL2CPP::Module::Unity
