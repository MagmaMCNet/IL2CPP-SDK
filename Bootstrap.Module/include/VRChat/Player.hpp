#pragma once

// ============================================================================
//  Player - VRChat Player MonoBehaviour wrapper
// ============================================================================

#include <IL2CPP.Module/include/il2cpp_module.hpp>

namespace IL2CPP::VRChat {

    class VRCPlayerApi;
    class VRCPlayer;
    class APIUser;

    class Player : public IL2CPP::Module::Unity::MonoBehaviour {
    public:
        using MonoBehaviour::MonoBehaviour;

        [[nodiscard]] VRCPlayerApi GetVRCPlayerApi();
        [[nodiscard]] VRCPlayer GetVRCPlayer();
        [[nodiscard]] APIUser GetAPIUser();
        [[nodiscard]] IL2CPP::Module::ManagedObject GetUSpeaker();

        static Player GetLocalPlayer();
    };

} // namespace IL2CPP::VRChat
