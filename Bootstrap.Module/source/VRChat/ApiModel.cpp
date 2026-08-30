#include <VRChat/ApiModel.hpp>
#include <IL2CPP.Module/include/MethodHandler.hpp>
#include <IL2CPP.Module/include/System/String.hpp>

namespace IL2CPP::VRChat {

    using IL2CPP::Module::MethodHandler;

    std::string ApiModel::GetId() {
        if (!valid()) return "";
        static auto m = MethodHandler::resolve("VRC.Core.ApiModel", "get_id", 0);
        void* str = MethodHandler::invoke<void*>(m, raw());
        return str ? IL2CPP::Module::System::String(str).to_string() : "";
    }

    bool ApiModel::GetPopulated() {
        if (!valid()) return false;
        static auto m = MethodHandler::resolve(IL2CPP_STR("VRC.Core.ApiModel"),
                                               IL2CPP_STR("get_Populated"), 0);
        return MethodHandler::invoke<bool>(m, raw());
    }

} // namespace IL2CPP::VRChat
