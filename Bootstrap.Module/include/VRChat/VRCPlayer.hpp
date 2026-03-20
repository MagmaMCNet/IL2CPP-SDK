#pragma once

#include <IL2CPP.Module/include/il2cpp_module.hpp>

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

        static VRCPlayer GetLocalPlayer();
    };

} // namespace IL2CPP::VRChat
