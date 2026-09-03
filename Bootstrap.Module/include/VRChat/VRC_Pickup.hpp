#pragma once

#include "VRC_Interactable.hpp"
#include "VRCPlayerApi.hpp"
#include "Enums.hpp"
#include <string>
#include <string_view>

namespace IL2CPP::VRChat {

    class VRC_Pickup : public VRC_Interactable {
    public:
        using VRC_Interactable::VRC_Interactable;

        [[nodiscard]] bool IsHeld();
        [[nodiscard]] VRCPlayerApi GetCurrentPlayer();
        [[nodiscard]] PickupHand GetCurrentHand();

        [[nodiscard]] bool GetPickupable();
        void SetPickupable(bool value);
        [[nodiscard]] std::string GetUseText();
        void SetUseText(std::string_view text);
        [[nodiscard]] bool GetDisallowTheft();
        void SetDisallowTheft(bool value);
        [[nodiscard]] AutoHoldMode GetAutoHold();
        void SetAutoHold(AutoHoldMode mode);
        [[nodiscard]] PickupOrientation GetOrientation();
        void SetOrientation(PickupOrientation orientation);

        void Drop();
        void GenerateHapticEvent(float duration, float amplitude, float frequency);
    };

} // namespace IL2CPP::VRChat
