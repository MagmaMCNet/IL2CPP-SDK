#pragma once

#include "VRCPlayerApi.hpp"
#include "Player.hpp"

namespace IL2CPP::VRChat {

    // Player event callback (typed alternative to Bootstrap::fn_player_simple_callback)
    using PlayerCallback = void(__cdecl*)(Player player);

    // Explorer navigation callback (typed alternative to Bootstrap::fn_explorer_navigate_callback)
    using ExplorerNavigateCallback = void(__cdecl*)(
        IL2CPP::Module::Unity::GameObject gameObject,
        IL2CPP::Module::ManagedObject component);

} // namespace IL2CPP::VRChat
