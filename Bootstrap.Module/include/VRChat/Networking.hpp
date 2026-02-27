#pragma once

// ============================================================================
//  Networking - VRChat SDK Networking static utility class
// ============================================================================

#include "VRCPlayerApi.hpp"
#include <IL2CPP.Module/include/il2cpp_module.hpp>

namespace IL2CPP::VRChat {

    class Networking {
    public:
        // Network State
        [[nodiscard]] static bool IsNetworkSettled();
        [[nodiscard]] static bool IsMaster();
        [[nodiscard]] static bool IsClogged();
        [[nodiscard]] static bool IsInstanceOwner();

        // Player Queries
        [[nodiscard]] static VRCPlayerApi GetLocalPlayer();
        [[nodiscard]] static VRCPlayerApi GetMaster();

        // Time
        [[nodiscard]] static double GetServerTimeInSeconds();
        [[nodiscard]] static int GetServerTimeInMilliseconds();

        // Ownership
        [[nodiscard]] static bool IsOwner(VRCPlayerApi player, IL2CPP::Module::Unity::GameObject obj);
        [[nodiscard]] static bool IsOwner(IL2CPP::Module::Unity::GameObject obj);
        [[nodiscard]] static VRCPlayerApi GetOwner(IL2CPP::Module::Unity::GameObject obj);
        static void SetOwner(VRCPlayerApi player, IL2CPP::Module::Unity::GameObject obj);

    private:
        static IL2CPP::Module::Class klass();
    };

} // namespace IL2CPP::VRChat
