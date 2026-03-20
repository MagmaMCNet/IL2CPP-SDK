#pragma once

#include <IL2CPP.Module/include/il2cpp_module.hpp>
#include <Bootstrap.Common/include/bootstrap_shared.hpp>

namespace IL2CPP::VRChat {

    class VRCPlayerApi;
    class VRCPlayer;
    class APIUser;

    using PlayerRank = Bootstrap::PlayerRank;

    class Player : public IL2CPP::Module::Unity::MonoBehaviour {
    public:
        using MonoBehaviour::MonoBehaviour;

        [[nodiscard]] VRCPlayerApi GetVRCPlayerApi();
        [[nodiscard]] VRCPlayer GetVRCPlayer();
        [[nodiscard]] APIUser GetAPIUser();
        [[nodiscard]] IL2CPP::Module::ManagedObject GetUSpeaker();

        [[nodiscard]] PlayerRank GetPlayerRank();
        [[nodiscard]] static Bootstrap::Color GetRankColor(PlayerRank rank);

        static Player GetLocalPlayer();
    };

} // namespace IL2CPP::VRChat
