#pragma once
#include "Component.hpp"
#include <IL2CPP.Common/il2cpp_types.hpp>
#include <IL2CPP.Common/il2cpp_shared.hpp>

// ============================================================================
//  IL2CPP.Module::Unity::Rigidbody
// ============================================================================

namespace IL2CPP::Module::Unity {

    class Rigidbody : public Component {
    public:
        using Component::Component;

        // ---- Velocity ----
        [[nodiscard]] Vector3 GetVelocity() const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->rigidbody.m_GetVelocity || !raw()) return Vector3{};
            Vector3 v; reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, Vector3*)>(fn->rigidbody.m_GetVelocity)(raw(), &v); return v;
        }
        void SetVelocity(const Vector3& vel) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->rigidbody.m_SetVelocity || !raw()) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, const Vector3&)>(fn->rigidbody.m_SetVelocity)(raw(), vel);
        }

        [[nodiscard]] Vector3 GetAngularVelocity() const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->rigidbody.m_GetAngularVelocity || !raw()) return Vector3{};
            Vector3 v; reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, Vector3*)>(fn->rigidbody.m_GetAngularVelocity)(raw(), &v); return v;
        }
        void SetAngularVelocity(const Vector3& vel) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->rigidbody.m_SetAngularVelocity || !raw()) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, const Vector3&)>(fn->rigidbody.m_SetAngularVelocity)(raw(), vel);
        }

        // ---- Mass / Drag ----
        [[nodiscard]] float GetMass() const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->rigidbody.m_GetMass || !raw()) return 0.f;
            return reinterpret_cast<float(IL2CPP_CALLTYPE)(void*)>(fn->rigidbody.m_GetMass)(raw());
        }
        void SetMass(float mass) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->rigidbody.m_SetMass || !raw()) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, float)>(fn->rigidbody.m_SetMass)(raw(), mass);
        }

        [[nodiscard]] float GetDrag() const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->rigidbody.m_GetDrag || !raw()) return 0.f;
            return reinterpret_cast<float(IL2CPP_CALLTYPE)(void*)>(fn->rigidbody.m_GetDrag)(raw());
        }
        void SetDrag(float drag) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->rigidbody.m_SetDrag || !raw()) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, float)>(fn->rigidbody.m_SetDrag)(raw(), drag);
        }

        [[nodiscard]] float GetAngularDrag() const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->rigidbody.m_GetAngularDrag || !raw()) return 0.f;
            return reinterpret_cast<float(IL2CPP_CALLTYPE)(void*)>(fn->rigidbody.m_GetAngularDrag)(raw());
        }
        void SetAngularDrag(float angularDrag) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->rigidbody.m_SetAngularDrag || !raw()) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, float)>(fn->rigidbody.m_SetAngularDrag)(raw(), angularDrag);
        }

        /// Set the density of the rigidbody (recalculates mass from colliders).
        void SetDensity(float density) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->rigidbody.m_SetDensity || !raw()) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, float)>(fn->rigidbody.m_SetDensity)(raw(), density);
        }

        // ---- Gravity / Kinematic ----
        [[nodiscard]] bool GetUseGravity() const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->rigidbody.m_GetUseGravity || !raw()) return false;
            return reinterpret_cast<bool(IL2CPP_CALLTYPE)(void*)>(fn->rigidbody.m_GetUseGravity)(raw());
        }
        void SetUseGravity(bool use) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->rigidbody.m_SetUseGravity || !raw()) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, bool)>(fn->rigidbody.m_SetUseGravity)(raw(), use);
        }

        [[nodiscard]] bool GetIsKinematic() const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->rigidbody.m_GetIsKinematic || !raw()) return false;
            return reinterpret_cast<bool(IL2CPP_CALLTYPE)(void*)>(fn->rigidbody.m_GetIsKinematic)(raw());
        }
        void SetIsKinematic(bool kinematic) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->rigidbody.m_SetIsKinematic || !raw()) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, bool)>(fn->rigidbody.m_SetIsKinematic)(raw(), kinematic);
        }

        // ---- Forces ----
        void AddForce(const Vector3& force, ForceMode mode = ForceMode::Force) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->rigidbody.m_AddForce || !raw()) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, Vector3, int)>(fn->rigidbody.m_AddForce)(raw(), force, static_cast<int>(mode));
        }

        void AddTorque(const Vector3& torque, ForceMode mode = ForceMode::Force) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->rigidbody.m_AddTorque || !raw()) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, Vector3, int)>(fn->rigidbody.m_AddTorque)(raw(), torque, static_cast<int>(mode));
        }

        void AddForceAtPosition(const Vector3& force, const Vector3& position, ForceMode mode = ForceMode::Force) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->rigidbody.m_AddForceAtPosition || !raw()) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, Vector3, Vector3, int)>(fn->rigidbody.m_AddForceAtPosition)(raw(), force, position, static_cast<int>(mode));
        }

        void AddExplosionForce(float explosionForce, const Vector3& explosionPosition, float explosionRadius, float upwardsModifier = 0.f, ForceMode mode = ForceMode::Force) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->rigidbody.m_AddExplosionForce || !raw()) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, float, Vector3, float, float, int)>(fn->rigidbody.m_AddExplosionForce)(raw(), explosionForce, explosionPosition, explosionRadius, upwardsModifier, static_cast<int>(mode));
        }

        // ---- Position / Rotation ----
        void MovePosition(const Vector3& pos) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->rigidbody.m_MovePosition || !raw()) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, const Vector3&)>(fn->rigidbody.m_MovePosition)(raw(), pos);
        }

        void MoveRotation(const Quaternion& rot) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->rigidbody.m_MoveRotation || !raw()) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, const Quaternion&)>(fn->rigidbody.m_MoveRotation)(raw(), rot);
        }

        void Move(const Vector3& pos, const Quaternion& rot) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->rigidbody.m_Move || !raw()) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, const Vector3&, const Quaternion&)>(fn->rigidbody.m_Move)(raw(), pos, rot);
        }

        // ---- Sleep ----
        void Sleep() {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->rigidbody.m_Sleep || !raw()) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*)>(fn->rigidbody.m_Sleep)(raw());
        }

        void WakeUp() {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->rigidbody.m_WakeUp || !raw()) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*)>(fn->rigidbody.m_WakeUp)(raw());
        }

        [[nodiscard]] bool IsSleeping() const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->rigidbody.m_IsSleeping || !raw()) return false;
            return reinterpret_cast<bool(IL2CPP_CALLTYPE)(void*)>(fn->rigidbody.m_IsSleeping)(raw());
        }

        // ---- Freeze / Detect Collisions ----
        [[nodiscard]] bool GetFreezeRotation() const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->rigidbody.m_GetFreezeRotation || !raw()) return false;
            return reinterpret_cast<bool(IL2CPP_CALLTYPE)(void*)>(fn->rigidbody.m_GetFreezeRotation)(raw());
        }
        void SetFreezeRotation(bool freeze) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->rigidbody.m_SetFreezeRotation || !raw()) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, bool)>(fn->rigidbody.m_SetFreezeRotation)(raw(), freeze);
        }

        [[nodiscard]] bool GetDetectCollisions() const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->rigidbody.m_GetDetectCollisions || !raw()) return false;
            return reinterpret_cast<bool(IL2CPP_CALLTYPE)(void*)>(fn->rigidbody.m_GetDetectCollisions)(raw());
        }
        void SetDetectCollisions(bool detect) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->rigidbody.m_SetDetectCollisions || !raw()) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, bool)>(fn->rigidbody.m_SetDetectCollisions)(raw(), detect);
        }

        // ---- Rigidbody Position / Rotation (physics interpolated) ----
        [[nodiscard]] Vector3 GetPosition() const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->rigidbody.m_GetPosition || !raw()) return Vector3{};
            Vector3 v; reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, Vector3*)>(fn->rigidbody.m_GetPosition)(raw(), &v); return v;
        }
        void SetPosition(const Vector3& pos) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->rigidbody.m_SetPosition || !raw()) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, const Vector3&)>(fn->rigidbody.m_SetPosition)(raw(), pos);
        }

        [[nodiscard]] Quaternion GetRotation() const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->rigidbody.m_GetRotation || !raw()) return Quaternion{};
            Quaternion q; reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, Quaternion*)>(fn->rigidbody.m_GetRotation)(raw(), &q); return q;
        }
        void SetRotation(const Quaternion& rot) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->rigidbody.m_SetRotation || !raw()) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, const Quaternion&)>(fn->rigidbody.m_SetRotation)(raw(), rot);
        }

        // ---- Center of Mass ----
        [[nodiscard]] Vector3 GetCenterOfMass() const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->rigidbody.m_GetCenterOfMass || !raw()) return Vector3{};
            Vector3 v; reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, Vector3*)>(fn->rigidbody.m_GetCenterOfMass)(raw(), &v); return v;
        }
        void SetCenterOfMass(const Vector3& com) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->rigidbody.m_SetCenterOfMass || !raw()) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, const Vector3&)>(fn->rigidbody.m_SetCenterOfMass)(raw(), com);
        }

        // ---- Interpolation / Collision Detection Mode ----
        [[nodiscard]] RigidbodyInterpolation GetInterpolation() const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->rigidbody.m_GetInterpolation || !raw()) return RigidbodyInterpolation::None;
            return static_cast<RigidbodyInterpolation>(reinterpret_cast<int(IL2CPP_CALLTYPE)(void*)>(fn->rigidbody.m_GetInterpolation)(raw()));
        }
        void SetInterpolation(RigidbodyInterpolation interp) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->rigidbody.m_SetInterpolation || !raw()) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, int)>(fn->rigidbody.m_SetInterpolation)(raw(), static_cast<int>(interp));
        }

        [[nodiscard]] CollisionDetectionMode GetCollisionDetectionMode() const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->rigidbody.m_GetCollisionDetectionMode || !raw()) return CollisionDetectionMode::Discrete;
            return static_cast<CollisionDetectionMode>(reinterpret_cast<int(IL2CPP_CALLTYPE)(void*)>(fn->rigidbody.m_GetCollisionDetectionMode)(raw()));
        }
        void SetCollisionDetectionMode(CollisionDetectionMode mode) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->rigidbody.m_SetCollisionDetectionMode || !raw()) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, int)>(fn->rigidbody.m_SetCollisionDetectionMode)(raw(), static_cast<int>(mode));
        }

        // ---- Velocity Queries ----
        [[nodiscard]] Vector3 GetRelativePointVelocity(const Vector3& relativePoint) const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->rigidbody.m_GetRelativePointVelocity || !raw()) return Vector3{};
            Vector3 v; reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, const Vector3&, Vector3*)>(fn->rigidbody.m_GetRelativePointVelocity)(raw(), relativePoint, &v); return v;
        }

        [[nodiscard]] Vector3 GetPointVelocity(const Vector3& worldPoint) const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->rigidbody.m_GetPointVelocity || !raw()) return Vector3{};
            Vector3 v; reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, const Vector3&, Vector3*)>(fn->rigidbody.m_GetPointVelocity)(raw(), worldPoint, &v); return v;
        }

        // ---- Bounds ----
        [[nodiscard]] Vector3 ClosestPointOnBounds(const Vector3& position) const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->rigidbody.m_ClosestPointOnBounds || !raw()) return Vector3{};
            Vector3 v; reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, const Vector3&, Vector3*)>(fn->rigidbody.m_ClosestPointOnBounds)(raw(), position, &v); return v;
        }

        // ---- Constraints ----
        [[nodiscard]] RigidbodyConstraints GetConstraints() const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->rigidbody.m_GetConstraints || !raw()) return RigidbodyConstraints::None;
            return static_cast<RigidbodyConstraints>(reinterpret_cast<int(IL2CPP_CALLTYPE)(void*)>(fn->rigidbody.m_GetConstraints)(raw()));
        }
        void SetConstraints(RigidbodyConstraints c) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->rigidbody.m_SetConstraints || !raw()) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, int)>(fn->rigidbody.m_SetConstraints)(raw(), static_cast<int>(c));
        }

        // ---- Legacy snake_case aliases (deprecated) ----
        [[deprecated("Use GetVelocity()")]] [[nodiscard]] Vector3 get_velocity() const { return GetVelocity(); }
        [[deprecated("Use SetVelocity()")]] void set_velocity(const Vector3& v) { SetVelocity(v); }
        [[deprecated("Use GetAngularVelocity()")]] [[nodiscard]] Vector3 get_angular_velocity() const { return GetAngularVelocity(); }
        [[deprecated("Use SetAngularVelocity()")]] void set_angular_velocity(const Vector3& v) { SetAngularVelocity(v); }
        [[deprecated("Use GetMass()")]] [[nodiscard]] float get_mass() const { return GetMass(); }
        [[deprecated("Use SetMass()")]] void set_mass(float m) { SetMass(m); }
        [[deprecated("Use GetDrag()")]] [[nodiscard]] float get_drag() const { return GetDrag(); }
        [[deprecated("Use SetDrag()")]] void set_drag(float d) { SetDrag(d); }
        [[deprecated("Use GetAngularDrag()")]] [[nodiscard]] float get_angular_drag() const { return GetAngularDrag(); }
        [[deprecated("Use SetAngularDrag()")]] void set_angular_drag(float d) { SetAngularDrag(d); }
        [[deprecated("Use SetDensity()")]] void set_density(float d) { SetDensity(d); }
        [[deprecated("Use GetUseGravity()")]] [[nodiscard]] bool get_use_gravity() const { return GetUseGravity(); }
        [[deprecated("Use SetUseGravity()")]] void set_use_gravity(bool u) { SetUseGravity(u); }
        [[deprecated("Use GetIsKinematic()")]] [[nodiscard]] bool get_is_kinematic() const { return GetIsKinematic(); }
        [[deprecated("Use SetIsKinematic()")]] void set_is_kinematic(bool k) { SetIsKinematic(k); }
        [[deprecated("Use AddForce()")]] void add_force(const Vector3& f, ForceMode m = ForceMode::Force) { AddForce(f, m); }
        [[deprecated("Use AddTorque()")]] void add_torque(const Vector3& t, ForceMode m = ForceMode::Force) { AddTorque(t, m); }
        [[deprecated("Use MovePosition()")]] void move_position(const Vector3& p) { MovePosition(p); }
        [[deprecated("Use MoveRotation()")]] void move_rotation(const Quaternion& r) { MoveRotation(r); }
        [[deprecated("Use Sleep()")]] void sleep() { Sleep(); }
        [[deprecated("Use WakeUp()")]] void wake_up() { WakeUp(); }
        [[deprecated("Use IsSleeping()")]] [[nodiscard]] bool is_sleeping() const { return IsSleeping(); }
    };

} // namespace IL2CPP::Module::Unity

// ---- Deferred implementation requiring complete Rigidbody type ----
#include "Collider.hpp"

namespace IL2CPP::Module::Unity {
    inline Rigidbody Collider::GetAttachedRigidbody() const {
        auto* fn = GetUnityFunctions();
        if (!fn || !fn->collider.m_GetAttachedRigidbody || !raw()) return Rigidbody{};
        return Rigidbody{ reinterpret_cast<void*(IL2CPP_CALLTYPE)(void*)>(fn->collider.m_GetAttachedRigidbody)(raw()) };
    }
    inline Rigidbody Collider::get_attached_rigidbody() const { return GetAttachedRigidbody(); }
} // deferred
