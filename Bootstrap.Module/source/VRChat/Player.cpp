#include <include/VRChat/Player.hpp>
#include <include/VRChat/VRCPlayerApi.hpp>
#include <include/VRChat/VRCPlayer.hpp>
#include <include/VRChat/APIUser.hpp>
#include <include/bootstrap_internal.hpp>

namespace IL2CPP::VRChat {

    Player Player::GetLocalPlayer() {
        if (!Bootstrap::Module::is_connected()) return Player();
        return Player(Bootstrap::Module::get_vtable()->get_local_player());
    }

    VRCPlayerApi Player::GetVRCPlayerApi() {
        if (!valid() || !Bootstrap::Module::is_connected()) return VRCPlayerApi();
        auto* data = Bootstrap::Module::get_vtable()->get_player_data();
        return VRCPlayerApi(*reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(m_native) + data->VRCPlayerApi));
    }

    VRCPlayer Player::GetVRCPlayer() {
        if (!valid() || !Bootstrap::Module::is_connected()) return {};
        auto* data = Bootstrap::Module::get_vtable()->get_player_data();
        return VRCPlayer(*reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(m_native) + data->VRCPlayer));
    }

    APIUser Player::GetAPIUser() {
        if (!valid() || !Bootstrap::Module::is_connected()) return {};
        auto* data = Bootstrap::Module::get_vtable()->get_player_data();
        return APIUser(*reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(m_native) + data->APIUser));
    }

    IL2CPP::Module::ManagedObject Player::GetUSpeaker() {
        if (!valid() || !Bootstrap::Module::is_connected()) return {};
        auto* data = Bootstrap::Module::get_vtable()->get_player_data();
        return IL2CPP::Module::ManagedObject(*reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(m_native) + data->USpeaker));
    }

    PlayerRank Player::GetPlayerRank() {
        if (!valid() || !Bootstrap::Module::is_connected()) return PlayerRank::Visitor;
        return static_cast<PlayerRank>(
            Bootstrap::Module::get_vtable()->get_player_rank(m_native));
    }

    Bootstrap::Color Player::GetRankColor(PlayerRank rank) {
        Bootstrap::Color c{ 1.f, 1.f, 1.f, 1.f };
        if (!Bootstrap::Module::is_connected()) return c;
        Bootstrap::Module::get_vtable()->get_rank_color(
            static_cast<uint8_t>(rank), &c.r, &c.g, &c.b, &c.a);
        return c;
    }

} // namespace IL2CPP::VRChat
