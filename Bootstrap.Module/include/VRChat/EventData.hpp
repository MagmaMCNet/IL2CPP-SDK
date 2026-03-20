#pragma once

#include <IL2CPP.Module/include/il2cpp_module.hpp>
#include <cstdint>

namespace IL2CPP::VRChat {

    class EventData : public IL2CPP::Module::ManagedObject {
    public:
        using ManagedObject::ManagedObject;

        [[nodiscard]] uint8_t GetCode();
        [[nodiscard]] void* GetParameters();
        [[nodiscard]] uint8_t GetSenderKey();
        [[nodiscard]] int GetSender();
        [[nodiscard]] uint8_t GetCustomDataKey();
        [[nodiscard]] void* GetCustomData();
    };

} // namespace IL2CPP::VRChat
