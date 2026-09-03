#pragma once

#include <IL2CPP.Module/include/il2cpp_module.hpp>
#include <unix/unix_types.hpp>

namespace IL2CPP::VRChat {

    class VRCPlayerApi;
    class VRCPlayer;
    class APIUser;

    using PlayerRank = UNIx::PlayerRank;

    class Player : public IL2CPP::Module::Unity::MonoBehaviour {
    public:
        using MonoBehaviour::MonoBehaviour;

        [[nodiscard]] VRCPlayerApi GetVRCPlayerApi();
        [[nodiscard]] VRCPlayer GetVRCPlayer();
        [[nodiscard]] APIUser GetAPIUser();
        [[nodiscard]] IL2CPP::Module::ManagedObject GetUSpeaker();

        [[nodiscard]] PlayerRank GetPlayerRank();
        [[nodiscard]] static unix_color GetRankColor(PlayerRank rank);

        static Player GetLocalPlayer();
    };

} // namespace IL2CPP::VRChat
