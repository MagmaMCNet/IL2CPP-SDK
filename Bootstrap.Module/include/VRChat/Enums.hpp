#pragma once

// ============================================================================
//  VRChat Enums - Shared enumerations for VRChat SDK types
// ============================================================================

#include <cstdint>

namespace IL2CPP::VRChat {

    enum class TrackingDataType : int {
        Head,
        LeftHand,
        RightHand,
        Origin,
        AvatarRoot
    };

    enum class HumanBodyBones : int {
        Hips = 0,
        LeftUpperLeg = 1,
        RightUpperLeg = 2,
        LeftLowerLeg = 3,
        RightLowerLeg = 4,
        LeftFoot = 5,
        RightFoot = 6,
        Spine = 7,
        Chest = 8,
        Neck = 9,
        Head = 10,
        LeftShoulder = 11,
        RightShoulder = 12,
        LeftUpperArm = 13,
        RightUpperArm = 14,
        LeftLowerArm = 15,
        RightLowerArm = 16,
        LeftHand = 17,
        RightHand = 18,
        LastBone = 19
    };

    enum class SpawnOrientation : int {
        Default,
        AlignPlayerWithSpawnPoint,
        AlignRoomWithSpawnPoint
    };

    enum class VRC_SerializationMethod : int {
        None = 0,
        All,
        OwnerOnly
    };

    enum class EventTiming : int {
        Update = 0,
        LateUpdate,
        PostLateUpdate,
        FixedUpdate
    };

    enum class NetworkEventTarget : int {
        All = 0,
        Others = 1,
        Owner = 2
    };

    enum class SyncType : int {
        Unknown = 0,
        None,
        Continuous,
        Manual
    };

} // namespace IL2CPP::VRChat
