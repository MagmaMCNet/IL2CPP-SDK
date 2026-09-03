#include <VRChat/VRCObjectSync.hpp>

namespace IL2CPP::VRChat {

    void VRCObjectSync::TeleportTo(IL2CPP::Module::Unity::Transform target) {
        if (!target) return;
        void* params[1] = { target.raw() };
        call_method<void>("TeleportTo", params, 1);
    }

    void VRCObjectSync::SetGravity(bool value) {
        void* params[1] = { &value };
        call_method<void>("SetGravity", params, 1);
    }

    void VRCObjectSync::SetKinematic(bool value) {
        void* params[1] = { &value };
        call_method<void>("SetKinematic", params, 1);
    }

    void VRCObjectSync::Respawn() {
        call_method<void>("Respawn", nullptr, 0);
    }

    void VRCObjectSync::FlagDiscontinuity() {
        call_method<void>("FlagDiscontinuity", nullptr, 0);
    }

    bool VRCObjectSync::GetAllowCollisionOwnershipTransfer() {
        return get_field<bool>("AllowCollisionOwnershipTransfer");
    }

} // namespace IL2CPP::VRChat
