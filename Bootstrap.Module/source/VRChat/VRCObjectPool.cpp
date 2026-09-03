#include <VRChat/VRCObjectPool.hpp>
#include <IL2CPP.Module/include/System/String.hpp>

namespace IL2CPP::VRChat {

    IL2CPP::Module::Unity::GameObject VRCObjectPool::TryToSpawn() {
        return IL2CPP::Module::Unity::GameObject(call_method<void*>("TryToSpawn", nullptr, 0));
    }

    void VRCObjectPool::Return(IL2CPP::Module::Unity::GameObject obj) {
        if (!obj) return;
        void* params[1] = { obj.raw() };
        call_method<void>("Return", params, 1);
    }

    void VRCObjectPool::Shuffle() {
        call_method<void>("Shuffle", nullptr, 0);
    }

    void* VRCObjectPool::GetPoolArray() {
        return get_field<void*>("Pool");
    }

    std::string VRCPortalMarker::GetRoomId() {
        return get_string_field("roomId");
    }

    std::string VRCPortalMarker::GetRoomName() {
        return get_string_field("roomName");
    }

    int VRCPortalMarker::GetPlayerCount() {
        return get_field<int>("playerCount");
    }

    int VRCPortalMarker::GetCapacity() {
        return get_field<int>("capacity");
    }

    bool VRCPortalMarker::IsValid() {
        return get_field<bool>("isValid");
    }

    void VRCPortalMarker::RefreshPortal() {
        call_method<void>("RefreshPortal", nullptr, 0);
    }

    VRCUrl VRCUrl::Create(std::string_view url) {
        auto klass = IL2CPP::Module::Class::find("VRC.SDKBase.VRCUrl");
        if (!klass) return {};
        auto str = IL2CPP::Module::System::String::create(url);
        if (!str) return {};
        void* params[1] = { str.raw() };
        return VRCUrl(klass.new_instance(params, 1).raw());
    }

    std::string VRCUrl::Get() {
        return call_string_method("Get", nullptr, 0);
    }

} // namespace IL2CPP::VRChat
