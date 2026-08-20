#pragma once
#include "Object.hpp"
#include "Camera.hpp"
#include "../MethodHandler.hpp"
#include "../ManagedObject.hpp"
#include "../Reflection.hpp"
#include <IL2CPP.Common/il2cpp_types.hpp>
#include <IL2CPP.Common/il2cpp_shared.hpp>
#include <cstring>
#include <string>
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

    /// <summary>A render target argument, as CommandBuffer's RenderTargetIdentifier parameters expect.</summary>
    class RenderTargetHandle {
    public:
        /// <summary>Address a temporary target allocated under a shader property id.</summary>
        [[nodiscard]] static RenderTargetHandle FromNameId(int nameId) {
            return Convert(IL2CPP_STR("Int32"), &nameId);
        }

        /// <summary>Address a texture the caller owns, such as a RenderTexture.</summary>
        [[nodiscard]] static RenderTargetHandle FromRenderTexture(void* renderTexture) {
            if (!renderTexture) return {};
            RenderTargetHandle handle = Convert(IL2CPP_STR("Texture"), renderTexture);
            if (!handle) handle = Convert(IL2CPP_STR("RenderTexture"), renderTexture);
            return handle;
        }

        /// <summary>Address one of the camera's own buffers.</summary>
        [[nodiscard]] static RenderTargetHandle FromBuiltin(BuiltinRenderTextureType type) {
            int value = static_cast<int>(type);
            return Convert(IL2CPP_STR("BuiltinRenderTextureType"), &value);
        }

        /// <summary>The conversion parameter types this Unity build offers, for diagnostics.</summary>
        [[nodiscard]] static std::string AvailableConversions() {
            std::string names;

            Class klass = Class::find(IL2CPP_STR("UnityEngine.Rendering.RenderTargetIdentifier"));
            if (!klass) return IL2CPP_STR("<no RenderTargetIdentifier class>");

            for (auto& method : klass.get_methods()) {
                if (!method || method.param_count() != 1) continue;
                if (std::strcmp(method.name(), IL2CPP_STR("op_Implicit")) != 0) continue;

                Type param = method.get_param_type(0);
                if (!param.name()) continue;
                if (!names.empty()) names += ", ";
                names += param.name();
            }

            return names.empty() ? IL2CPP_STR("<none>") : names;
        }

        /// <summary>Hex dump of the produced struct, for diagnosing a bad conversion.</summary>
        [[nodiscard]] std::string Describe() const {
            if (!m_valid) return IL2CPP_STR("<invalid>");

            static const char* const digits = IL2CPP_STR("0123456789abcdef");
            std::string out;
            for (size_t i = 0; i < 32 && i < sizeof(m_data); ++i) {
                if (i && i % 4 == 0) out += ' ';
                out += digits[(m_data[i] >> 4) & 0xF];
                out += digits[m_data[i] & 0xF];
            }
            return out;
        }

        [[nodiscard]] void* data() { return m_data; }
        [[nodiscard]] bool valid() const { return m_valid; }
        [[nodiscard]] explicit operator bool() const { return m_valid; }

    private:
        // RenderTargetIdentifier's field layout has changed between Unity
        // versions, so the struct is produced by the game's own conversion
        // operator and copied out of the box rather than laid out here.
        [[nodiscard]] static RenderTargetHandle Convert(const char* paramTypeName, void* argument) {
            RenderTargetHandle handle{};

            Class klass = Class::find(IL2CPP_STR("UnityEngine.Rendering.RenderTargetIdentifier"));
            if (!klass) return handle;

            Method conversion{};
            for (auto& method : klass.get_methods()) {
                if (!method || method.param_count() != 1) continue;
                if (std::strcmp(method.name(), IL2CPP_STR("op_Implicit")) != 0) continue;

                Type param = method.get_param_type(0);
                if (!param.name() || std::strcmp(param.name(), paramTypeName) != 0) continue;

                conversion = method;
                break;
            }

            if (!conversion) return handle;

            void* params[] = { argument };
            void* boxed = MethodHandler::invoke<void*>(conversion, nullptr, params);
            if (!boxed) return handle;

            uint32_t size = klass.instance_size();
            if (size <= sizeof(il2cppObject)) return handle;

            size -= static_cast<uint32_t>(sizeof(il2cppObject));
            if (size > sizeof(m_data)) size = sizeof(m_data);

            std::memcpy(handle.m_data, IL2CPP::Unbox(boxed), size);
            handle.m_size = size;
            handle.m_valid = true;
            return handle;
        }

        alignas(16) uint8_t m_data[64]{};
        uint32_t m_size = 0;
        bool m_valid = false;

    public:
        [[nodiscard]] uint32_t size() const { return m_size; }
    };

    /// <summary>A recorded list of rendering commands that can be attached to a camera.</summary>
    class CommandBuffer : public ManagedObject {
    public:
        using ManagedObject::ManagedObject;

        /// <summary>Resolve one of CommandBuffer's overloads by its first parameter's type.</summary>
        /// <param name="firstParamType">Short type name, e.g. "RenderTargetIdentifier" or "Int32".</param>
        [[nodiscard]] static Method ResolveOverload(const char* name, int argc, const char* firstParamType) {
            Class klass = Class::find(IL2CPP_STR("UnityEngine.Rendering.CommandBuffer"));
            if (!klass) return Method{ nullptr };

            for (auto& method : klass.get_methods()) {
                if (!method || static_cast<int>(method.param_count()) != argc) continue;
                if (std::strcmp(method.name(), name) != 0) continue;

                Type param = method.get_param_type(0);
                if (!param.name() || std::strcmp(param.name(), firstParamType) != 0) continue;
                return method;
            }

            return Method{ nullptr };
        }

        /// <summary>Which of the overloads this wrapper needs actually resolved, for diagnostics.</summary>
        [[nodiscard]] static std::string ResolutionReport() {
            struct Wanted { const char* name; int argc; const char* first; };
            static const Wanted wanted[]{
                { IL2CPP_STR("Blit"), 2, IL2CPP_STR("RenderTargetIdentifier") },
                { IL2CPP_STR("Blit"), 4, IL2CPP_STR("RenderTargetIdentifier") },
                { IL2CPP_STR("SetRenderTarget"), 1, IL2CPP_STR("RenderTargetIdentifier") },
                { IL2CPP_STR("ClearRenderTarget"), 4, IL2CPP_STR("Boolean") },
                { IL2CPP_STR("ClearRenderTarget"), 3, IL2CPP_STR("Boolean") },
                { IL2CPP_STR("DrawRenderer"), 4, IL2CPP_STR("Renderer") },
                { IL2CPP_STR("SetGlobalTexture"), 2, IL2CPP_STR("Int32") },
                { IL2CPP_STR("SetGlobalVector"), 2, IL2CPP_STR("Int32") },
                { IL2CPP_STR("SetGlobalFloat"), 2, IL2CPP_STR("Int32") },
            };

            std::string report;
            for (const auto& entry : wanted) {
                if (!report.empty()) report += ", ";
                report += entry.name;
                report += '/';
                report += static_cast<char>('0' + entry.argc);
                report += ResolveOverload(entry.name, entry.argc, entry.first) ? "=ok" : "=MISS";
            }
            return report;
        }

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
            static auto m = ResolveOverload(
                IL2CPP_STR("DrawRenderer"), 4, IL2CPP_STR("Renderer"));
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
            static auto m = ResolveOverload(
                IL2CPP_STR("GetTemporaryRT"), 6, IL2CPP_STR("Int32"));
            void* params[] = { &nameId, &width, &height, &depthBuffer, &filterMode, &format };
            MethodHandler::invoke(m, raw(), params);
        }

        /// <summary>Release a target previously allocated with GetTemporaryRT.</summary>
        /// <param name="nameId">The same shader property id the target was allocated under.</param>
        void ReleaseTemporaryRT(int nameId) {
            static auto m = ResolveOverload(
                IL2CPP_STR("ReleaseTemporaryRT"), 1, IL2CPP_STR("Int32"));
            void* params[] = { &nameId };
            MethodHandler::invoke(m, raw(), params);
        }

        /// <summary>Direct subsequent draws at a render target.</summary>
        void SetRenderTarget(RenderTargetHandle target) {
            if (!target) return;
            static auto m = ResolveOverload(
                IL2CPP_STR("SetRenderTarget"), 1, IL2CPP_STR("RenderTargetIdentifier"));
            void* params[] = { target.data() };
            MethodHandler::invoke(m, raw(), params);
        }

        /// <summary>Clear the current render target.</summary>
        /// <param name="depth">Depth value to clear to, 1.0 being the far plane.</param>
        void ClearRenderTarget(bool clearDepth, bool clearColor, const Color& background, float depth = 1.0f) {
            static auto four = ResolveOverload(
                IL2CPP_STR("ClearRenderTarget"), 4, IL2CPP_STR("Boolean"));
            static auto three = ResolveOverload(
                IL2CPP_STR("ClearRenderTarget"), 3, IL2CPP_STR("Boolean"));

            Color c = background;
            if (four) {
                void* params[] = { &clearDepth, &clearColor, &c, &depth };
                MethodHandler::invoke(four, raw(), params);
                return;
            }

            if (three) {
                void* params[] = { &clearDepth, &clearColor, &c };
                MethodHandler::invoke(three, raw(), params);
            }
        }

        /// <summary>Copy source to destination, optionally through a material.</summary>
        /// <param name="material">Null for a straight copy; otherwise the shader to run.</param>
        /// <param name="pass">Pass index, or -1 for every pass.</param>
        void Blit(RenderTargetHandle source, RenderTargetHandle destination,
                  void* material = nullptr, int pass = -1) {
            if (!source || !destination) return;

            if (!material) {
                static auto simple = ResolveOverload(
                    IL2CPP_STR("Blit"), 2, IL2CPP_STR("RenderTargetIdentifier"));
                void* params[] = { source.data(), destination.data() };
                MethodHandler::invoke(simple, raw(), params);
                return;
            }

            static auto withMaterial = ResolveOverload(
                IL2CPP_STR("Blit"), 4, IL2CPP_STR("RenderTargetIdentifier"));
            void* params[] = { source.data(), destination.data(), material, &pass };
            MethodHandler::invoke(withMaterial, raw(), params);
        }

        /// <summary>Bind a render target to a global shader property.</summary>
        /// <param name="nameId">Shader property id from Shader.PropertyToID.</param>
        void SetGlobalTexture(int nameId, RenderTargetHandle target) {
            if (!target) return;
            static auto m = ResolveOverload(
                IL2CPP_STR("SetGlobalTexture"), 2, IL2CPP_STR("Int32"));
            void* params[] = { &nameId, target.data() };
            MethodHandler::invoke(m, raw(), params);
        }

        /// <summary>Set a global shader float.</summary>
        /// <param name="nameId">Shader property id from Shader.PropertyToID.</param>
        void SetGlobalFloat(int nameId, float value) {
            static auto m = ResolveOverload(
                IL2CPP_STR("SetGlobalFloat"), 2, IL2CPP_STR("Int32"));
            void* params[] = { &nameId, &value };
            MethodHandler::invoke(m, raw(), params);
        }

        /// <summary>Set a global shader vector.</summary>
        /// <param name="nameId">Shader property id from Shader.PropertyToID.</param>
        void SetGlobalVector(int nameId, const Vector4& value) {
            static auto m = ResolveOverload(
                IL2CPP_STR("SetGlobalVector"), 2, IL2CPP_STR("Int32"));
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
