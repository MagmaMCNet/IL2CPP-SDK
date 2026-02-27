#pragma once

// ============================================================================
//  VRChatEvents - Player lifecycle event registration
// ============================================================================

#include "Callbacks.hpp"
#include <Bootstrap.Common/include/bootstrap_shared.hpp>
#include <cstdint>

namespace IL2CPP::VRChat {

    class VRChatEvents {
    public:
        static VRChatEvents& Get();

        uint32_t register_on_awake(uint32_t module_id, PlayerCallback callback);
        uint32_t register_on_join(uint32_t module_id, PlayerCallback callback);
        uint32_t register_on_join_complete(uint32_t module_id, PlayerCallback callback);
        uint32_t register_on_leave(uint32_t module_id, PlayerCallback callback);

        void unregister_callback(uint32_t module_id, uint32_t callback_id);

        [[nodiscard]] bool valid() const noexcept;

    private:
        VRChatEvents() = default;
    };

} // namespace IL2CPP::VRChat
