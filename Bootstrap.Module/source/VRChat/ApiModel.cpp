#include <include/VRChat/ApiModel.hpp>

namespace IL2CPP::VRChat {

    std::string ApiModel::GetId() {
        return call_string_method("get_id");
    }

} // namespace IL2CPP::VRChat
