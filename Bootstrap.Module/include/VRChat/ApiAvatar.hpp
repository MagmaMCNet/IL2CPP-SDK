#pragma once

#include "ApiContentModel.hpp"

namespace IL2CPP::VRChat {

    /// VRC.Core.ApiAvatar. Name, author, images, tags and version are declared by
    /// ApiContentModel`1 and inherited; only avatar-specific members belong here.
    class ApiAvatar : public ApiContentModel {
    public:
        using ApiContentModel::ApiContentModel;
    };

} // namespace IL2CPP::VRChat
