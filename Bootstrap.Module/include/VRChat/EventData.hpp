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

        /// <summary>Read one entry of the event's parameter dictionary.</summary>
        /// <param name="key">Parameter code. GetCustomDataKey() is the one holding the payload.</param>
        /// <returns>The boxed value, or nullptr when the event carries no such parameter.</returns>
        [[nodiscard]] void* GetParameter(uint8_t key);

        /// <summary>Number of parameters on this event.</summary>
        [[nodiscard]] int GetParameterCount();

        void SetSender(int sender);

        /// <summary>Clear the event so the instance can be reused for the next one.</summary>
        void Reset();
    };

} // namespace IL2CPP::VRChat
