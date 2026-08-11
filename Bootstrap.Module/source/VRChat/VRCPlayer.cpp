#include <VRChat/VRCPlayer.hpp>
#include <VRChat/VRCPlayerApi.hpp>
#include <VRChat/Player.hpp>
#include <VRChat/PlayerNameplate.hpp>
#include <bootstrap_internal.hpp>
#include <IL2CPP.Module/include/MethodHandler.hpp>
#include <IL2CPP.Module/include/System/String.hpp>

namespace IL2CPP::VRChat {

    namespace {
        std::string invoke_string_getter(void* methodInfo, void* instance) {
            if (!methodInfo || !instance) return "";
            void* str = IL2CPP::Module::MethodHandler::invoke<void*>(
                IL2CPP::Module::Method(methodInfo), instance);
            return str ? IL2CPP::Module::System::String(str).to_string() : "";
        }
    }

    VRCPlayer VRCPlayer::GetLocalPlayer() {
        if (!Bootstrap::Module::is_connected()) return VRCPlayer();
        return VRCPlayer(Bootstrap::Module::get_vtable()->get_local_vrc_player());
    }

    VRCPlayerApi VRCPlayer::GetVRCPlayerApi() {
        if (!valid() || !Bootstrap::Module::is_connected()) return VRCPlayerApi();
        auto* data = Bootstrap::Module::get_vtable()->get_vrc_player_data();
        return VRCPlayerApi(*reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(raw()) + data->VRCPlayerApi));
    }

    Player VRCPlayer::GetPlayer() {
        if (!valid() || !Bootstrap::Module::is_connected()) return Player();
        auto* data = Bootstrap::Module::get_vtable()->get_vrc_player_data();
        return Player(*reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(raw()) + data->Player));
    }

    PlayerNameplate VRCPlayer::GetNameplate() {
        if (!valid() || !Bootstrap::Module::is_connected()) return {};
        auto* data = Bootstrap::Module::get_vtable()->get_vrc_player_data();
        if (!data->PlayerNameplate) return {};
        return PlayerNameplate(*reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(raw()) + data->PlayerNameplate));
    }

    std::string VRCPlayer::GetUsername() {
        if (!valid() || !Bootstrap::Module::is_connected()) return "";
        return invoke_string_getter(
            Bootstrap::Module::get_vtable()->get_vrc_player_data()->get_username, raw());
    }

    std::string VRCPlayer::GetDisplayName() {
        if (!valid() || !Bootstrap::Module::is_connected()) return "";
        return invoke_string_getter(
            Bootstrap::Module::get_vtable()->get_vrc_player_data()->get_displayName, raw());
    }

    std::string VRCPlayer::GetUserId() {
        if (!valid() || !Bootstrap::Module::is_connected()) return "";
        return invoke_string_getter(
            Bootstrap::Module::get_vtable()->get_vrc_player_data()->get_userId, raw());
    }

    std::string VRCPlayer::GetPronouns() {
        if (!valid() || !Bootstrap::Module::is_connected()) return "";
        return invoke_string_getter(
            Bootstrap::Module::get_vtable()->get_vrc_player_data()->get_pronouns, raw());
    }

    IL2CPP::Module::Unity::Animator VRCPlayer::GetAnimator() {
        if (!valid() || !Bootstrap::Module::is_connected()) return {};
        auto* data = Bootstrap::Module::get_vtable()->get_vrc_player_data();
        if (!data->Animator) return {};
        return IL2CPP::Module::Unity::Animator(
            *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(raw()) + data->Animator));
    }

} // namespace IL2CPP::VRChat
