#include <VRChat/VRCStation.hpp>

namespace IL2CPP::VRChat {

    void VRCStation::UseStation(VRCPlayerApi player) {
        if (!player) return;
        void* params[1] = { player.raw() };
        call_method<void>("UseStation", params, 1);
    }

    void VRCStation::ExitStation(VRCPlayerApi player) {
        if (!player) return;
        void* params[1] = { player.raw() };
        call_method<void>("ExitStation", params, 1);
    }

    StationMobility VRCStation::GetPlayerMobility() {
        return static_cast<StationMobility>(get_field<int>("PlayerMobility"));
    }

    void VRCStation::SetPlayerMobility(StationMobility mobility) {
        set_field("PlayerMobility", static_cast<int>(mobility));
    }

    bool VRCStation::GetSeated() {
        return get_field<bool>("seated");
    }

    void VRCStation::SetSeated(bool value) {
        set_field("seated", value);
    }

    bool VRCStation::GetDisableStationExit() {
        return get_field<bool>("disableStationExit");
    }

    void VRCStation::SetDisableStationExit(bool value) {
        set_field("disableStationExit", value);
    }

    bool VRCStation::GetCanUseStationFromStation() {
        return get_field<bool>("canUseStationFromStation");
    }

} // namespace IL2CPP::VRChat
