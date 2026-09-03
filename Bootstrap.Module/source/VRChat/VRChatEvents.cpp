#include <VRChat/VRChatEvents.hpp>
#include <VRChat/HostBridge.hpp>

namespace IL2CPP::VRChat {

    namespace {
        void UNIX_CC forward_player_event(void* ud, const unix_player_ev* ev) {
            if (!ud || !ev) return;
            reinterpret_cast<PlayerCallback>(ud)(Player(ev->player));
        }

        uint32_t subscribe(unix_player_phase phase, PlayerCallback callback) {
            if (!callback) return 0;
            return Bridge::OnPlayerEvent(1u << static_cast<uint32_t>(phase), &forward_player_event,
                                         reinterpret_cast<void*>(callback));
        }
    }

    VRChatEvents& VRChatEvents::Get() {
        static VRChatEvents instance;
        return instance;
    }

    uint32_t VRChatEvents::RegisterOnAwake(PlayerCallback callback) {
        return subscribe(unix_player_awake, callback);
    }

    uint32_t VRChatEvents::RegisterOnJoin(PlayerCallback callback) {
        return subscribe(unix_player_joined, callback);
    }

    uint32_t VRChatEvents::RegisterOnJoinComplete(PlayerCallback callback) {
        return subscribe(unix_player_joined_complete, callback);
    }

    uint32_t VRChatEvents::RegisterOnLeave(PlayerCallback callback) {
        return subscribe(unix_player_left, callback);
    }

    void VRChatEvents::Unregister(uint32_t handle) {
        if (handle != unix_null) Bridge::Cancel(handle);
    }

} // namespace IL2CPP::VRChat
