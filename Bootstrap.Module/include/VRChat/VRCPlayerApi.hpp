#pragma once

#include "Enums.hpp"
#include <IL2CPP.Module/include/il2cpp_module.hpp>
#include <IL2CPP.Common/il2cpp_shared.hpp>
#include <string>
#include <string_view>

namespace IL2CPP::VRChat {

    class VRCPlayer;

    class VRCPlayerApi : public IL2CPP::Module::ManagedObject {
    public:
        using ManagedObject::ManagedObject;

        struct TrackingData {
            Vector3 position;
            Quaternion rotation;

            [[nodiscard]] std::string ToString() const {
                return std::format("({}), ({})", position.ToString(), rotation.ToString());
            }
        };

        // Identity
        [[nodiscard]] std::string GetDisplayName();
        void SetDisplayName(std::string_view name);
        [[nodiscard]] int GetPlayerId();
        [[nodiscard]] bool IsLocal();

        // Status & Permissions
        [[nodiscard]] bool IsMaster();
        [[nodiscard]] bool IsInstanceOwner();
        [[nodiscard]] bool IsModerator();
        [[nodiscard]] bool IsSuper();
        [[nodiscard]] bool IsSuspended();
        [[nodiscard]] bool IsValid();

        // VR & Locomotion State
        [[nodiscard]] bool IsUserInVR();
        [[nodiscard]] bool IsPlayerGrounded();

        // Transform & Movement
        [[nodiscard]] TrackingData GetTrackingData(TrackingDataType tt);
        [[nodiscard]] IL2CPP::Vector3 GetVelocity();
        [[nodiscard]] IL2CPP::Vector3 GetPosition();
        [[nodiscard]] IL2CPP::Quaternion GetRotation();
        [[nodiscard]] IL2CPP::Vector3 GetBonePosition(HumanBodyBones bone);
        [[nodiscard]] IL2CPP::Quaternion GetBoneRotation(HumanBodyBones bone);

        void SetVelocity(IL2CPP::Vector3 v);
        void TeleportTo(IL2CPP::Vector3 pos, IL2CPP::Quaternion rot);
        void TeleportTo(IL2CPP::Vector3 pos, IL2CPP::Quaternion rot, SpawnOrientation o);
        void TeleportTo(IL2CPP::Vector3 pos, IL2CPP::Quaternion rot, SpawnOrientation o, bool lerpOnRemote);
        void Respawn();
        void Respawn(int idx);

        // Movement Settings
        [[nodiscard]] float GetGravityStrength();
        [[nodiscard]] float GetRunSpeed();
        [[nodiscard]] float GetWalkSpeed();
        [[nodiscard]] float GetStrafeSpeed();
        [[nodiscard]] float GetJumpImpulse();

        void SetGravityStrength(float s);
        void SetRunSpeed(float s);
        void SetWalkSpeed(float s);
        void SetStrafeSpeed(float s);
        void SetJumpImpulse(float i);

        void UseLegacyLocomotion();
        void UseAttachedStation();
        void Immobilize(bool i);

        // Voice Settings
        [[nodiscard]] float GetVoiceGain();
        [[nodiscard]] float GetVoiceDistanceNear();
        [[nodiscard]] float GetVoiceDistanceFar();
        [[nodiscard]] float GetVoiceVolumetricRadius();
        [[nodiscard]] bool GetVoiceLowpass();

        void SetVoiceGain(float g);
        void SetVoiceDistanceNear(float n);
        void SetVoiceDistanceFar(float f);
        void SetVoiceVolumetricRadius(float r);
        void SetVoiceLowpass(bool e);

        // Avatar Audio Settings
        void SetAvatarAudioGain(float g);
        void SetAvatarAudioFarRadius(float d);
        void SetAvatarAudioNearRadius(float d);
        void SetAvatarAudioVolumetricRadius(float r);
        void SetAvatarAudioForceSpatial(bool f);
        void SetAvatarAudioCustomCurve(bool a);

        // Avatar Scaling
        [[nodiscard]] float GetAvatarEyeHeightAsMeters();
        [[nodiscard]] float GetAvatarEyeHeightMaximumAsMeters();
        [[nodiscard]] float GetAvatarEyeHeightMinimumAsMeters();
        [[nodiscard]] bool GetManualAvatarScalingAllowed();

        void SetAvatarEyeHeightByMeters(float m);
        void SetAvatarEyeHeightByMultiplier(float m);
        void SetAvatarEyeHeightMaximumByMeters(float m);
        void SetAvatarEyeHeightMinimumByMeters(float m);
        void SetManualAvatarScalingAllowed(bool e);

        // Nameplate
        void SetNamePlateColor(IL2CPP::Color c);
        void RestoreNamePlateColor();
        void SetNamePlateVisibility(bool f);
        void RestoreNamePlateVisibility();

        // Ownership
        [[nodiscard]] bool IsOwner(IL2CPP::Module::Unity::GameObject obj);
        void TakeOwnership(IL2CPP::Module::Unity::GameObject obj);

        // Interactions
        void EnablePickups(bool e);

        // Object References
        [[nodiscard]] IL2CPP::Module::Unity::GameObject GetGameObject();
        [[nodiscard]] VRCPlayer GetVRCPlayer();

        // Static Methods
        static int GetPlayerCount();
        static int GetPlayerId(VRCPlayerApi p);
        static VRCPlayerApi GetPlayerByGameObject(IL2CPP::Module::Unity::GameObject o);
        static VRCPlayerApi GetPlayerById(int id);

        static VRCPlayerApi GetLocalPlayer();
    };

} // namespace IL2CPP::VRChat
