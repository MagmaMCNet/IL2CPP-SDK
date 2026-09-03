#pragma once

#include <IL2CPP.Module/include/il2cpp_module.hpp>
#include <IL2CPP.Module/include/Unity/Transform.hpp>

namespace IL2CPP::VRChat {

    class VRCObjectSync : public IL2CPP::Module::Unity::MonoBehaviour {
    public:
        using MonoBehaviour::MonoBehaviour;

        void TeleportTo(IL2CPP::Module::Unity::Transform target);
        void SetGravity(bool value);
        void SetKinematic(bool value);
        void Respawn();
        void FlagDiscontinuity();
        [[nodiscard]] bool GetAllowCollisionOwnershipTransfer();
    };

} // namespace IL2CPP::VRChat
