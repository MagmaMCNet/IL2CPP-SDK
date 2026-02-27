#pragma once

// ============================================================================
//  UdonBehaviour - VRChat Udon scripting behaviour
// ============================================================================

#include "VRC_Interactable.hpp"
#include "Enums.hpp"
#include <string>
#include <string_view>

namespace IL2CPP::VRChat {

    class UdonBehaviour : public VRC_Interactable {
    public:
        using VRC_Interactable::VRC_Interactable;

        // Field Getters
        [[nodiscard]] bool GetSynchronizePosition();
        [[nodiscard]] bool GetSynchronizeAnimation();
        [[nodiscard]] bool GetReliable();
        [[nodiscard]] SyncType GetSyncMethod();
        [[nodiscard]] bool GetIsReady();
        [[nodiscard]] bool GetHasError();
        [[nodiscard]] bool GetInitialized();

        // Events
        void SendCustomEvent(std::string_view eventName);
        void SendCustomNetworkEvent(NetworkEventTarget target, std::string_view eventName);
        void RequestSerialization();
        void SendCustomEventDelayedSeconds(std::string_view eventName, float delaySeconds, EventTiming eventTiming = EventTiming::Update);
        void SendCustomEventDelayedFrames(std::string_view eventName, int delayFrames, EventTiming eventTiming = EventTiming::Update);

        // Interaction
        [[nodiscard]] std::string GetInteractionText();
        void SetInteractionText(std::string_view text);

        // Variables
        void SetProgramVariable(std::string_view symbolName, void* value);
        [[nodiscard]] void* GetProgramVariable(std::string_view symbolName);
        [[nodiscard]] bool TryGetVariableValue(std::string_view symbolName, void** value);
        [[nodiscard]] bool TrySetVariableValue(std::string_view symbolName, void* value);
    };

} // namespace IL2CPP::VRChat
