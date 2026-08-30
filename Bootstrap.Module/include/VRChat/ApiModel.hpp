#pragma once

#include <IL2CPP.Module/include/il2cpp_module.hpp>
#include <string>

namespace IL2CPP::VRChat {

    class ApiModel : public IL2CPP::Module::ManagedObject {
    public:
        using ManagedObject::ManagedObject;

        [[nodiscard]] std::string GetId();

        /// <summary>True once the record holds real data. VRChat caches a model
        /// before filling it in, so an unpopulated object carries only an id.</summary>
        [[nodiscard]] bool GetPopulated();
    };

} // namespace IL2CPP::VRChat
