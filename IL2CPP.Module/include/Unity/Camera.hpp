#pragma once
#include "Behaviour.hpp"
#include "../MethodHandler.hpp"
#include <IL2CPP.Common/il2cpp_types.hpp>

// ============================================================================
//  IL2CPP.Module::Unity::Camera
// ============================================================================

namespace IL2CPP::Module::Unity {

    class Camera : public Behaviour {
    public:
        using Behaviour::Behaviour;

        [[nodiscard]] static Camera GetMain() {
            static auto m = MethodHandler::resolve("UnityEngine.Camera", "get_main", 0);
            return Camera{ MethodHandler::invoke<void*>(m, nullptr) };
        }

        [[nodiscard]] static Camera GetCurrent() {
            static auto m = MethodHandler::resolve("UnityEngine.Camera", "get_current", 0);
            return Camera{ MethodHandler::invoke<void*>(m, nullptr) };
        }

        [[nodiscard]] Vector3 WorldToScreenPoint(const Vector3& worldPos) const {
            static auto m = MethodHandler::resolve("UnityEngine.Camera", "WorldToScreenPoint", 1);
            Vector3 v = worldPos;
            void* params[] = { &v };
            return MethodHandler::invoke<Vector3>(m, raw(), params);
        }

        [[nodiscard]] Matrix4x4 GetWorldToCameraMatrix() const {
            static auto m = MethodHandler::resolve("UnityEngine.Camera", "get_worldToCameraMatrix", 0);
            return MethodHandler::invoke<Matrix4x4>(m, raw());
        }

        [[nodiscard]] Matrix4x4 GetProjectionMatrix() const {
            static auto m = MethodHandler::resolve("UnityEngine.Camera", "get_projectionMatrix", 0);
            return MethodHandler::invoke<Matrix4x4>(m, raw());
        }

        // ---- Field of View ----
        [[nodiscard]] float GetFieldOfView() const {
            static auto m = MethodHandler::resolve("UnityEngine.Camera", "get_fieldOfView", 0);
            return MethodHandler::invoke<float>(m, raw());
        }
        void SetFieldOfView(float fov) {
            static auto m = MethodHandler::resolve("UnityEngine.Camera", "set_fieldOfView", 1);
            void* params[] = { &fov };
            MethodHandler::invoke(m, raw(), params);
        }

        // ---- Clip Planes ----
        [[nodiscard]] float GetNearClipPlane() const {
            static auto m = MethodHandler::resolve("UnityEngine.Camera", "get_nearClipPlane", 0);
            return MethodHandler::invoke<float>(m, raw());
        }
        void SetNearClipPlane(float nearClip) {
            static auto m = MethodHandler::resolve("UnityEngine.Camera", "set_nearClipPlane", 1);
            void* params[] = { &nearClip };
            MethodHandler::invoke(m, raw(), params);
        }

        [[nodiscard]] float GetFarClipPlane() const {
            static auto m = MethodHandler::resolve("UnityEngine.Camera", "get_farClipPlane", 0);
            return MethodHandler::invoke<float>(m, raw());
        }
        void SetFarClipPlane(float farClip) {
            static auto m = MethodHandler::resolve("UnityEngine.Camera", "set_farClipPlane", 1);
            void* params[] = { &farClip };
            MethodHandler::invoke(m, raw(), params);
        }

        // ---- Orthographic ----
        [[nodiscard]] bool GetOrthographic() const {
            static auto m = MethodHandler::resolve("UnityEngine.Camera", "get_orthographic", 0);
            return MethodHandler::invoke<bool>(m, raw());
        }
        void SetOrthographic(bool ortho) {
            static auto m = MethodHandler::resolve("UnityEngine.Camera", "set_orthographic", 1);
            void* params[] = { &ortho };
            MethodHandler::invoke(m, raw(), params);
        }

        [[nodiscard]] float GetOrthographicSize() const {
            static auto m = MethodHandler::resolve("UnityEngine.Camera", "get_orthographicSize", 0);
            return MethodHandler::invoke<float>(m, raw());
        }
        void SetOrthographicSize(float size) {
            static auto m = MethodHandler::resolve("UnityEngine.Camera", "set_orthographicSize", 1);
            void* params[] = { &size };
            MethodHandler::invoke(m, raw(), params);
        }

        // ---- Depth ----
        [[nodiscard]] float GetDepth() const {
            static auto m = MethodHandler::resolve("UnityEngine.Camera", "get_depth", 0);
            return MethodHandler::invoke<float>(m, raw());
        }
        void SetDepth(float depth) {
            static auto m = MethodHandler::resolve("UnityEngine.Camera", "set_depth", 1);
            void* params[] = { &depth };
            MethodHandler::invoke(m, raw(), params);
        }

        // ---- Culling Mask ----
        [[nodiscard]] int GetCullingMask() const {
            static auto m = MethodHandler::resolve("UnityEngine.Camera", "get_cullingMask", 0);
            return MethodHandler::invoke<int>(m, raw());
        }
        void SetCullingMask(int mask) {
            static auto m = MethodHandler::resolve("UnityEngine.Camera", "set_cullingMask", 1);
            void* params[] = { &mask };
            MethodHandler::invoke(m, raw(), params);
        }
        void SetCullingMask(LayerMask mask) { SetCullingMask(mask.value()); }

        // ---- Viewport Rect ----
        [[nodiscard]] Rect GetPixelRect() const {
            static auto m = MethodHandler::resolve("UnityEngine.Camera", "get_pixelRect", 0);
            return MethodHandler::invoke<Rect>(m, raw());
        }

        [[nodiscard]] Rect GetRect() const {
            static auto m = MethodHandler::resolve("UnityEngine.Camera", "get_rect", 0);
            return MethodHandler::invoke<Rect>(m, raw());
        }
        void SetRect(const Rect& rect) {
            static auto m = MethodHandler::resolve("UnityEngine.Camera", "set_rect", 1);
            Rect r = rect;
            void* params[] = { &r };
            MethodHandler::invoke(m, raw(), params);
        }

        // ---- Screen/Viewport Conversions ----
        [[nodiscard]] Vector3 ScreenToWorldPoint(const Vector3& screenPos) const {
            static auto m = MethodHandler::resolve("UnityEngine.Camera", "ScreenToWorldPoint", 1);
            Vector3 v = screenPos;
            void* params[] = { &v };
            return MethodHandler::invoke<Vector3>(m, raw(), params);
        }

        [[nodiscard]] Ray ScreenPointToRay(const Vector3& screenPos) const {
            static auto m = MethodHandler::resolve("UnityEngine.Camera", "ScreenPointToRay", 1);
            Vector3 v = screenPos;
            void* params[] = { &v };
            return MethodHandler::invoke<Ray>(m, raw(), params);
        }

        [[nodiscard]] Vector3 ViewportToWorldPoint(const Vector3& viewportPos) const {
            static auto m = MethodHandler::resolve("UnityEngine.Camera", "ViewportToWorldPoint", 1);
            Vector3 v = viewportPos;
            void* params[] = { &v };
            return MethodHandler::invoke<Vector3>(m, raw(), params);
        }

        [[nodiscard]] Vector3 WorldToViewportPoint(const Vector3& worldPos) const {
            static auto m = MethodHandler::resolve("UnityEngine.Camera", "WorldToViewportPoint", 1);
            Vector3 v = worldPos;
            void* params[] = { &v };
            return MethodHandler::invoke<Vector3>(m, raw(), params);
        }

        // ---- Static: All Cameras ----
        [[nodiscard]] static int GetAllCamerasCount() {
            static auto m = MethodHandler::resolve("UnityEngine.Camera", "get_allCamerasCount", 0);
            return MethodHandler::invoke<int>(m, nullptr);
        }

        // ---- Utility Methods ----

        [[nodiscard]] bool IsWorldPointVisible(const Vector3& worldPos, float screenWidth, float screenHeight) const {
            Vector3 screenPoint = WorldToScreenPoint(worldPos);
            return screenPoint.z > 0.f &&
                   screenPoint.x >= 0.f && screenPoint.x <= screenWidth &&
                   screenPoint.y >= 0.f && screenPoint.y <= screenHeight;
        }

        [[nodiscard]] Matrix4x4 GetViewMatrix() const { return GetWorldToCameraMatrix(); }

        [[nodiscard]] Matrix4x4 GetViewProjectionMatrix() const {
            Matrix4x4 view = GetWorldToCameraMatrix();
            Matrix4x4 proj = GetProjectionMatrix();
            Matrix4x4 result;
            for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++) {
                    result[i][j] = 0.f;
                    for (int k = 0; k < 4; k++)
                        result[i][j] += proj[i][k] * view[k][j];
                }
            return result;
        }

        // ---- Legacy snake_case aliases (deprecated) ----
        [[deprecated("Use GetMain()")]] [[nodiscard]] static Camera get_main() { return GetMain(); }
        [[deprecated("Use GetCurrent()")]] [[nodiscard]] static Camera get_current() { return GetCurrent(); }
        [[deprecated("Use WorldToScreenPoint()")]] [[nodiscard]] Vector3 world_to_screen_point(const Vector3& p) const { return WorldToScreenPoint(p); }
        [[deprecated("Use GetWorldToCameraMatrix()")]] [[nodiscard]] Matrix4x4 get_world_to_camera_matrix() const { return GetWorldToCameraMatrix(); }
        [[deprecated("Use GetProjectionMatrix()")]] [[nodiscard]] Matrix4x4 get_projection_matrix() const { return GetProjectionMatrix(); }
        [[deprecated("Use GetFieldOfView()")]] [[nodiscard]] float get_field_of_view() const { return GetFieldOfView(); }
        [[deprecated("Use SetFieldOfView()")]] void set_field_of_view(float f) { SetFieldOfView(f); }
        [[deprecated("Use GetNearClipPlane()")]] [[nodiscard]] float get_near_clip_plane() const { return GetNearClipPlane(); }
        [[deprecated("Use SetNearClipPlane()")]] void set_near_clip_plane(float n) { SetNearClipPlane(n); }
        [[deprecated("Use GetFarClipPlane()")]] [[nodiscard]] float get_far_clip_plane() const { return GetFarClipPlane(); }
        [[deprecated("Use SetFarClipPlane()")]] void set_far_clip_plane(float f) { SetFarClipPlane(f); }
    };

} // namespace IL2CPP::Module::Unity
