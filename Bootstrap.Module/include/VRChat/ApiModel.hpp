#pragma once

// ============================================================================
//  ApiModel - Base class for VRChat API model objects
// ============================================================================

#include <IL2CPP.Module/include/il2cpp_module.hpp>
#include <string>

namespace IL2CPP::VRChat {

    class ApiModel : public IL2CPP::Module::ManagedObject {
    public:
        using ManagedObject::ManagedObject;

        [[nodiscard]] std::string GetId();
    };

} // namespace IL2CPP::VRChat
