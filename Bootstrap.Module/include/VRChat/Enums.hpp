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

    enum class RpcDestination : int {
        All = 0,
        Others = 1,
        Owner = 2,
        Master = 3,
        AllBuffered = 4,
        OthersBuffered = 5,
        Local = 6,
        AllBufferOne = 7,
        OthersBufferOne = 8,
        TargetPlayer = 9
    };

    enum class VrcBroadcastType : int {
        Always = 0,
        Master = 1,
        Local = 2,
        Owner = 3,
        AlwaysUnbuffered = 4,
        MasterUnbuffered = 5,
        OwnerUnbuffered = 6,
        AlwaysBufferOne = 7,
        MasterBufferOne = 8,
        OwnerBufferOne = 9
    };

} // namespace IL2CPP::VRChat
