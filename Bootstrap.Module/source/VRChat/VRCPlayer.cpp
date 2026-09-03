#include <VRChat/VRCPlayer.hpp>
#include <VRChat/VRCPlayerApi.hpp>
#include <VRChat/Player.hpp>
#include <VRChat/PlayerNameplate.hpp>
#include <VRChat/HostBridge.hpp>

namespace IL2CPP::VRChat {

    namespace {
        std::optional<unix_vrc_player_offsets> vrc_player_table() {
            return Bridge::Offsets<unix_vrc_player_offsets>(unix_offsets_vrc_player);
        }
    }

    VRCPlayer VRCPlayer::GetLocalPlayer() {
        return VRCPlayer(Bridge::LocalVrcPlayer());
    }

    VRCPlayerApi VRCPlayer::GetVRCPlayerApi() {
        if (!valid()) return {};
        const auto o = vrc_player_table();
        if (!o) return {};
        return VRCPlayerApi(Bridge::MemberAt(raw(), o->vrc_player_api));
    }

    Player VRCPlayer::GetPlayer() {
        if (!valid()) return {};
        const auto o = vrc_player_table();
        if (!o) return {};
        return Player(Bridge::MemberAt(raw(), o->player));
    }

    PlayerNameplate VRCPlayer::GetNameplate() {
        if (!valid()) return {};
        const auto o = vrc_player_table();
        if (!o) return {};
        return PlayerNameplate(Bridge::MemberAt(raw(), o->player_nameplate));
    }

    std::string VRCPlayer::GetUsername() {
        if (!valid()) return {};
        return Bridge::VrcPlayerString(raw(), Bridge::kStrUsername);
    }

    std::string VRCPlayer::GetDisplayName() {
        if (!valid()) return {};
        return Bridge::VrcPlayerString(raw(), Bridge::kStrDisplayName);
    }

    std::string VRCPlayer::GetUserId() {
        if (!valid()) return {};
        return Bridge::VrcPlayerString(raw(), Bridge::kStrUserId);
    }

    std::string VRCPlayer::GetPronouns() {
        if (!valid()) return {};
        return Bridge::VrcPlayerString(raw(), Bridge::kStrPronouns);
    }

    IL2CPP::Module::Unity::Animator VRCPlayer::GetAnimator() {
        if (!valid()) return {};
        const auto o = vrc_player_table();
        if (!o) return {};
        return IL2CPP::Module::Unity::Animator(Bridge::MemberAt(raw(), o->animator));
    }

} // namespace IL2CPP::VRChat
