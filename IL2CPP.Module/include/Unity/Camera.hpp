#pragma once
#include "Behaviour.hpp"
#include <IL2CPP.Common/il2cpp_types.hpp>
#include <IL2CPP.Common/il2cpp_shared.hpp>

// ============================================================================
//  IL2CPP.Module::Unity::Camera
// ============================================================================

namespace IL2CPP::Module::Unity {

    class Camera : public Behaviour {
    public:
        using Behaviour::Behaviour;

        [[nodiscard]] static Camera GetMain() {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->camera.m_GetMain) return Camera{};
            return Camera{ reinterpret_cast<void*(IL2CPP_CALLTYPE)()>(fn->camera.m_GetMain)() };
        }

        [[nodiscard]] static Camera GetCurrent() {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->camera.m_GetCurrent) return Camera{};
            return Camera{ reinterpret_cast<void*(IL2CPP_CALLTYPE)()>(fn->camera.m_GetCurrent)() };
        }

        [[nodiscard]] Vector3 WorldToScreenPoint(const Vector3& worldPos) const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->camera.m_WorldToScreenPoint || !raw()) return Vector3{};
            Vector3 v;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, const Vector3, int, Vector3&)>(fn->camera.m_WorldToScreenPoint)(raw(), worldPos, 2, v);
            return v;
        }

        [[nodiscard]] Matrix4x4 GetWorldToCameraMatrix() const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->camera.m_GetWorldToCameraMatrix || !raw()) return Matrix4x4{};
            Matrix4x4 m;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, Matrix4x4&)>(fn->camera.m_GetWorldToCameraMatrix)(raw(), m);
            return m;
        }

        [[nodiscard]] Matrix4x4 GetProjectionMatrix() const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->camera.m_GetProjectionMatrix || !raw()) return Matrix4x4{};
            Matrix4x4 m;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, Matrix4x4&)>(fn->camera.m_GetProjectionMatrix)(raw(), m);
            return m;
        }

        // ---- Field of View ----
        [[nodiscard]] float GetFieldOfView() const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->camera.m_GetFieldOfView || !raw()) return 60.f;
            return reinterpret_cast<float(IL2CPP_CALLTYPE)(void*)>(fn->camera.m_GetFieldOfView)(raw());
        }
        void SetFieldOfView(float fov) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->camera.m_SetFieldOfView || !raw()) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, float)>(fn->camera.m_SetFieldOfView)(raw(), fov);
        }

        // ---- Clip Planes ----
        [[nodiscard]] float GetNearClipPlane() const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->camera.m_GetNearClipPlane || !raw()) return 0.3f;
            return reinterpret_cast<float(IL2CPP_CALLTYPE)(void*)>(fn->camera.m_GetNearClipPlane)(raw());
        }
        void SetNearClipPlane(float nearClip) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->camera.m_SetNearClipPlane || !raw()) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, float)>(fn->camera.m_SetNearClipPlane)(raw(), nearClip);
        }

        [[nodiscard]] float GetFarClipPlane() const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->camera.m_GetFarClipPlane || !raw()) return 1000.f;
            return reinterpret_cast<float(IL2CPP_CALLTYPE)(void*)>(fn->camera.m_GetFarClipPlane)(raw());
        }
        void SetFarClipPlane(float farClip) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->camera.m_SetFarClipPlane || !raw()) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, float)>(fn->camera.m_SetFarClipPlane)(raw(), farClip);
        }

        // ---- Orthographic ----
        [[nodiscard]] bool GetOrthographic() const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->camera.m_GetOrthographic || !raw()) return false;
            return reinterpret_cast<bool(IL2CPP_CALLTYPE)(void*)>(fn->camera.m_GetOrthographic)(raw());
        }
        void SetOrthographic(bool ortho) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->camera.m_SetOrthographic || !raw()) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, bool)>(fn->camera.m_SetOrthographic)(raw(), ortho);
        }

        [[nodiscard]] float GetOrthographicSize() const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->camera.m_GetOrthographicSize || !raw()) return 5.f;
            return reinterpret_cast<float(IL2CPP_CALLTYPE)(void*)>(fn->camera.m_GetOrthographicSize)(raw());
        }
        void SetOrthographicSize(float size) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->camera.m_SetOrthographicSize || !raw()) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, float)>(fn->camera.m_SetOrthographicSize)(raw(), size);
        }

        // ---- Depth ----
        [[nodiscard]] float GetDepth() const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->camera.m_GetDepth || !raw()) return 0.f;
            return reinterpret_cast<float(IL2CPP_CALLTYPE)(void*)>(fn->camera.m_GetDepth)(raw());
        }
        void SetDepth(float depth) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->camera.m_SetDepth || !raw()) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, float)>(fn->camera.m_SetDepth)(raw(), depth);
        }

        // ---- Culling Mask ----
        [[nodiscard]] int GetCullingMask() const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->camera.m_GetCullingMask || !raw()) return -1;
            return reinterpret_cast<int(IL2CPP_CALLTYPE)(void*)>(fn->camera.m_GetCullingMask)(raw());
        }
        void SetCullingMask(int mask) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->camera.m_SetCullingMask || !raw()) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, int)>(fn->camera.m_SetCullingMask)(raw(), mask);
        }
        void SetCullingMask(LayerMask mask) {
            SetCullingMask(mask.value());
        }

        // ---- Viewport Rect ----
        [[nodiscard]] Rect GetPixelRect() const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->camera.m_GetPixelRect || !raw()) return Rect{};
            Rect r;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, Rect*)>(fn->camera.m_GetPixelRect)(raw(), &r);
            return r;
        }

        [[nodiscard]] Rect GetRect() const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->camera.m_GetRect || !raw()) return Rect{};
            Rect r;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, Rect*)>(fn->camera.m_GetRect)(raw(), &r);
            return r;
        }
        void SetRect(const Rect& rect) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->camera.m_SetRect || !raw()) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, const Rect&)>(fn->camera.m_SetRect)(raw(), rect);
        }

        // ---- Screen/Viewport Conversions ----
        [[nodiscard]] Vector3 ScreenToWorldPoint(const Vector3& screenPos) const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->camera.m_ScreenToWorldPoint || !raw()) return Vector3{};
            Vector3 v;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, const Vector3&, Vector3*)>(fn->camera.m_ScreenToWorldPoint)(raw(), screenPos, &v);
            return v;
        }

        [[nodiscard]] Ray ScreenPointToRay(const Vector3& screenPos) const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->camera.m_ScreenPointToRay || !raw()) return Ray{};
            Ray r;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, const Vector3&, Ray*)>(fn->camera.m_ScreenPointToRay)(raw(), screenPos, &r);
            return r;
        }

        [[nodiscard]] Vector3 ViewportToWorldPoint(const Vector3& viewportPos) const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->camera.m_ViewportToWorldPoint || !raw()) return Vector3{};
            Vector3 v;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, const Vector3&, Vector3*)>(fn->camera.m_ViewportToWorldPoint)(raw(), viewportPos, &v);
            return v;
        }

        [[nodiscard]] Vector3 WorldToViewportPoint(const Vector3& worldPos) const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->camera.m_WorldToViewportPoint || !raw()) return Vector3{};
            Vector3 v;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, const Vector3&, Vector3*)>(fn->camera.m_WorldToViewportPoint)(raw(), worldPos, &v);
            return v;
        }

        // ---- Static: All Cameras ----
        [[nodiscard]] static int GetAllCamerasCount() {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->camera.m_GetAllCamerasCount) return 0;
            return reinterpret_cast<int(IL2CPP_CALLTYPE)()>(fn->camera.m_GetAllCamerasCount)();
        }

        // ---- Utility Methods ----

        /// Check if a world point is within the camera's view frustum (simplified check).
        [[nodiscard]] bool IsWorldPointVisible(const Vector3& worldPos, float screenWidth, float screenHeight) const {
            Vector3 screenPoint = WorldToScreenPoint(worldPos);
            return screenPoint.z > 0.f &&
                   screenPoint.x >= 0.f && screenPoint.x <= screenWidth &&
                   screenPoint.y >= 0.f && screenPoint.y <= screenHeight;
        }

        /// Get the view matrix (same as GetWorldToCameraMatrix).
        [[nodiscard]] Matrix4x4 GetViewMatrix() const {
            return GetWorldToCameraMatrix();
        }

        /// Get combined view-projection matrix.
        [[nodiscard]] Matrix4x4 GetViewProjectionMatrix() const {
            Matrix4x4 view = GetWorldToCameraMatrix();
            Matrix4x4 proj = GetProjectionMatrix();
            Matrix4x4 result;
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    result[i][j] = 0.f;
                    for (int k = 0; k < 4; k++) {
                        result[i][j] += proj[i][k] * view[k][j];
                    }
                }
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
