#pragma once
#include "Component.hpp"
#include "../MethodHandler.hpp"
#include <IL2CPP.Common/il2cpp_types.hpp>
#include <IL2CPP.Common/il2cpp_shared.hpp>

// ============================================================================
//  IL2CPP.Module::Unity::Transform
// ============================================================================

namespace IL2CPP::Module::Unity {

    class Transform : public Component {
    public:
        using Component::Component;

        // ---- Position ----
        [[nodiscard]] Vector3 GetPosition() const {
            static auto m = MethodHandler::resolve("UnityEngine.Transform", "get_position", 0);
            return MethodHandler::invoke<Vector3>(m, raw());
        }
        void SetPosition(const Vector3& pos) {
            static auto m = MethodHandler::resolve("UnityEngine.Transform", "set_position", 1);
            Vector3 p = pos;
            void* params[] = { &p };
            MethodHandler::invoke(m, raw(), params);
        }

        [[nodiscard]] Vector3 GetLocalPosition() const {
            static auto m = MethodHandler::resolve("UnityEngine.Transform", "get_localPosition", 0);
            return MethodHandler::invoke<Vector3>(m, raw());
        }
        void SetLocalPosition(const Vector3& pos) {
            static auto m = MethodHandler::resolve("UnityEngine.Transform", "set_localPosition", 1);
            Vector3 p = pos;
            void* params[] = { &p };
            MethodHandler::invoke(m, raw(), params);
        }

        // ---- Rotation ----
        [[nodiscard]] Quaternion GetRotation() const {
            static auto m = MethodHandler::resolve("UnityEngine.Transform", "get_rotation", 0);
            return MethodHandler::invoke<Quaternion>(m, raw());
        }
        void SetRotation(const Quaternion& rot) {
            static auto m = MethodHandler::resolve("UnityEngine.Transform", "set_rotation", 1);
            Quaternion r = rot;
            void* params[] = { &r };
            MethodHandler::invoke(m, raw(), params);
        }

        [[nodiscard]] Quaternion GetLocalRotation() const {
            static auto m = MethodHandler::resolve("UnityEngine.Transform", "get_localRotation", 0);
            return MethodHandler::invoke<Quaternion>(m, raw());
        }
        void SetLocalRotation(const Quaternion& rot) {
            static auto m = MethodHandler::resolve("UnityEngine.Transform", "set_localRotation", 1);
            Quaternion r = rot;
            void* params[] = { &r };
            MethodHandler::invoke(m, raw(), params);
        }

        // ---- Scale ----
        [[nodiscard]] Vector3 GetLocalScale() const {
            static auto m = MethodHandler::resolve("UnityEngine.Transform", "get_localScale", 0);
            return MethodHandler::invoke<Vector3>(m, raw());
        }
        void SetLocalScale(const Vector3& scale) {
            static auto m = MethodHandler::resolve("UnityEngine.Transform", "set_localScale", 1);
            Vector3 s = scale;
            void* params[] = { &s };
            MethodHandler::invoke(m, raw(), params);
        }

        [[nodiscard]] Vector3 GetLossyScale() const {
            static auto m = MethodHandler::resolve("UnityEngine.Transform", "get_lossyScale", 0);
            return MethodHandler::invoke<Vector3>(m, raw());
        }

        // ---- Directions ----
        [[nodiscard]] Vector3 GetForward() const {
            static auto m = MethodHandler::resolve("UnityEngine.Transform", "get_forward", 0);
            return MethodHandler::invoke<Vector3>(m, raw());
        }
        void SetForward(const Vector3& fwd) {
            static auto m = MethodHandler::resolve("UnityEngine.Transform", "set_forward", 1);
            Vector3 f = fwd;
            void* params[] = { &f };
            MethodHandler::invoke(m, raw(), params);
        }

        [[nodiscard]] Vector3 GetRight() const {
            static auto m = MethodHandler::resolve("UnityEngine.Transform", "get_right", 0);
            return MethodHandler::invoke<Vector3>(m, raw());
        }
        void SetRight(const Vector3& r) {
            static auto m = MethodHandler::resolve("UnityEngine.Transform", "set_right", 1);
            Vector3 rv = r;
            void* params[] = { &rv };
            MethodHandler::invoke(m, raw(), params);
        }

        [[nodiscard]] Vector3 GetUp() const {
            static auto m = MethodHandler::resolve("UnityEngine.Transform", "get_up", 0);
            return MethodHandler::invoke<Vector3>(m, raw());
        }
        void SetUp(const Vector3& u) {
            static auto m = MethodHandler::resolve("UnityEngine.Transform", "set_up", 1);
            Vector3 uv = u;
            void* params[] = { &uv };
            MethodHandler::invoke(m, raw(), params);
        }

        // ---- Hierarchy ----
        [[nodiscard]] Transform GetParent() const {
            static auto m = MethodHandler::resolve("UnityEngine.Transform", "get_parent", 0);
            return Transform{ MethodHandler::invoke<void*>(m, raw()) };
        }
        void SetParent(Transform parent, bool worldPositionStays = true) {
            static auto m = MethodHandler::resolve("UnityEngine.Transform", "SetParent", 2);
            void* p = parent.raw();
            void* params[] = { p, &worldPositionStays };
            MethodHandler::invoke(m, raw(), params);
        }

        [[nodiscard]] Transform GetRoot() const {
            static auto m = MethodHandler::resolve("UnityEngine.Transform", "get_root", 0);
            return Transform{ MethodHandler::invoke<void*>(m, raw()) };
        }

        [[nodiscard]] int GetChildCount() const {
            static auto m = MethodHandler::resolve("UnityEngine.Transform", "get_childCount", 0);
            return MethodHandler::invoke<int>(m, raw());
        }

        [[nodiscard]] Transform GetChild(int index) const {
            static auto m = MethodHandler::resolve("UnityEngine.Transform", "GetChild", 1);
            void* params[] = { &index };
            return Transform{ MethodHandler::invoke<void*>(m, raw(), params) };
        }

        [[nodiscard]] int GetHierarchyCount() const {
            static auto m = MethodHandler::resolve("UnityEngine.Transform", "get_hierarchyCount", 0);
            return MethodHandler::invoke<int>(m, raw());
        }

        [[nodiscard]] bool IsChildOf(Transform parent) const {
            static auto m = MethodHandler::resolve("UnityEngine.Transform", "IsChildOf", 1);
            void* p = parent.raw();
            void* params[] = { p };
            return MethodHandler::invoke<bool>(m, raw(), params);
        }

        void DetachChildren() {
            static auto m = MethodHandler::resolve("UnityEngine.Transform", "DetachChildren", 0);
            MethodHandler::invoke(m, raw());
        }

        [[nodiscard]] Transform Find(std::string_view name) const {
            static auto m = MethodHandler::resolve("UnityEngine.Transform", "Find", 1);
            auto* exports = GetExports();
            if (!exports || !exports->m_stringNew) return Transform{};
            void* il2cppStr = reinterpret_cast<void*(IL2CPP_CALLTYPE)(const char*)>(exports->m_stringNew)(
                std::string(name).c_str());
            void* params[] = { il2cppStr };
            return Transform{ MethodHandler::invoke<void*>(m, raw(), params) };
        }

        // ---- Transform operations ----
        void SetPositionAndRotation(const Vector3& pos, const Quaternion& rot) {
            static auto m = MethodHandler::resolve("UnityEngine.Transform", "SetPositionAndRotation", 2);
            Vector3 p = pos;
            Quaternion r = rot;
            void* params[] = { &p, &r };
            MethodHandler::invoke(m, raw(), params);
        }

        void SetLocalPositionAndRotation(const Vector3& pos, const Quaternion& rot) {
            static auto m = MethodHandler::resolve("UnityEngine.Transform", "SetLocalPositionAndRotation", 2);
            Vector3 p = pos;
            Quaternion r = rot;
            void* params[] = { &p, &r };
            MethodHandler::invoke(m, raw(), params);
        }

        [[nodiscard]] Vector3 TransformDirection(const Vector3& dir) const {
            static auto m = MethodHandler::resolve("UnityEngine.Transform", "TransformDirection", 1);
            Vector3 d = dir;
            void* params[] = { &d };
            return MethodHandler::invoke<Vector3>(m, raw(), params);
        }

        [[nodiscard]] Vector3 InverseTransformDirection(const Vector3& dir) const {
            static auto m = MethodHandler::resolve("UnityEngine.Transform", "InverseTransformDirection", 1);
            Vector3 d = dir;
            void* params[] = { &d };
            return MethodHandler::invoke<Vector3>(m, raw(), params);
        }

        [[nodiscard]] Vector3 TransformPoint(const Vector3& point) const {
            static auto m = MethodHandler::resolve("UnityEngine.Transform", "TransformPoint", 1);
            Vector3 p = point;
            void* params[] = { &p };
            return MethodHandler::invoke<Vector3>(m, raw(), params);
        }

        // ---- Rotation Methods ----

        /// Rotate around a point in world space.
        void RotateAround(const Vector3& point, const Vector3& axis, float angle) {
            static auto m = MethodHandler::resolve("UnityEngine.Transform", "RotateAround", 3);
            Vector3 p = point;
            Vector3 a = axis;
            void* params[] = { &p, &a, &angle };
            MethodHandler::invoke(m, raw(), params);
        }

        /// Rotate around a point in local space.
        void RotateAroundLocal(const Vector3& point, const Vector3& axis, float angle) {
            static auto m = MethodHandler::resolve("UnityEngine.Transform", "RotateAroundLocal", 3);
            Vector3 p = point;
            Vector3 a = axis;
            void* params[] = { &p, &a, &angle };
            MethodHandler::invoke(m, raw(), params);
        }

        // ---- Utility Methods (client-side implementation) ----

        /// Make the transform look at a target position.
        void LookAt(const Vector3& worldPosition, const Vector3& worldUp = Vector3(0, 1, 0)) {
            Vector3 dir = worldPosition - GetPosition();
            if (dir.SqrMagnitude() < 0.0001f) return;
            dir.NormalizeInPlace();
            Quaternion rot;
            rot = rot.Euler(Vector3(
                std::atan2(-dir.y, std::sqrt(dir.x * dir.x + dir.z * dir.z)) * RAD2DEG,
                std::atan2(dir.x, dir.z) * RAD2DEG,
                0.f
            ));
            SetRotation(rot);
        }

        /// Make the transform look at another transform's position.
        void LookAt(Transform target, const Vector3& worldUp = Vector3(0, 1, 0)) {
            if (!target) return;
            LookAt(target.GetPosition(), worldUp);
        }

        /// Rotate the transform by euler angles (degrees).
        void Rotate(const Vector3& eulers, Space relativeTo = Space::Self) {
            Quaternion deltaRot;
            deltaRot = deltaRot.Euler(eulers);
            if (relativeTo == Space::Self) {
                SetLocalRotation(GetLocalRotation() * deltaRot);
            } else {
                SetRotation(deltaRot * GetRotation());
            }
        }

        /// Rotate the transform around an axis by an angle (degrees).
        void Rotate(const Vector3& axis, float angle, Space relativeTo = Space::Self) {
            float halfAngle = angle * DEG2RAD * 0.5f;
            float s = std::sin(halfAngle);
            Quaternion deltaRot(axis.x * s, axis.y * s, axis.z * s, std::cos(halfAngle));
            if (relativeTo == Space::Self) {
                SetLocalRotation(GetLocalRotation() * deltaRot);
            } else {
                SetRotation(deltaRot * GetRotation());
            }
        }

        /// Translate the transform by a vector.
        void Translate(const Vector3& translation, Space relativeTo = Space::Self) {
            if (relativeTo == Space::Self) {
                Vector3 worldTranslation = TransformDirection(translation);
                SetPosition(GetPosition() + worldTranslation);
            } else {
                SetPosition(GetPosition() + translation);
            }
        }

        /// Translate relative to another transform.
        void Translate(const Vector3& translation, Transform relativeTo) {
            if (relativeTo) {
                Vector3 worldTranslation = relativeTo.TransformDirection(translation);
                SetPosition(GetPosition() + worldTranslation);
            } else {
                SetPosition(GetPosition() + translation);
            }
        }

        // ---- Matrices ----
        [[nodiscard]] Matrix4x4 GetWorldToLocalMatrix() const {
            static auto m = MethodHandler::resolve("UnityEngine.Transform", "get_worldToLocalMatrix", 0);
            return MethodHandler::invoke<Matrix4x4>(m, raw());
        }

        [[nodiscard]] Matrix4x4 GetLocalToWorldMatrix() const {
            static auto m = MethodHandler::resolve("UnityEngine.Transform", "get_localToWorldMatrix", 0);
            return MethodHandler::invoke<Matrix4x4>(m, raw());
        }

        // ---- Legacy snake_case aliases (deprecated) ----
        [[deprecated("Use GetPosition()")]] [[nodiscard]] Vector3 get_position() const { return GetPosition(); }
        [[deprecated("Use SetPosition()")]] void set_position(const Vector3& p) { SetPosition(p); }
        [[deprecated("Use GetLocalPosition()")]] [[nodiscard]] Vector3 get_local_position() const { return GetLocalPosition(); }
        [[deprecated("Use SetLocalPosition()")]] void set_local_position(const Vector3& p) { SetLocalPosition(p); }
        [[deprecated("Use GetRotation()")]] [[nodiscard]] Quaternion get_rotation() const { return GetRotation(); }
        [[deprecated("Use SetRotation()")]] void set_rotation(const Quaternion& r) { SetRotation(r); }
        [[deprecated("Use GetLocalRotation()")]] [[nodiscard]] Quaternion get_local_rotation() const { return GetLocalRotation(); }
        [[deprecated("Use SetLocalRotation()")]] void set_local_rotation(const Quaternion& r) { SetLocalRotation(r); }
        [[deprecated("Use GetLocalScale()")]] [[nodiscard]] Vector3 get_local_scale() const { return GetLocalScale(); }
        [[deprecated("Use SetLocalScale()")]] void set_local_scale(const Vector3& s) { SetLocalScale(s); }
        [[deprecated("Use GetLossyScale()")]] [[nodiscard]] Vector3 get_lossy_scale() const { return GetLossyScale(); }
        [[deprecated("Use GetForward()")]] [[nodiscard]] Vector3 get_forward() const { return GetForward(); }
        [[deprecated("Use SetForward()")]] void set_forward(const Vector3& f) { SetForward(f); }
        [[deprecated("Use GetRight()")]] [[nodiscard]] Vector3 get_right() const { return GetRight(); }
        [[deprecated("Use SetRight()")]] void set_right(const Vector3& r) { SetRight(r); }
        [[deprecated("Use GetUp()")]] [[nodiscard]] Vector3 get_up() const { return GetUp(); }
        [[deprecated("Use SetUp()")]] void set_up(const Vector3& u) { SetUp(u); }
        [[deprecated("Use GetParent()")]] [[nodiscard]] Transform get_parent() const { return GetParent(); }
        [[deprecated("Use SetParent()")]] void set_parent(Transform p, bool w = true) { SetParent(p, w); }
        [[deprecated("Use GetRoot()")]] [[nodiscard]] Transform get_root() const { return GetRoot(); }
        [[deprecated("Use GetChildCount()")]] [[nodiscard]] int get_child_count() const { return GetChildCount(); }
        [[deprecated("Use GetChild()")]] [[nodiscard]] Transform get_child(int i) const { return GetChild(i); }
        [[deprecated("Use GetHierarchyCount()")]] [[nodiscard]] int get_hierarchy_count() const { return GetHierarchyCount(); }
        [[deprecated("Use IsChildOf()")]] [[nodiscard]] bool is_child_of(Transform p) const { return IsChildOf(p); }
        [[deprecated("Use DetachChildren()")]] void detach_children() { DetachChildren(); }
        [[deprecated("Use Find()")]] [[nodiscard]] Transform find(std::string_view n) const { return Find(n); }
    };

    // ---- Deferred implementations requiring Transform ----

    inline Transform Component::GetTransform() const {
        static auto m = MethodHandler::resolve("UnityEngine.Component", "get_transform", 0);
        return Transform{ MethodHandler::invoke<void*>(m, raw()) };
    }

    inline GameObject Component::GetGameObject() const {
        static auto m = MethodHandler::resolve("UnityEngine.Component", "get_gameObject", 0);
        return GameObject{ MethodHandler::invoke<void*>(m, raw()) };
    }

    inline Transform GameObject::GetTransform() const {
        static auto m = MethodHandler::resolve("UnityEngine.GameObject", "get_transform", 0);
        return Transform{ MethodHandler::invoke<void*>(m, raw()) };
    }

    // ---- Legacy deferred implementations ----
    inline Transform Component::get_transform() const { return GetTransform(); }
    inline GameObject Component::get_game_object() const { return GetGameObject(); }
    inline Transform GameObject::get_transform() const { return GetTransform(); }

    // ---- Object deferred implementations ----

    inline Object Object::InstantiateWithParent(Transform parent, bool WorldPositionStays) const {
        static auto m = MethodHandler::resolve("UnityEngine.Object", "Internal_CloneSingleWithParent", 3);
        void* self = raw();
        void* p = parent.raw();
		bool wps = WorldPositionStays;
        void* params[] = { self, p, &wps };
        return Object{ MethodHandler::invoke<void*>(m, nullptr, params) };
    }

} // namespace IL2CPP::Module::Unity
