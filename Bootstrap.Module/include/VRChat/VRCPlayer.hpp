#pragma once

#include <IL2CPP.Module/include/il2cpp_module.hpp>
#include <string>

namespace IL2CPP::VRChat {

    class VRCPlayerApi;
    class Player;
    class PlayerNameplate;

    class VRCPlayer : public IL2CPP::Module::Unity::MonoBehaviour {
    public:
        using MonoBehaviour::MonoBehaviour;

        [[nodiscard]] VRCPlayerApi GetVRCPlayerApi();
        [[nodiscard]] Player GetPlayer();
        [[nodiscard]] PlayerNameplate GetNameplate();

        // Straight off VRCPlayer -- no APIUser round-trip, so these work for
        // remote players whose APIUser has not been fetched.
        [[nodiscard]] std::string GetUsername();
        [[nodiscard]] std::string GetDisplayName();
        [[nodiscard]] std::string GetUserId();
        [[nodiscard]] std::string GetPronouns();

        [[nodiscard]] IL2CPP::Module::Unity::Animator GetAnimator();

        static VRCPlayer GetLocalPlayer();
    };

} // namespace IL2CPP::VRChat
