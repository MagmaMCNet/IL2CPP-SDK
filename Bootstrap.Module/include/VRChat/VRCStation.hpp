#pragma once

#include "VRCPlayerApi.hpp"
#include "Enums.hpp"
#include <IL2CPP.Module/include/il2cpp_module.hpp>

namespace IL2CPP::VRChat {

    class VRCStation : public IL2CPP::Module::Unity::MonoBehaviour {
    public:
        using MonoBehaviour::MonoBehaviour;

        void UseStation(VRCPlayerApi player);
        void ExitStation(VRCPlayerApi player);

        [[nodiscard]] StationMobility GetPlayerMobility();
        void SetPlayerMobility(StationMobility mobility);
        [[nodiscard]] bool GetSeated();
        void SetSeated(bool value);
        [[nodiscard]] bool GetDisableStationExit();
        void SetDisableStationExit(bool value);
        [[nodiscard]] bool GetCanUseStationFromStation();
    };

} // namespace IL2CPP::VRChat
