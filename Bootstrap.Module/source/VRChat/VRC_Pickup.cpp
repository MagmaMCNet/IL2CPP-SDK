#include <VRChat/VRC_Pickup.hpp>

namespace IL2CPP::VRChat {

    bool VRC_Pickup::IsHeld() {
        return call_method<bool>("get_IsHeld", nullptr, 0);
    }

    VRCPlayerApi VRC_Pickup::GetCurrentPlayer() {
        return VRCPlayerApi(call_method<void*>("get_currentPlayer", nullptr, 0));
    }

    PickupHand VRC_Pickup::GetCurrentHand() {
        return static_cast<PickupHand>(call_method<int>("get_currentHand", nullptr, 0));
    }

    bool VRC_Pickup::GetPickupable() {
        return get_field<bool>("pickupable");
    }

    void VRC_Pickup::SetPickupable(bool value) {
        set_field("pickupable", value);
    }

    std::string VRC_Pickup::GetUseText() {
        return get_string_field("UseText");
    }

    void VRC_Pickup::SetUseText(std::string_view text) {
        set_string_field("UseText", text);
    }

    bool VRC_Pickup::GetDisallowTheft() {
        return get_field<bool>("DisallowTheft");
    }

    void VRC_Pickup::SetDisallowTheft(bool value) {
        set_field("DisallowTheft", value);
    }

    AutoHoldMode VRC_Pickup::GetAutoHold() {
        return static_cast<AutoHoldMode>(get_field<int>("AutoHold"));
    }

    void VRC_Pickup::SetAutoHold(AutoHoldMode mode) {
        set_field("AutoHold", static_cast<int>(mode));
    }

    PickupOrientation VRC_Pickup::GetOrientation() {
        return static_cast<PickupOrientation>(get_field<int>("orientation"));
    }

    void VRC_Pickup::SetOrientation(PickupOrientation orientation) {
        set_field("orientation", static_cast<int>(orientation));
    }

    void VRC_Pickup::Drop() {
        call_method<void>("Drop", nullptr, 0);
    }

    void VRC_Pickup::GenerateHapticEvent(float duration, float amplitude, float frequency) {
        void* params[3] = { &duration, &amplitude, &frequency };
        call_method<void>("GenerateHapticEvent", params, 3);
    }

} // namespace IL2CPP::VRChat
