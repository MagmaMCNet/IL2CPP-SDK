#pragma once
#include "Object.hpp"
#include "Transform.hpp"
#include "../MethodHandler.hpp"
#include <vector>

namespace IL2CPP::Module::Unity {

    /// <summary>Managed layout of UnityEngine.HumanPose.</summary>
    struct HumanPoseNative {
        IL2CPP::Vector3 bodyPosition;
        IL2CPP::Quaternion bodyRotation;
        void* muscles = nullptr;
    };

    /// <summary>Writes Unity humanoid muscle values onto a rig.</summary>
    class HumanPoseHandler : public Object {
    public:
        using Object::Object;

        /// <summary>Bind a handler to an avatar asset and the rig root it should drive.</summary>
        [[nodiscard]] static HumanPoseHandler New(void* avatar, Transform root) {
            void* params[] = { avatar, root.raw() };
            return Object::New<HumanPoseHandler>(
                IL2CPP_STR("UnityEngine.HumanPoseHandler"), params, 2);
        }

        void SetHumanPose(HumanPoseNative& pose) {
            static auto m = MethodHandler::resolve(
                IL2CPP_STR("UnityEngine.HumanPoseHandler"), IL2CPP_STR("SetHumanPose"), 1);
            void* params[] = { &pose };
            MethodHandler::invoke<void>(m, raw(), params);
        }

        void GetHumanPose(HumanPoseNative& pose) {
            static auto m = MethodHandler::resolve(
                IL2CPP_STR("UnityEngine.HumanPoseHandler"), IL2CPP_STR("GetHumanPose"), 1);
            void* params[] = { &pose };
            MethodHandler::invoke<void>(m, raw(), params);
        }

        /// <summary>Release the native binding. The handler is unusable afterwards.</summary>
        void Dispose() {
            static auto m = MethodHandler::resolve(
                IL2CPP_STR("UnityEngine.HumanPoseHandler"), IL2CPP_STR("Dispose"), 0);
            MethodHandler::invoke<void>(m, raw());
        }

        /// <summary>Allocate a managed float[] suitable for HumanPose.muscles.</summary>
        [[nodiscard]] static void* NewMuscleArray(size_t count) {
            Class klass = Class::find("System.Single");
            if (!klass) return nullptr;

            auto* exports = GetExports();
            if (!exports || !exports->m_arrayNew) return nullptr;

            return reinterpret_cast<void*(IL2CPP_CALLTYPE)(void*, uintptr_t)>(
                exports->m_arrayNew)(klass.raw(), count);
        }
    };

} // namespace IL2CPP::Module::Unity
