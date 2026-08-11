#pragma once
#include "../MethodHandler.hpp"
#include "../System/Array.hpp"
#include <IL2CPP.Common/il2cpp_types.hpp>
#include <vector>

namespace IL2CPP::Module::Unity {

    class Physics {
    public:
        Physics() = delete;

        /// <summary>Cast a ray and check for collisions.</summary>
        /// <param name="layerMask">Layers to test; defaults to Unity's DefaultRaycastLayers (Ignore Raycast excluded).</param>
        /// <param name="queryTrigger">0 = UseGlobal, 1 = Collide (hit triggers), 2 = Ignore.</param>
        [[nodiscard]] static bool Raycast(const Vector3& origin, const Vector3& direction, RaycastHit& hit,
                                          float maxDistance = 1e10f, LayerMask layerMask = LayerMask(~(1 << 2)),
                                          int queryTrigger = 2) {
            static auto m = MethodHandler::resolve(IL2CPP_STR("UnityEngine.Physics"), IL2CPP_STR("Raycast"), 6);
            Vector3 o = origin, d = direction;
            float md = maxDistance;
            int mask = layerMask.value();
            int qti = queryTrigger;
            void* params[] = { &o, &d, &hit, &md, &mask, &qti };
            return MethodHandler::invoke<bool>(m, nullptr, params);
        }

        /// <summary>Cast a ray without needing hit info (simple collision check).</summary>
        /// <param name="queryTrigger">0 = UseGlobal, 1 = Collide (hit triggers), 2 = Ignore.</param>
        [[nodiscard]] static bool Raycast(const Vector3& origin, const Vector3& direction,
                                          float maxDistance = 1e10f, LayerMask layerMask = LayerMask(~(1 << 2)),
                                          int queryTrigger = 2) {
            RaycastHit hit;
            return Raycast(origin, direction, hit, maxDistance, layerMask, queryTrigger);
        }

        /// <summary>Cast a ray from a Ray struct.</summary>
        /// <param name="queryTrigger">0 = UseGlobal, 1 = Collide (hit triggers), 2 = Ignore.</param>
        [[nodiscard]] static bool Raycast(const Ray& ray, RaycastHit& hit,
                                          float maxDistance = 1e10f, LayerMask layerMask = LayerMask(~(1 << 2)),
                                          int queryTrigger = 2) {
            return Raycast(ray.origin, ray.direction, hit, maxDistance, layerMask, queryTrigger);
        }

        /// <summary>Cast a ray from a Ray struct (simple collision check).</summary>
        /// <param name="queryTrigger">0 = UseGlobal, 1 = Collide (hit triggers), 2 = Ignore.</param>
        [[nodiscard]] static bool Raycast(const Ray& ray, float maxDistance = 1e10f,
                                          LayerMask layerMask = LayerMask(~(1 << 2)), int queryTrigger = 2) {
            RaycastHit hit;
            return Raycast(ray.origin, ray.direction, hit, maxDistance, layerMask, queryTrigger);
        }

        /// <summary>Cast a ray and return ALL colliders hit along it, nearest first not guaranteed.</summary>
        /// <param name="queryTrigger">0 = UseGlobal, 1 = Collide (hit triggers), 2 = Ignore.</param>
        [[nodiscard]] static std::vector<RaycastHit> RaycastAll(const Vector3& origin, const Vector3& direction,
                                                                float maxDistance = 1e10f, LayerMask layerMask = LayerMask(~(1 << 2)),
                                                                int queryTrigger = 1) {
            static auto m = MethodHandler::resolve(IL2CPP_STR("UnityEngine.Physics"), IL2CPP_STR("RaycastAll"), 5);
            Vector3 o = origin, d = direction;
            float md = maxDistance;
            int mask = layerMask.value();
            int qti = queryTrigger;
            void* params[] = { &o, &d, &md, &mask, &qti };
            void* arr = MethodHandler::invoke<void*>(m, nullptr, params);
            return System::Array<RaycastHit>(arr).to_vector();
        }

        /// <summary>Cast a ray (Ray struct) and return ALL colliders hit along it.</summary>
        /// <param name="queryTrigger">0 = UseGlobal, 1 = Collide (hit triggers), 2 = Ignore.</param>
        [[nodiscard]] static std::vector<RaycastHit> RaycastAll(const Ray& ray, float maxDistance = 1e10f,
                                                                LayerMask layerMask = LayerMask(~(1 << 2)), int queryTrigger = 1) {
            return RaycastAll(ray.origin, ray.direction, maxDistance, layerMask, queryTrigger);
        }

        /// <summary>Cast a sphere along a ray and check for collisions.</summary>
        /// <param name="layerMask">Layers to test; defaults to Unity's DefaultRaycastLayers (Ignore Raycast excluded).</param>
        /// <param name="queryTrigger">0 = UseGlobal, 1 = Collide (hit triggers), 2 = Ignore.</param>
        [[nodiscard]] static bool SphereCast(const Vector3& origin, float radius, const Vector3& direction,
                                             RaycastHit& hit, float maxDistance = 1e10f,
                                             LayerMask layerMask = LayerMask(~(1 << 2)), int queryTrigger = 2) {
            static auto m = MethodHandler::resolve(IL2CPP_STR("UnityEngine.Physics"), IL2CPP_STR("SphereCast"), 7);
            Vector3 o = origin, d = direction;
            float r = radius, md = maxDistance;
            int mask = layerMask.value();
            int qti = queryTrigger;
            void* params[] = { &o, &r, &d, &hit, &md, &mask, &qti };
            return MethodHandler::invoke<bool>(m, nullptr, params);
        }

        /// <summary>Cast a sphere along a ray (simple collision check).</summary>
        /// <param name="queryTrigger">0 = UseGlobal, 1 = Collide (hit triggers), 2 = Ignore.</param>
        [[nodiscard]] static bool SphereCast(const Vector3& origin, float radius, const Vector3& direction,
                                             float maxDistance = 1e10f, LayerMask layerMask = LayerMask(~(1 << 2)),
                                             int queryTrigger = 2) {
            RaycastHit hit;
            return SphereCast(origin, radius, direction, hit, maxDistance, layerMask, queryTrigger);
        }

        /// <summary>Cast a sphere from a Ray struct.</summary>
        /// <param name="queryTrigger">0 = UseGlobal, 1 = Collide (hit triggers), 2 = Ignore.</param>
        [[nodiscard]] static bool SphereCast(const Ray& ray, float radius, RaycastHit& hit,
                                             float maxDistance = 1e10f, LayerMask layerMask = LayerMask(~(1 << 2)),
                                             int queryTrigger = 2) {
            return SphereCast(ray.origin, radius, ray.direction, hit, maxDistance, layerMask, queryTrigger);
        }


        [[nodiscard]] static Ray CreateRayToward(const Vector3& from, const Vector3& to) {
            Vector3 dir = to - from;
            dir.NormalizeInPlace();
            return Ray(from, dir);
        }

        [[nodiscard]] static bool LineOfSight(const Vector3& from, const Vector3& to,
                                              LayerMask layerMask = LayerMask(~(1 << 2))) {
            Vector3 dir = to - from;
            float dist = dir.Magnitude();
            if (dist < 0.0001f) return true;
            dir = dir / dist;
            RaycastHit hit;
            return !Raycast(from, dir, hit, dist, layerMask);
        }
    };

} // namespace IL2CPP::Module::Unity
