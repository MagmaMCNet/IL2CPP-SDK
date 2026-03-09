#pragma once

// ============================================================================
//  VRChat.hpp - Master include for all VRChat class wrappers
//
//  Usage:
//      #include <VRChat/VRChat.hpp>
//      auto player = IL2CPP::VRChat::VRCPlayerApi::GetLocalPlayer();
//      auto name = player.GetDisplayName();
// ============================================================================

#include <IL2CPP.Module/include/il2cpp_module.hpp>
#include "Enums.hpp"
#include "Callbacks.hpp"
#include "VRCPlayerApi.hpp"
#include "Player.hpp"
#include "VRCPlayer.hpp"
#include "ApiModel.hpp"
#include "ApiBadge.hpp"
#include "APIUser.hpp"
#include "EventData.hpp"
#include "Networking.hpp"
#include "PlayerNameplate.hpp"
#include "VRC_Interactable.hpp"
#include "UdonBehaviour.hpp"
#include "VRChatEvents.hpp"
#include "LocalizableString.hpp"
