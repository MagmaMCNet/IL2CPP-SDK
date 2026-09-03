#pragma once

#include <IL2CPP.Module/include/il2cpp_module.hpp>
#include <IL2CPP.Module/include/Unity/GameObject.hpp>
#include <string>
#include <string_view>

namespace IL2CPP::VRChat {

    class VRCObjectPool : public IL2CPP::Module::Unity::MonoBehaviour {
    public:
        using MonoBehaviour::MonoBehaviour;

        [[nodiscard]] IL2CPP::Module::Unity::GameObject TryToSpawn();
        void Return(IL2CPP::Module::Unity::GameObject obj);
        void Shuffle();
        [[nodiscard]] void* GetPoolArray();
    };

    class VRCPortalMarker : public IL2CPP::Module::Unity::MonoBehaviour {
    public:
        using MonoBehaviour::MonoBehaviour;

        [[nodiscard]] std::string GetRoomId();
        [[nodiscard]] std::string GetRoomName();
        [[nodiscard]] int GetPlayerCount();
        [[nodiscard]] int GetCapacity();
        [[nodiscard]] bool IsValid();
        void RefreshPortal();
    };

    class VRCUrl : public IL2CPP::Module::ManagedObject {
    public:
        using ManagedObject::ManagedObject;

        [[nodiscard]] static VRCUrl Create(std::string_view url);
        [[nodiscard]] std::string Get();
    };

} // namespace IL2CPP::VRChat
