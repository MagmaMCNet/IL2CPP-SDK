#pragma once

// ============================================================================
//  VRChat Callbacks - Typed callback aliases for VRChat events
//
//  These are ABI-compatible with the void*-based callbacks in bootstrap_shared.hpp
//  on MSVC x64 (Player/VRCPlayerApi are trivial void* wrappers).
// ============================================================================

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
