#include <VRChat/VRC_SceneDescriptor.hpp>

namespace IL2CPP::VRChat {

    VRC_SceneDescriptor VRC_SceneDescriptor::Instance() {
        auto klass = IL2CPP::Module::Class::find("VRC.SDKBase.VRC_SceneDescriptor");
        if (!klass) return {};
        auto field = klass.get_field("Instance");
        if (!field) return {};
        void* value = nullptr;
        field.get_static_value(&value);
        return VRC_SceneDescriptor(value);
    }

    float VRC_SceneDescriptor::GetRespawnHeight() {
        return get_field<float>("RespawnHeightY");
    }

    void* VRC_SceneDescriptor::GetSpawnsArray() {
        return get_field<void*>("spawns");
    }

    SpawnOrder VRC_SceneDescriptor::GetSpawnOrder() {
        return static_cast<SpawnOrder>(get_field<int>("spawnOrder"));
    }

    SpawnOrientation VRC_SceneDescriptor::GetSpawnOrientation() {
        return static_cast<SpawnOrientation>(get_field<int>("spawnOrientation"));
    }

    IL2CPP::Module::Unity::GameObject VRC_SceneDescriptor::GetReferenceCamera() {
        return get_field<IL2CPP::Module::Unity::GameObject>("ReferenceCamera");
    }

} // namespace IL2CPP::VRChat
