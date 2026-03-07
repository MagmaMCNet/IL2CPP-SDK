#pragma once
#include "../MethodHandler.hpp"
#include <IL2CPP.Common/il2cpp_types.hpp>

// ============================================================================
//  IL2CPP.Module::Unity::Physics - Static utility class for physics queries
// ============================================================================

namespace IL2CPP::Module::Unity {

    class Physics {
    public:
        Physics() = delete;

        /// Cast a ray and check for collisions.
        [[nodiscard]] static bool Raycast(const Vector3& origin, const Vector3& direction, RaycastHit& hit,
                                          float maxDistance = 1e10f, LayerMask layerMask = LayerMask(-1)) {
            static auto m = MethodHandler::resolve("UnityEngine.Physics", "Raycast", 5);
            Vector3 o = origin, d = direction;
            float md = maxDistance;
            int mask = layerMask.value();
            void* params[] = { &o, &d, &hit, &md, &mask };
            return MethodHandler::invoke<bool>(m, nullptr, params);
        }

        /// Cast a ray without needing hit info (simple collision check).
        [[nodiscard]] static bool Raycast(const Vector3& origin, const Vector3& direction,
                                          float maxDistance = 1e10f, LayerMask layerMask = LayerMask(-1)) {
            RaycastHit hit;
            return Raycast(origin, direction, hit, maxDistance, layerMask);
        }

        /// Cast a ray from a Ray struct.
        [[nodiscard]] static bool Raycast(const Ray& ray, RaycastHit& hit,
                                          float maxDistance = 1e10f, LayerMask layerMask = LayerMask(-1)) {
            return Raycast(ray.origin, ray.direction, hit, maxDistance, layerMask);
        }

        /// Cast a ray from a Ray struct (simple collision check).
        [[nodiscard]] static bool Raycast(const Ray& ray, float maxDistance = 1e10f, LayerMask layerMask = LayerMask(-1)) {
            RaycastHit hit;
            return Raycast(ray.origin, ray.direction, hit, maxDistance, layerMask);
        }

        /// Cast a sphere along a ray and check for collisions.
        [[nodiscard]] static bool SphereCast(const Vector3& origin, float radius, const Vector3& direction,
                                             RaycastHit& hit, float maxDistance = 1e10f, LayerMask layerMask = LayerMask(-1)) {
            static auto m = MethodHandler::resolve("UnityEngine.Physics", "SphereCast", 6);
            Vector3 o = origin, d = direction;
            float r = radius, md = maxDistance;
            int mask = layerMask.value();
            void* params[] = { &o, &r, &d, &hit, &md, &mask };
            return MethodHandler::invoke<bool>(m, nullptr, params);
        }

        /// Cast a sphere along a ray (simple collision check).
        [[nodiscard]] static bool SphereCast(const Vector3& origin, float radius, const Vector3& direction,
                                             float maxDistance = 1e10f, LayerMask layerMask = LayerMask(-1)) {
            RaycastHit hit;
            return SphereCast(origin, radius, direction, hit, maxDistance, layerMask);
        }

        /// Cast a sphere from a Ray struct.
        [[nodiscard]] static bool SphereCast(const Ray& ray, float radius, RaycastHit& hit,
                                             float maxDistance = 1e10f, LayerMask layerMask = LayerMask(-1)) {
            return SphereCast(ray.origin, radius, ray.direction, hit, maxDistance, layerMask);
        }

        // ---- Utility Methods ----

        [[nodiscard]] static Ray CreateRayToward(const Vector3& from, const Vector3& to) {
            Vector3 dir = to - from;
            dir.NormalizeInPlace();
            return Ray(from, dir);
        }

        [[nodiscard]] static bool LineOfSight(const Vector3& from, const Vector3& to, LayerMask layerMask = LayerMask(-1)) {
            Vector3 dir = to - from;
            float dist = dir.Magnitude();
            if (dist < 0.0001f) return true;
            dir = dir / dist;
            RaycastHit hit;
            return !Raycast(from, dir, hit, dist, layerMask);
        }

        // ---- Legacy snake_case aliases (deprecated) ----
        [[deprecated("Use Raycast()")]] [[nodiscard]] static bool raycast(const Vector3& o, const Vector3& d, RaycastHit& h, float m = 1e10f, LayerMask l = LayerMask(-1)) { return Raycast(o, d, h, m, l); }
        [[deprecated("Use Raycast()")]] [[nodiscard]] static bool raycast(const Vector3& o, const Vector3& d, float m = 1e10f, LayerMask l = LayerMask(-1)) { return Raycast(o, d, m, l); }
        [[deprecated("Use Raycast()")]] [[nodiscard]] static bool raycast(const Ray& r, RaycastHit& h, float m = 1e10f, LayerMask l = LayerMask(-1)) { return Raycast(r, h, m, l); }
        [[deprecated("Use Raycast()")]] [[nodiscard]] static bool raycast(const Ray& r, float m = 1e10f, LayerMask l = LayerMask(-1)) { return Raycast(r, m, l); }
        [[deprecated("Use SphereCast()")]] [[nodiscard]] static bool sphere_cast(const Vector3& o, float ra, const Vector3& d, RaycastHit& h, float m = 1e10f, LayerMask l = LayerMask(-1)) { return SphereCast(o, ra, d, h, m, l); }
        [[deprecated("Use SphereCast()")]] [[nodiscard]] static bool sphere_cast(const Vector3& o, float ra, const Vector3& d, float m = 1e10f, LayerMask l = LayerMask(-1)) { return SphereCast(o, ra, d, m, l); }
        [[deprecated("Use SphereCast()")]] [[nodiscard]] static bool sphere_cast(const Ray& r, float ra, RaycastHit& h, float m = 1e10f, LayerMask l = LayerMask(-1)) { return SphereCast(r, ra, h, m, l); }
        [[deprecated("Use CreateRayToward()")]] [[nodiscard]] static Ray create_ray_toward(const Vector3& f, const Vector3& t) { return CreateRayToward(f, t); }
        [[deprecated("Use LineOfSight()")]] [[nodiscard]] static bool line_of_sight(const Vector3& f, const Vector3& t, LayerMask l = LayerMask(-1)) { return LineOfSight(f, t, l); }
    };

} // namespace IL2CPP::Module::Unity
