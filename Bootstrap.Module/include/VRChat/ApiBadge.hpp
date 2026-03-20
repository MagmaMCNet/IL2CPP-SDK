#pragma once

#include "ApiModel.hpp"
#include <string>

namespace IL2CPP::VRChat {

    class ApiBadge : public ApiModel {
    public:
        using ApiModel::ApiModel;

        [[nodiscard]] std::string GetBadgeId();
        [[nodiscard]] bool GetShowcased();
        [[nodiscard]] std::string GetBadgeName();
        [[nodiscard]] std::string GetBadgeDescription();
        [[nodiscard]] std::string GetBadgeImageUrl();
    };

} // namespace IL2CPP::VRChat
