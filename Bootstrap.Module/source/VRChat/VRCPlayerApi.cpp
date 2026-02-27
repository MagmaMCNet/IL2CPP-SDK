#include <include/VRChat/VRCPlayerApi.hpp>
#include <include/VRChat/VRCPlayer.hpp>
#include <include/bootstrap_internal.hpp>
#include <IL2CPP.Module/include/Reflection.hpp>
#include <IL2CPP.Module/include/Unity/GameObject.hpp>

namespace IL2CPP::VRChat {

    std::string VRCPlayerApi::GetDisplayName() {
        return get_string_field("displayName");
    }

    void VRCPlayerApi::SetDisplayName(std::string_view name) {
        set_string_field("displayName", name);
    }

    int VRCPlayerApi::GetPlayerId() {
        if (!valid()) return -1;
        return call_method<int>("get_playerId");
    }

    bool VRCPlayerApi::IsLocal() {
        if (!valid()) return false;
        return get_field<bool>("isLocal");
    }

    bool VRCPlayerApi::IsMaster() {
        if (!valid()) return false;
        return call_method<bool>("get_isMaster");
    }

    bool VRCPlayerApi::IsInstanceOwner() {
        if (!valid()) return false;
        return call_method<bool>("get_isInstanceOwner");
    }

    bool VRCPlayerApi::IsModerator() {
        if (!valid()) return false;
        return call_method<bool>("get_isModerator");
    }

    bool VRCPlayerApi::IsSuper() {
        if (!valid()) return false;
        return call_method<bool>("get_isSuper");
    }

    bool VRCPlayerApi::IsSuspended() {
        if (!valid()) return false;
        return call_method<bool>("get_isSuspended");
    }

    bool VRCPlayerApi::IsValid() {
        if (!valid()) return false;
        return call_method<bool>("IsValid");
    }

    bool VRCPlayerApi::IsUserInVR() {
        if (!valid()) return false;
        return call_method<bool>("IsUserInVR");
    }

    bool VRCPlayerApi::IsPlayerGrounded() {
        if (!valid()) return false;
        return call_method<bool>("IsPlayerGrounded");
    }

    VRCPlayerApi::TrackingData VRCPlayerApi::GetTrackingData(TrackingDataType tt) {
        if (!valid()) return {};
        void* params[1] = { &tt };
        return call_method<TrackingData>("GetTrackingData", params, 1);
    }

    IL2CPP::Vector3 VRCPlayerApi::GetVelocity() {
        if (!valid()) return {};
        return call_method<IL2CPP::Vector3>("GetVelocity");
    }

    IL2CPP::Vector3 VRCPlayerApi::GetPosition() {
        if (!valid()) return {};
        return call_method<IL2CPP::Vector3>("GetPosition");
    }

    IL2CPP::Quaternion VRCPlayerApi::GetRotation() {
        if (!valid()) return {};
        return call_method<IL2CPP::Quaternion>("GetRotation");
    }

    IL2CPP::Vector3 VRCPlayerApi::GetBonePosition(HumanBodyBones bone) {
        if (!valid()) return {};
        void* params[1] = { &bone };
        return call_method<IL2CPP::Vector3>("GetBonePosition", params, 1);
    }

    IL2CPP::Quaternion VRCPlayerApi::GetBoneRotation(HumanBodyBones bone) {
        if (!valid()) return {};
        void* params[1] = { &bone };
        return call_method<IL2CPP::Quaternion>("GetBoneRotation", params, 1);
    }

    void VRCPlayerApi::SetVelocity(IL2CPP::Vector3 v) {
        if (!valid()) return;
        void* params[1] = { &v };
        call_method<void>("SetVelocity", params, 1);
    }

    void VRCPlayerApi::TeleportTo(IL2CPP::Vector3 pos, IL2CPP::Quaternion rot) {
        if (!valid()) return;
        void* params[2] = { &pos, &rot };
        call_method<void>("TeleportTo", params, 2);
    }

    void VRCPlayerApi::TeleportTo(IL2CPP::Vector3 pos, IL2CPP::Quaternion rot, SpawnOrientation o) {
        if (!valid()) return;
        void* params[3] = { &pos, &rot, &o };
        call_method<void>("TeleportTo", params, 3);
    }

    void VRCPlayerApi::TeleportTo(IL2CPP::Vector3 pos, IL2CPP::Quaternion rot, SpawnOrientation o, bool lerpOnRemote) {
        if (!valid()) return;
        void* params[4] = { &pos, &rot, &o, &lerpOnRemote };
        call_method<void>("TeleportTo", params, 4);
    }

    void VRCPlayerApi::Respawn() {
        if (!valid()) return;
        call_method<void>("Respawn");
    }

    void VRCPlayerApi::Respawn(int idx) {
        if (!valid()) return;
        void* params[1] = { &idx };
        call_method<void>("Respawn", params, 1);
    }

    float VRCPlayerApi::GetGravityStrength() {
        if (!valid()) return 1.0f;
        return call_method<float>("GetGravityStrength");
    }

    float VRCPlayerApi::GetRunSpeed() {
        if (!valid()) return 4.0f;
        return call_method<float>("GetRunSpeed");
    }

    float VRCPlayerApi::GetWalkSpeed() {
        if (!valid()) return 2.0f;
        return call_method<float>("GetWalkSpeed");
    }

    float VRCPlayerApi::GetStrafeSpeed() {
        if (!valid()) return 2.0f;
        return call_method<float>("GetStrafeSpeed");
    }

    float VRCPlayerApi::GetJumpImpulse() {
        if (!valid()) return 3.0f;
        return call_method<float>("GetJumpImpulse");
    }

    void VRCPlayerApi::SetGravityStrength(float s) {
        if (!valid()) return;
        void* params[1] = { &s };
        call_method<void>("SetGravityStrength", params, 1);
    }

    void VRCPlayerApi::SetRunSpeed(float s) {
        if (!valid()) return;
        void* params[1] = { &s };
        call_method<void>("SetRunSpeed", params, 1);
    }

    void VRCPlayerApi::SetWalkSpeed(float s) {
        if (!valid()) return;
        void* params[1] = { &s };
        call_method<void>("SetWalkSpeed", params, 1);
    }

    void VRCPlayerApi::SetStrafeSpeed(float s) {
        if (!valid()) return;
        void* params[1] = { &s };
        call_method<void>("SetStrafeSpeed", params, 1);
    }

    void VRCPlayerApi::SetJumpImpulse(float i) {
        if (!valid()) return;
        void* params[1] = { &i };
        call_method<void>("SetJumpImpulse", params, 1);
    }

    void VRCPlayerApi::UseLegacyLocomotion() {
        if (!valid()) return;
        call_method<void>("UseLegacyLocomotion");
    }

    void VRCPlayerApi::UseAttachedStation() {
        if (!valid()) return;
        call_method<void>("UseAttachedStation");
    }

    void VRCPlayerApi::Immobilize(bool i) {
        if (!valid()) return;
        void* params[1] = { &i };
        call_method<void>("Immobilize", params, 1);
    }

    float VRCPlayerApi::GetVoiceGain() {
        if (!valid()) return 1.0f;
        return call_method<float>("GetVoiceGain");
    }

    float VRCPlayerApi::GetVoiceDistanceNear() {
        if (!valid()) return 0.0f;
        return call_method<float>("GetVoiceDistanceNear");
    }

    float VRCPlayerApi::GetVoiceDistanceFar() {
        if (!valid()) return 25.0f;
        return call_method<float>("GetVoiceDistanceFar");
    }

    float VRCPlayerApi::GetVoiceVolumetricRadius() {
        if (!valid()) return 0.0f;
        return call_method<float>("GetVoiceVolumetricRadius");
    }

    bool VRCPlayerApi::GetVoiceLowpass() {
        if (!valid()) return false;
        return call_method<bool>("GetVoiceLowpass");
    }

    void VRCPlayerApi::SetVoiceGain(float g) {
        if (!valid()) return;
        void* params[1] = { &g };
        call_method<void>("SetVoiceGain", params, 1);
    }

    void VRCPlayerApi::SetVoiceDistanceNear(float n) {
        if (!valid()) return;
        void* params[1] = { &n };
        call_method<void>("SetVoiceDistanceNear", params, 1);
    }

    void VRCPlayerApi::SetVoiceDistanceFar(float f) {
        if (!valid()) return;
        void* params[1] = { &f };
        call_method<void>("SetVoiceDistanceFar", params, 1);
    }

    void VRCPlayerApi::SetVoiceVolumetricRadius(float r) {
        if (!valid()) return;
        void* params[1] = { &r };
        call_method<void>("SetVoiceVolumetricRadius", params, 1);
    }

    void VRCPlayerApi::SetVoiceLowpass(bool e) {
        if (!valid()) return;
        void* params[1] = { &e };
        call_method<void>("SetVoiceLowpass", params, 1);
    }

    void VRCPlayerApi::SetAvatarAudioGain(float g) {
        if (!valid()) return;
        void* params[1] = { &g };
        call_method<void>("SetAvatarAudioGain", params, 1);
    }

    void VRCPlayerApi::SetAvatarAudioFarRadius(float d) {
        if (!valid()) return;
        void* params[1] = { &d };
        call_method<void>("SetAvatarAudioFarRadius", params, 1);
    }

    void VRCPlayerApi::SetAvatarAudioNearRadius(float d) {
        if (!valid()) return;
        void* params[1] = { &d };
        call_method<void>("SetAvatarAudioNearRadius", params, 1);
    }

    void VRCPlayerApi::SetAvatarAudioVolumetricRadius(float r) {
        if (!valid()) return;
        void* params[1] = { &r };
        call_method<void>("SetAvatarAudioVolumetricRadius", params, 1);
    }

    void VRCPlayerApi::SetAvatarAudioForceSpatial(bool f) {
        if (!valid()) return;
        void* params[1] = { &f };
        call_method<void>("SetAvatarAudioForceSpatial", params, 1);
    }

    void VRCPlayerApi::SetAvatarAudioCustomCurve(bool a) {
        if (!valid()) return;
        void* params[1] = { &a };
        call_method<void>("SetAvatarAudioCustomCurve", params, 1);
    }

    float VRCPlayerApi::GetAvatarEyeHeightAsMeters() {
        if (!valid()) return 0.0f;
        return call_method<float>("GetAvatarEyeHeightAsMeters");
    }

    float VRCPlayerApi::GetAvatarEyeHeightMaximumAsMeters() {
        if (!valid()) return 0.0f;
        return call_method<float>("GetAvatarEyeHeightMaximumAsMeters");
    }

    float VRCPlayerApi::GetAvatarEyeHeightMinimumAsMeters() {
        if (!valid()) return 0.0f;
        return call_method<float>("GetAvatarEyeHeightMinimumAsMeters");
    }

    bool VRCPlayerApi::GetManualAvatarScalingAllowed() {
        if (!valid()) return false;
        return call_method<bool>("GetManualAvatarScalingAllowed");
    }

    void VRCPlayerApi::SetAvatarEyeHeightByMeters(float m) {
        if (!valid()) return;
        void* params[1] = { &m };
        call_method<void>("SetAvatarEyeHeightByMeters", params, 1);
    }

    void VRCPlayerApi::SetAvatarEyeHeightByMultiplier(float m) {
        if (!valid()) return;
        void* params[1] = { &m };
        call_method<void>("SetAvatarEyeHeightByMultiplier", params, 1);
    }

    void VRCPlayerApi::SetAvatarEyeHeightMaximumByMeters(float m) {
        if (!valid()) return;
        void* params[1] = { &m };
        call_method<void>("SetAvatarEyeHeightMaximumByMeters", params, 1);
    }

    void VRCPlayerApi::SetAvatarEyeHeightMinimumByMeters(float m) {
        if (!valid()) return;
        void* params[1] = { &m };
        call_method<void>("SetAvatarEyeHeightMinimumByMeters", params, 1);
    }

    void VRCPlayerApi::SetManualAvatarScalingAllowed(bool e) {
        if (!valid()) return;
        void* params[1] = { &e };
        call_method<void>("SetManualAvatarScalingAllowed", params, 1);
    }

    void VRCPlayerApi::SetNamePlateColor(IL2CPP::Color c) {
        if (!valid()) return;
        void* params[1] = { &c };
        call_method<void>("SetNamePlateColor", params, 1);
    }

    void VRCPlayerApi::RestoreNamePlateColor() {
        if (!valid()) return;
        call_method<void>("RestoreNamePlateColor");
    }

    void VRCPlayerApi::SetNamePlateVisibility(bool f) {
        if (!valid()) return;
        void* params[1] = { &f };
        call_method<void>("SetNamePlateVisibility", params, 1);
    }

    void VRCPlayerApi::RestoreNamePlateVisibility() {
        if (!valid()) return;
        call_method<void>("RestoreNamePlateVisibility");
    }

    bool VRCPlayerApi::IsOwner(IL2CPP::Module::Unity::GameObject obj) {
        if (!valid() || !obj) return false;
        void* params[1] = { obj.raw() };
        return call_method<bool>("IsOwner", params, 1);
    }

    void VRCPlayerApi::TakeOwnership(IL2CPP::Module::Unity::GameObject obj) {
        if (!valid() || !obj) return;
        void* params[1] = { obj.raw() };
        call_method<void>("TakeOwnership", params, 1);
    }

    void VRCPlayerApi::EnablePickups(bool e) {
        if (!valid()) return;
        void* params[1] = { &e };
        call_method<void>("EnablePickups", params, 1);
    }

    IL2CPP::Module::Unity::GameObject VRCPlayerApi::GetGameObject() {
        if (!valid()) return {};
        return get_field<IL2CPP::Module::Unity::GameObject>("gameObject");
    }

    VRCPlayer VRCPlayerApi::GetVRCPlayer() {
        if (!valid()) return {};
        auto go = GetGameObject();
        if (!go) return {};
        auto klass = IL2CPP::Module::Class::find("VRCPlayer");
        if (!klass) return {};
        return VRCPlayer(IL2CPP::Module::Unity::GameObject(go).GetComponent(klass).raw());
    }

    int VRCPlayerApi::GetPlayerCount() {
        if (!Bootstrap::Module::is_connected()) return 0;
        static auto klass = IL2CPP::Module::Class::find("VRC.SDKBase.VRCPlayerApi");
        if (!klass) return 0;
        static auto method = klass.get_method("GetPlayerCount", 0);
        if (!method) return 0;
        void* result = method.invoke(nullptr, nullptr);
        return result ? *reinterpret_cast<int*>(IL2CPP::Unbox(result)) : 0;
    }

    int VRCPlayerApi::GetPlayerId(VRCPlayerApi p) {
        if (!Bootstrap::Module::is_connected() || !p) return -1;
        static auto klass = IL2CPP::Module::Class::find("VRC.SDKBase.VRCPlayerApi");
        if (!klass) return -1;
        static auto method = klass.get_method("GetPlayerId", 1);
        if (!method) return -1;
        void* params[1] = { p.raw() };
        void* result = method.invoke(nullptr, params);
        return result ? *reinterpret_cast<int*>(IL2CPP::Unbox(result)) : -1;
    }

    VRCPlayerApi VRCPlayerApi::GetPlayerByGameObject(IL2CPP::Module::Unity::GameObject o) {
        if (!Bootstrap::Module::is_connected() || !o) return VRCPlayerApi();
        static auto klass = IL2CPP::Module::Class::find("VRC.SDKBase.VRCPlayerApi");
        if (!klass) return VRCPlayerApi();
        static auto method = klass.get_method("GetPlayerByGameObject", 1);
        if (!method) return VRCPlayerApi();
        void* params[1] = { o.raw() };
        void* result = method.invoke(nullptr, params);
        return result ? VRCPlayerApi(result) : VRCPlayerApi();
    }

    VRCPlayerApi VRCPlayerApi::GetPlayerById(int id) {
        if (!Bootstrap::Module::is_connected()) return VRCPlayerApi();
        static auto klass = IL2CPP::Module::Class::find("VRC.SDKBase.VRCPlayerApi");
        if (!klass) return VRCPlayerApi();
        static auto method = klass.get_method("GetPlayerById", 1);
        if (!method) return VRCPlayerApi();
        void* params[1] = { &id };
        void* result = method.invoke(nullptr, params);
        return result ? VRCPlayerApi(result) : VRCPlayerApi();
    }

    VRCPlayerApi VRCPlayerApi::GetLocalPlayer() {
        if (!Bootstrap::Module::is_connected()) return VRCPlayerApi();
        return VRCPlayerApi(Bootstrap::Module::get_vtable()->get_local_player_api());
    }

} // namespace IL2CPP::VRChat
