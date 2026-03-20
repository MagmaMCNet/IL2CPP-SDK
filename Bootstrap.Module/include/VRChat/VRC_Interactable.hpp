#pragma once

#include <IL2CPP.Module/include/il2cpp_module.hpp>
#include <string>
#include <string_view>

namespace IL2CPP::VRChat {

    class VRC_Interactable : public IL2CPP::Module::Unity::MonoBehaviour {
    public:
        using MonoBehaviour::MonoBehaviour;

        [[nodiscard]] std::string GetInteractText();
        void SetInteractText(std::string_view text);
        [[nodiscard]] float GetProximity();
        void SetProximity(float proximity);
    };

} // namespace IL2CPP::VRChat
