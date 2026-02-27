#pragma once
#include "Component.hpp"
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
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->transform.m_GetPosition || !raw()) return Vector3{};
            Vector3 v; reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, Vector3*)>(fn->transform.m_GetPosition)(raw(), &v); return v;
        }
        void SetPosition(const Vector3& pos) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->transform.m_SetPosition || !raw()) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, const Vector3&)>(fn->transform.m_SetPosition)(raw(), pos);
        }

        [[nodiscard]] Vector3 GetLocalPosition() const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->transform.m_GetLocalPosition || !raw()) return Vector3{};
            Vector3 v; reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, Vector3*)>(fn->transform.m_GetLocalPosition)(raw(), &v); return v;
        }
        void SetLocalPosition(const Vector3& pos) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->transform.m_SetLocalPosition || !raw()) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, const Vector3&)>(fn->transform.m_SetLocalPosition)(raw(), pos);
        }

        // ---- Rotation ----
        [[nodiscard]] Quaternion GetRotation() const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->transform.m_GetRotation || !raw()) return Quaternion{};
            Quaternion q; reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, Quaternion*)>(fn->transform.m_GetRotation)(raw(), &q); return q;
        }
        void SetRotation(const Quaternion& rot) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->transform.m_SetRotation || !raw()) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, const Quaternion&)>(fn->transform.m_SetRotation)(raw(), rot);
        }

        [[nodiscard]] Quaternion GetLocalRotation() const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->transform.m_GetLocalRotation || !raw()) return Quaternion{};
            Quaternion q; reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, Quaternion*)>(fn->transform.m_GetLocalRotation)(raw(), &q); return q;
        }
        void SetLocalRotation(const Quaternion& rot) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->transform.m_SetLocalRotation || !raw()) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, const Quaternion&)>(fn->transform.m_SetLocalRotation)(raw(), rot);
        }

        // ---- Scale ----
        [[nodiscard]] Vector3 GetLocalScale() const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->transform.m_GetLocalScale || !raw()) return Vector3{};
            Vector3 v; reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, Vector3*)>(fn->transform.m_GetLocalScale)(raw(), &v); return v;
        }
        void SetLocalScale(const Vector3& scale) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->transform.m_SetLocalScale || !raw()) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, const Vector3&)>(fn->transform.m_SetLocalScale)(raw(), scale);
        }

        [[nodiscard]] Vector3 GetLossyScale() const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->transform.m_GetLossyScale || !raw()) return Vector3{};
            Vector3 v; reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, Vector3*)>(fn->transform.m_GetLossyScale)(raw(), &v); return v;
        }

        // ---- Directions ----
        [[nodiscard]] Vector3 GetForward() const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->transform.m_GetForward || !raw()) return Vector3{};
            Vector3 v; reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, Vector3*)>(fn->transform.m_GetForward)(raw(), &v); return v;
        }
        void SetForward(const Vector3& fwd) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->transform.m_SetForward || !raw()) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, const Vector3&)>(fn->transform.m_SetForward)(raw(), fwd);
        }

        [[nodiscard]] Vector3 GetRight() const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->transform.m_GetRight || !raw()) return Vector3{};
            Vector3 v; reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, Vector3*)>(fn->transform.m_GetRight)(raw(), &v); return v;
        }
        void SetRight(const Vector3& r) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->transform.m_SetRight || !raw()) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, const Vector3&)>(fn->transform.m_SetRight)(raw(), r);
        }

        [[nodiscard]] Vector3 GetUp() const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->transform.m_GetUp || !raw()) return Vector3{};
            Vector3 v; reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, Vector3*)>(fn->transform.m_GetUp)(raw(), &v); return v;
        }
        void SetUp(const Vector3& u) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->transform.m_SetUp || !raw()) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, const Vector3&)>(fn->transform.m_SetUp)(raw(), u);
        }

        // ---- Hierarchy ----
        [[nodiscard]] Transform GetParent() const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->transform.m_GetParent || !raw()) return Transform{};
            return Transform{ reinterpret_cast<void*(IL2CPP_CALLTYPE)(void*)>(fn->transform.m_GetParent)(raw()) };
        }
        void SetParent(Transform parent, bool worldPositionStays = true) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->transform.m_SetParent || !raw()) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, void*, bool)>(fn->transform.m_SetParent)(raw(), parent.raw(), worldPositionStays);
        }

        [[nodiscard]] Transform GetRoot() const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->transform.m_GetRoot || !raw()) return Transform{};
            return Transform{ reinterpret_cast<void*(IL2CPP_CALLTYPE)(void*)>(fn->transform.m_GetRoot)(raw()) };
        }

        [[nodiscard]] int GetChildCount() const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->transform.m_GetChildCount || !raw()) return 0;
            return reinterpret_cast<int(IL2CPP_CALLTYPE)(void*)>(fn->transform.m_GetChildCount)(raw());
        }

        [[nodiscard]] Transform GetChild(int index) const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->transform.m_GetChild || !raw()) return Transform{};
            return Transform{ reinterpret_cast<void*(IL2CPP_CALLTYPE)(void*, int)>(fn->transform.m_GetChild)(raw(), index) };
        }

        [[nodiscard]] int GetHierarchyCount() const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->transform.m_GetHierarchyCount || !raw()) return 0;
            return reinterpret_cast<int(IL2CPP_CALLTYPE)(void*)>(fn->transform.m_GetHierarchyCount)(raw());
        }

        [[nodiscard]] bool IsChildOf(Transform parent) const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->transform.m_IsChildOf || !raw()) return false;
            return reinterpret_cast<bool(IL2CPP_CALLTYPE)(void*, void*)>(fn->transform.m_IsChildOf)(raw(), parent.raw());
        }

        void DetachChildren() {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->transform.m_DetachChildren || !raw()) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*)>(fn->transform.m_DetachChildren)(raw());
        }

        [[nodiscard]] Transform Find(std::string_view name) const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->transform.m_Find || !raw()) return Transform{};
            auto* exports = GetExports();
            if (!exports || !exports->m_stringNew) return Transform{};
            void* il2cppStr = reinterpret_cast<void*(IL2CPP_CALLTYPE)(const char*)>(exports->m_stringNew)(
                std::string(name).c_str());
            return Transform{ reinterpret_cast<void*(IL2CPP_CALLTYPE)(void*, void*)>(fn->transform.m_Find)(raw(), il2cppStr) };
        }

        // ---- Transform operations ----
        void SetPositionAndRotation(const Vector3& pos, const Quaternion& rot) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->transform.m_SetPositionAndRotation || !raw()) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, const Vector3&, const Quaternion&)>(fn->transform.m_SetPositionAndRotation)(raw(), pos, rot);
        }

        void SetLocalPositionAndRotation(const Vector3& pos, const Quaternion& rot) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->transform.m_SetLocalPositionAndRotation || !raw()) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, const Vector3&, const Quaternion&)>(fn->transform.m_SetLocalPositionAndRotation)(raw(), pos, rot);
        }

        [[nodiscard]] Vector3 TransformDirection(const Vector3& dir) const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->transform.m_TransformDirection || !raw()) return Vector3{};
            Vector3 v; reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, const Vector3&, Vector3*)>(fn->transform.m_TransformDirection)(raw(), dir, &v); return v;
        }

        [[nodiscard]] Vector3 InverseTransformDirection(const Vector3& dir) const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->transform.m_InverseTransformDirection || !raw()) return Vector3{};
            Vector3 v; reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, const Vector3&, Vector3*)>(fn->transform.m_InverseTransformDirection)(raw(), dir, &v); return v;
        }

        [[nodiscard]] Vector3 TransformPoint(const Vector3& point) const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->transform.m_TransformPoint || !raw()) return Vector3{};
            Vector3 v; reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, const Vector3&, Vector3*)>(fn->transform.m_TransformPoint)(raw(), point, &v); return v;
        }

        // ---- Rotation Methods ----

        /// Rotate around a point in world space.
        void RotateAround(const Vector3& point, const Vector3& axis, float angle) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->transform.m_RotateAround || !raw()) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, const Vector3&, const Vector3&, float)>(fn->transform.m_RotateAround)(raw(), point, axis, angle);
        }

        /// Rotate around a point in local space.
        void RotateAroundLocal(const Vector3& point, const Vector3& axis, float angle) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->transform.m_RotateAroundLocal || !raw()) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, const Vector3&, const Vector3&, float)>(fn->transform.m_RotateAroundLocal)(raw(), point, axis, angle);
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
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->transform.m_GetWorldToLocalMatrix || !raw()) return Matrix4x4{};
            Matrix4x4 m; reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, Matrix4x4*)>(fn->transform.m_GetWorldToLocalMatrix)(raw(), &m); return m;
        }

        [[nodiscard]] Matrix4x4 GetLocalToWorldMatrix() const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->transform.m_GetLocalToWorldMatrix || !raw()) return Matrix4x4{};
            Matrix4x4 m; reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, Matrix4x4*)>(fn->transform.m_GetLocalToWorldMatrix)(raw(), &m); return m;
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
        auto* fn = GetUnityFunctions();
        if (!fn || !fn->component.m_GetTransform || !raw()) return Transform{};
        return Transform{ reinterpret_cast<void*(IL2CPP_CALLTYPE)(void*)>(fn->component.m_GetTransform)(raw()) };
    }

    inline GameObject Component::GetGameObject() const {
        auto* fn = GetUnityFunctions();
        if (!fn || !fn->component.m_GetGameObject || !raw()) return GameObject{};
        return GameObject{ reinterpret_cast<void*(IL2CPP_CALLTYPE)(void*)>(fn->component.m_GetGameObject)(raw()) };
    }

    inline Transform GameObject::GetTransform() const {
        auto* fn = GetUnityFunctions();
        if (!fn || !fn->gameObject.m_GetTransform || !raw()) return Transform{};
        return Transform{ reinterpret_cast<void*(IL2CPP_CALLTYPE)(void*)>(fn->gameObject.m_GetTransform)(raw()) };
    }

    // ---- Legacy deferred implementations ----
    inline Transform Component::get_transform() const { return GetTransform(); }
    inline GameObject Component::get_game_object() const { return GetGameObject(); }
    inline Transform GameObject::get_transform() const { return GetTransform(); }

    // ---- Object deferred implementations ----

    inline Object Object::InstantiateWithParent(Transform parent) const {
        auto* fn = GetUnityFunctions();
        if (!fn || !fn->object.m_Internal_CloneSingleWithParent || !raw()) return Object{};
        return Object{ reinterpret_cast<void*(IL2CPP_CALLTYPE)(void*, void*)>(fn->object.m_Internal_CloneSingleWithParent)(raw(), parent.raw()) };
    }

} // namespace IL2CPP::Module::Unity
