#pragma once

#include "Callbacks.hpp"
#include <cstdint>

namespace IL2CPP::VRChat {

    /// <summary>Player lifecycle notifications. A module written against the SDK overrides
    /// UNIx::Module::OnPlayerJoined and friends instead; this is the raw-callback form for
    /// consumers that are not UNIx::Module subclasses.</summary>
    class VRChatEvents {
    public:
        static VRChatEvents& Get();

        /// <returns>A subscription handle for Unregister, or 0 when the host refused.</returns>
        uint32_t RegisterOnAwake(PlayerCallback callback);
        uint32_t RegisterOnJoin(PlayerCallback callback);
        uint32_t RegisterOnJoinComplete(PlayerCallback callback);
        uint32_t RegisterOnLeave(PlayerCallback callback);

        /// <param name="handle">A handle from one of the Register calls.</param>
        void Unregister(uint32_t handle);

    private:
        VRChatEvents() = default;
    };

} // namespace IL2CPP::VRChat
