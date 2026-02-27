#include <include/VRChat/UdonBehaviour.hpp>
#include <IL2CPP.Module/include/System/String.hpp>
#include <IL2CPP.Module/include/ManagedObject.hpp>

namespace IL2CPP::VRChat {

    bool UdonBehaviour::GetSynchronizePosition() {
        if (!valid()) return false;
        return get_field<bool>("SynchronizePosition");
    }

    bool UdonBehaviour::GetSynchronizeAnimation() {
        if (!valid()) return false;
        return get_field<bool>("SynchronizeAnimation");
    }

    bool UdonBehaviour::GetReliable() {
        if (!valid()) return false;
        return get_field<bool>("Reliable");
    }

    SyncType UdonBehaviour::GetSyncMethod() {
        if (!valid()) return SyncType::Unknown;
        return get_field<SyncType>("_syncMethod");
    }

    bool UdonBehaviour::GetIsReady() {
        if (!valid()) return false;
        return get_field<bool>("_isReady");
    }

    bool UdonBehaviour::GetHasError() {
        if (!valid()) return false;
        return get_field<bool>("_hasError");
    }

    bool UdonBehaviour::GetInitialized() {
        if (!valid()) return false;
        return get_field<bool>("_initialized");
    }

    void UdonBehaviour::SendCustomEvent(std::string_view eventName) {
        if (!valid()) return;
        auto str = IL2CPP::Module::System::String::create(eventName);
        void* params[1] = { str.raw() };
        call_method<void>("SendCustomEvent", params, 1);
    }

    void UdonBehaviour::SendCustomNetworkEvent(NetworkEventTarget target, std::string_view eventName) {
        if (!valid()) return;
        auto str = IL2CPP::Module::System::String::create(eventName);
        int iTarget = static_cast<int>(target);
        void* params[2] = { &iTarget, str.raw() };
        call_method<void>("SendCustomNetworkEvent", params, 2);
    }

    void UdonBehaviour::RequestSerialization() {
        if (!valid()) return;
        call_method<void>("RequestSerialization");
    }

    void UdonBehaviour::SendCustomEventDelayedSeconds(std::string_view eventName, float delaySeconds, EventTiming eventTiming) {
        if (!valid()) return;
        auto str = IL2CPP::Module::System::String::create(eventName);
        int iTiming = static_cast<int>(eventTiming);
        void* params[3] = { str.raw(), &delaySeconds, &iTiming };
        call_method<void>("SendCustomEventDelayedSeconds", params, 3);
    }

    void UdonBehaviour::SendCustomEventDelayedFrames(std::string_view eventName, int delayFrames, EventTiming eventTiming) {
        if (!valid()) return;
        auto str = IL2CPP::Module::System::String::create(eventName);
        int iTiming = static_cast<int>(eventTiming);
        void* params[3] = { str.raw(), &delayFrames, &iTiming };
        call_method<void>("SendCustomEventDelayedFrames", params, 3);
    }

    std::string UdonBehaviour::GetInteractionText() {
        return call_string_method("get_InteractionText");
    }

    void UdonBehaviour::SetInteractionText(std::string_view text) {
        if (!valid()) return;
        auto str = IL2CPP::Module::System::String::create(text);
        void* params[1] = { str.raw() };
        call_method<void>("set_InteractionText", params, 1);
    }

    void UdonBehaviour::SetProgramVariable(std::string_view symbolName, void* value) {
        if (!valid()) return;
        auto str = IL2CPP::Module::System::String::create(symbolName);
        void* params[2] = { str.raw(), value };
        call_method<void>("SetProgramVariable", params, 2);
    }

    void* UdonBehaviour::GetProgramVariable(std::string_view symbolName) {
        if (!valid()) return nullptr;
        auto str = IL2CPP::Module::System::String::create(symbolName);
        void* params[1] = { str.raw() };
        return call_method<void*>("GetProgramVariable", params, 1);
    }

    bool UdonBehaviour::TryGetVariableValue(std::string_view symbolName, void** value) {
        if (!valid() || !value) return false;
        auto* table = get_field<void*>("publicVariables");
        if (!table) return false;
        IL2CPP::Module::ManagedObject tableObj(table);
        auto str = IL2CPP::Module::System::String::create(symbolName);
        void* params[2] = { str.raw(), value };
        return tableObj.call_method<bool>("TryGetVariableValue", params, 2);
    }

    bool UdonBehaviour::TrySetVariableValue(std::string_view symbolName, void* value) {
        if (!valid()) return false;
        auto* table = get_field<void*>("publicVariables");
        if (!table) return false;
        IL2CPP::Module::ManagedObject tableObj(table);
        auto str = IL2CPP::Module::System::String::create(symbolName);
        void* params[2] = { str.raw(), value };
        return tableObj.call_method<bool>("TrySetVariableValue", params, 2);
    }

} // namespace IL2CPP::VRChat
