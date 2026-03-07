#pragma once
#include "Component.hpp"
#include "../MethodHandler.hpp"
#include <IL2CPP.Common/il2cpp_types.hpp>

// ============================================================================
//  IL2CPP.Module::Unity::Rigidbody
// ============================================================================

namespace IL2CPP::Module::Unity {

    class Rigidbody : public Component {
    public:
        using Component::Component;

        // ---- Velocity ----
        [[nodiscard]] Vector3 GetVelocity() const {
            static auto m = MethodHandler::resolve("UnityEngine.Rigidbody", "get_velocity", 0);
            return MethodHandler::invoke<Vector3>(m, raw());
        }
        void SetVelocity(const Vector3& vel) {
            static auto m = MethodHandler::resolve("UnityEngine.Rigidbody", "set_velocity", 1);
            Vector3 v = vel;
            void* params[] = { &v };
            MethodHandler::invoke(m, raw(), params);
        }

        [[nodiscard]] Vector3 GetAngularVelocity() const {
            static auto m = MethodHandler::resolve("UnityEngine.Rigidbody", "get_angularVelocity", 0);
            return MethodHandler::invoke<Vector3>(m, raw());
        }
        void SetAngularVelocity(const Vector3& vel) {
            static auto m = MethodHandler::resolve("UnityEngine.Rigidbody", "set_angularVelocity", 1);
            Vector3 v = vel;
            void* params[] = { &v };
            MethodHandler::invoke(m, raw(), params);
        }

        // ---- Mass / Drag ----
        [[nodiscard]] float GetMass() const {
            static auto m = MethodHandler::resolve("UnityEngine.Rigidbody", "get_mass", 0);
            return MethodHandler::invoke<float>(m, raw());
        }
        void SetMass(float mass) {
            static auto m = MethodHandler::resolve("UnityEngine.Rigidbody", "set_mass", 1);
            void* params[] = { &mass };
            MethodHandler::invoke(m, raw(), params);
        }

        [[nodiscard]] float GetDrag() const {
            static auto m = MethodHandler::resolve("UnityEngine.Rigidbody", "get_drag", 0);
            return MethodHandler::invoke<float>(m, raw());
        }
        void SetDrag(float drag) {
            static auto m = MethodHandler::resolve("UnityEngine.Rigidbody", "set_drag", 1);
            void* params[] = { &drag };
            MethodHandler::invoke(m, raw(), params);
        }

        [[nodiscard]] float GetAngularDrag() const {
            static auto m = MethodHandler::resolve("UnityEngine.Rigidbody", "get_angularDrag", 0);
            return MethodHandler::invoke<float>(m, raw());
        }
        void SetAngularDrag(float angularDrag) {
            static auto m = MethodHandler::resolve("UnityEngine.Rigidbody", "set_angularDrag", 1);
            void* params[] = { &angularDrag };
            MethodHandler::invoke(m, raw(), params);
        }

        /// Set the density of the rigidbody (recalculates mass from colliders).
        void SetDensity(float density) {
            static auto m = MethodHandler::resolve("UnityEngine.Rigidbody", "SetDensity", 1);
            void* params[] = { &density };
            MethodHandler::invoke(m, raw(), params);
        }

        // ---- Gravity / Kinematic ----
        [[nodiscard]] bool GetUseGravity() const {
            static auto m = MethodHandler::resolve("UnityEngine.Rigidbody", "get_useGravity", 0);
            return MethodHandler::invoke<bool>(m, raw());
        }
        void SetUseGravity(bool use) {
            static auto m = MethodHandler::resolve("UnityEngine.Rigidbody", "set_useGravity", 1);
            void* params[] = { &use };
            MethodHandler::invoke(m, raw(), params);
        }

        [[nodiscard]] bool GetIsKinematic() const {
            static auto m = MethodHandler::resolve("UnityEngine.Rigidbody", "get_isKinematic", 0);
            return MethodHandler::invoke<bool>(m, raw());
        }
        void SetIsKinematic(bool kinematic) {
            static auto m = MethodHandler::resolve("UnityEngine.Rigidbody", "set_isKinematic", 1);
            void* params[] = { &kinematic };
            MethodHandler::invoke(m, raw(), params);
        }

        // ---- Forces ----
        void AddForce(const Vector3& force, ForceMode mode = ForceMode::Force) {
            static auto m = MethodHandler::resolve("UnityEngine.Rigidbody", "AddForce", 2);
            Vector3 f = force;
            int md = static_cast<int>(mode);
            void* params[] = { &f, &md };
            MethodHandler::invoke(m, raw(), params);
        }

        void AddTorque(const Vector3& torque, ForceMode mode = ForceMode::Force) {
            static auto m = MethodHandler::resolve("UnityEngine.Rigidbody", "AddTorque", 2);
            Vector3 t = torque;
            int md = static_cast<int>(mode);
            void* params[] = { &t, &md };
            MethodHandler::invoke(m, raw(), params);
        }

        void AddForceAtPosition(const Vector3& force, const Vector3& position, ForceMode mode = ForceMode::Force) {
            static auto m = MethodHandler::resolve("UnityEngine.Rigidbody", "AddForceAtPosition", 3);
            Vector3 f = force;
            Vector3 p = position;
            int md = static_cast<int>(mode);
            void* params[] = { &f, &p, &md };
            MethodHandler::invoke(m, raw(), params);
        }

        void AddExplosionForce(float explosionForce, const Vector3& explosionPosition, float explosionRadius, float upwardsModifier = 0.f, ForceMode mode = ForceMode::Force) {
            static auto m = MethodHandler::resolve("UnityEngine.Rigidbody", "AddExplosionForce", 5);
            Vector3 ep = explosionPosition;
            int md = static_cast<int>(mode);
            void* params[] = { &explosionForce, &ep, &explosionRadius, &upwardsModifier, &md };
            MethodHandler::invoke(m, raw(), params);
        }

        // ---- Position / Rotation ----
        void MovePosition(const Vector3& pos) {
            static auto m = MethodHandler::resolve("UnityEngine.Rigidbody", "MovePosition", 1);
            Vector3 p = pos;
            void* params[] = { &p };
            MethodHandler::invoke(m, raw(), params);
        }

        void MoveRotation(const Quaternion& rot) {
            static auto m = MethodHandler::resolve("UnityEngine.Rigidbody", "MoveRotation", 1);
            Quaternion r = rot;
            void* params[] = { &r };
            MethodHandler::invoke(m, raw(), params);
        }

        void Move(const Vector3& pos, const Quaternion& rot) {
            static auto m = MethodHandler::resolve("UnityEngine.Rigidbody", "Move", 2);
            Vector3 p = pos;
            Quaternion r = rot;
            void* params[] = { &p, &r };
            MethodHandler::invoke(m, raw(), params);
        }

        // ---- Sleep ----
        void Sleep() {
            static auto m = MethodHandler::resolve("UnityEngine.Rigidbody", "Sleep", 0);
            MethodHandler::invoke(m, raw());
        }

        void WakeUp() {
            static auto m = MethodHandler::resolve("UnityEngine.Rigidbody", "WakeUp", 0);
            MethodHandler::invoke(m, raw());
        }

        [[nodiscard]] bool IsSleeping() const {
            static auto m = MethodHandler::resolve("UnityEngine.Rigidbody", "IsSleeping", 0);
            return MethodHandler::invoke<bool>(m, raw());
        }

        // ---- Freeze / Detect Collisions ----
        [[nodiscard]] bool GetFreezeRotation() const {
            static auto m = MethodHandler::resolve("UnityEngine.Rigidbody", "get_freezeRotation", 0);
            return MethodHandler::invoke<bool>(m, raw());
        }
        void SetFreezeRotation(bool freeze) {
            static auto m = MethodHandler::resolve("UnityEngine.Rigidbody", "set_freezeRotation", 1);
            void* params[] = { &freeze };
            MethodHandler::invoke(m, raw(), params);
        }

        [[nodiscard]] bool GetDetectCollisions() const {
            static auto m = MethodHandler::resolve("UnityEngine.Rigidbody", "get_detectCollisions", 0);
            return MethodHandler::invoke<bool>(m, raw());
        }
        void SetDetectCollisions(bool detect) {
            static auto m = MethodHandler::resolve("UnityEngine.Rigidbody", "set_detectCollisions", 1);
            void* params[] = { &detect };
            MethodHandler::invoke(m, raw(), params);
        }

        // ---- Rigidbody Position / Rotation (physics interpolated) ----
        [[nodiscard]] Vector3 GetPosition() const {
            static auto m = MethodHandler::resolve("UnityEngine.Rigidbody", "get_position", 0);
            return MethodHandler::invoke<Vector3>(m, raw());
        }
        void SetPosition(const Vector3& pos) {
            static auto m = MethodHandler::resolve("UnityEngine.Rigidbody", "set_position", 1);
            Vector3 p = pos;
            void* params[] = { &p };
            MethodHandler::invoke(m, raw(), params);
        }

        [[nodiscard]] Quaternion GetRotation() const {
            static auto m = MethodHandler::resolve("UnityEngine.Rigidbody", "get_rotation", 0);
            return MethodHandler::invoke<Quaternion>(m, raw());
        }
        void SetRotation(const Quaternion& rot) {
            static auto m = MethodHandler::resolve("UnityEngine.Rigidbody", "set_rotation", 1);
            Quaternion r = rot;
            void* params[] = { &r };
            MethodHandler::invoke(m, raw(), params);
        }

        // ---- Center of Mass ----
        [[nodiscard]] Vector3 GetCenterOfMass() const {
            static auto m = MethodHandler::resolve("UnityEngine.Rigidbody", "get_centerOfMass", 0);
            return MethodHandler::invoke<Vector3>(m, raw());
        }
        void SetCenterOfMass(const Vector3& com) {
            static auto m = MethodHandler::resolve("UnityEngine.Rigidbody", "set_centerOfMass", 1);
            Vector3 c = com;
            void* params[] = { &c };
            MethodHandler::invoke(m, raw(), params);
        }

        // ---- Interpolation / Collision Detection Mode ----
        [[nodiscard]] RigidbodyInterpolation GetInterpolation() const {
            static auto m = MethodHandler::resolve("UnityEngine.Rigidbody", "get_interpolation", 0);
            return static_cast<RigidbodyInterpolation>(MethodHandler::invoke<int>(m, raw()));
        }
        void SetInterpolation(RigidbodyInterpolation interp) {
            static auto m = MethodHandler::resolve("UnityEngine.Rigidbody", "set_interpolation", 1);
            int val = static_cast<int>(interp);
            void* params[] = { &val };
            MethodHandler::invoke(m, raw(), params);
        }

        [[nodiscard]] CollisionDetectionMode GetCollisionDetectionMode() const {
            static auto m = MethodHandler::resolve("UnityEngine.Rigidbody", "get_collisionDetectionMode", 0);
            return static_cast<CollisionDetectionMode>(MethodHandler::invoke<int>(m, raw()));
        }
        void SetCollisionDetectionMode(CollisionDetectionMode mode) {
            static auto m = MethodHandler::resolve("UnityEngine.Rigidbody", "set_collisionDetectionMode", 1);
            int val = static_cast<int>(mode);
            void* params[] = { &val };
            MethodHandler::invoke(m, raw(), params);
        }

        // ---- Velocity Queries ----
        [[nodiscard]] Vector3 GetRelativePointVelocity(const Vector3& relativePoint) const {
            static auto m = MethodHandler::resolve("UnityEngine.Rigidbody", "GetRelativePointVelocity", 1);
            Vector3 rp = relativePoint;
            void* params[] = { &rp };
            return MethodHandler::invoke<Vector3>(m, raw(), params);
        }

        [[nodiscard]] Vector3 GetPointVelocity(const Vector3& worldPoint) const {
            static auto m = MethodHandler::resolve("UnityEngine.Rigidbody", "GetPointVelocity", 1);
            Vector3 wp = worldPoint;
            void* params[] = { &wp };
            return MethodHandler::invoke<Vector3>(m, raw(), params);
        }

        // ---- Bounds ----
        [[nodiscard]] Vector3 ClosestPointOnBounds(const Vector3& position) const {
            static auto m = MethodHandler::resolve("UnityEngine.Rigidbody", "ClosestPointOnBounds", 1);
            Vector3 p = position;
            void* params[] = { &p };
            return MethodHandler::invoke<Vector3>(m, raw(), params);
        }

        // ---- Constraints ----
        [[nodiscard]] RigidbodyConstraints GetConstraints() const {
            static auto m = MethodHandler::resolve("UnityEngine.Rigidbody", "get_constraints", 0);
            return static_cast<RigidbodyConstraints>(MethodHandler::invoke<int>(m, raw()));
        }
        void SetConstraints(RigidbodyConstraints c) {
            static auto m = MethodHandler::resolve("UnityEngine.Rigidbody", "set_constraints", 1);
            int val = static_cast<int>(c);
            void* params[] = { &val };
            MethodHandler::invoke(m, raw(), params);
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
        static auto m = MethodHandler::resolve("UnityEngine.Collider", "get_attachedRigidbody", 0);
        return Rigidbody{ MethodHandler::invoke<void*>(m, raw()) };
    }
    inline Rigidbody Collider::get_attached_rigidbody() const { return GetAttachedRigidbody(); }
} // deferred
