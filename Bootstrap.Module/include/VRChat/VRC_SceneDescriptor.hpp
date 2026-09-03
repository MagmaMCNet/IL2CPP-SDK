#pragma once

#include "Enums.hpp"
#include <IL2CPP.Module/include/il2cpp_module.hpp>
#include <IL2CPP.Module/include/Unity/GameObject.hpp>

namespace IL2CPP::VRChat {

    class VRC_SceneDescriptor : public IL2CPP::Module::Unity::MonoBehaviour {
    public:
        using MonoBehaviour::MonoBehaviour;

        [[nodiscard]] static VRC_SceneDescriptor Instance();

        [[nodiscard]] float GetRespawnHeight();
        [[nodiscard]] void* GetSpawnsArray();
        [[nodiscard]] SpawnOrder GetSpawnOrder();
        [[nodiscard]] SpawnOrientation GetSpawnOrientation();
        [[nodiscard]] IL2CPP::Module::Unity::GameObject GetReferenceCamera();
    };

} // namespace IL2CPP::VRChat
