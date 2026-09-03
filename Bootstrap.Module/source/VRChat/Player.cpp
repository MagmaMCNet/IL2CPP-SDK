#include <VRChat/Player.hpp>
#include <VRChat/VRCPlayerApi.hpp>
#include <VRChat/VRCPlayer.hpp>
#include <VRChat/APIUser.hpp>
#include <VRChat/HostBridge.hpp>

namespace IL2CPP::VRChat {

    namespace {
        std::optional<unix_player_offsets> player_table() {
            return Bridge::Offsets<unix_player_offsets>(unix_offsets_player);
        }
    }

    Player Player::GetLocalPlayer() {
        return Player(Bridge::LocalPlayer());
    }

    VRCPlayerApi Player::GetVRCPlayerApi() {
        if (!valid()) return {};
        const auto o = player_table();
        if (!o) return {};
        return VRCPlayerApi(Bridge::MemberAt(raw(), o->vrc_player_api));
    }

    VRCPlayer Player::GetVRCPlayer() {
        if (!valid()) return {};
        const auto o = player_table();
        if (!o) return {};
        return VRCPlayer(Bridge::MemberAt(raw(), o->vrc_player));
    }

    APIUser Player::GetAPIUser() {
        if (!valid()) return {};
        const auto o = player_table();
        if (!o) return {};
        return APIUser(Bridge::MemberAt(raw(), o->api_user));
    }

    IL2CPP::Module::ManagedObject Player::GetUSpeaker() {
        if (!valid()) return {};
        const auto o = player_table();
        if (!o) return {};
        return IL2CPP::Module::ManagedObject(Bridge::MemberAt(raw(), o->uspeaker));
    }

    PlayerRank Player::GetPlayerRank() {
        if (!valid()) return PlayerRank::Visitor;
        return static_cast<PlayerRank>(Bridge::Rank(GetAPIUser().raw()));
    }

    unix_color Player::GetRankColor(PlayerRank rank) {
        const unix_color c = Bridge::RankColor(static_cast<uint32_t>(rank));
        if (c.a <= 0.f) return unix_color{ 1.f, 1.f, 1.f, 1.f };
        return c;
    }

} // namespace IL2CPP::VRChat
