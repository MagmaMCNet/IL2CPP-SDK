#pragma once

// ============================================================================
//  APIUser - VRChat API user model
// ============================================================================

#include "ApiModel.hpp"
#include <Bootstrap.Common/include/bootstrap_shared.hpp>
#include <string>
#include <vector>

namespace IL2CPP::VRChat {

    class ApiBadge;
    using PlayerRank = Bootstrap::PlayerRank;

    class APIUser : public ApiModel {
    public:
        using ApiModel::ApiModel;

        // Identity & Profile
        [[nodiscard]] std::string GetDisplayName();
        [[nodiscard]] std::string GetUsername();
        [[nodiscard]] std::string GetPronouns();
        [[nodiscard]] std::string GetBio();
        [[nodiscard]] std::vector<std::string> GetBioLinks();
        [[nodiscard]] std::string GetStatus();
        [[nodiscard]] std::string GetStatusDescription();
        [[nodiscard]] std::vector<std::string> GetTags();
        [[nodiscard]] std::string GetNote();
        [[nodiscard]] std::string GetUserLanguageCode();

        // Avatar Information
        [[nodiscard]] std::string GetAvatarId();
        [[nodiscard]] std::string GetFallbackId();
        [[nodiscard]] std::string GetCurrentAvatarImageUrl();
        [[nodiscard]] std::string GetCurrentAvatarThumbnailImageUrl();
        [[nodiscard]] std::vector<std::string> GetCurrentAvatarTags();
        [[nodiscard]] bool GetAllowAvatarCopying();

        // Profile Images
        [[nodiscard]] std::string GetUserIcon();
        [[nodiscard]] std::string GetProfilePicOverride();
        [[nodiscard]] std::string GetIconUrl();
        [[nodiscard]] std::string GetThumbnailUrl();

        // Social & Relationships
        [[nodiscard]] bool GetIsFriend();
        [[nodiscard]] std::string GetLocation();
        [[nodiscard]] std::vector<ApiBadge> GetBadges();

        // Verification & Platform
        [[nodiscard]] bool GetAgeVerified();
        [[nodiscard]] bool GetIsAdult();
        [[nodiscard]] bool GetIsOnMobile();
        [[nodiscard]] std::string GetLast_platform();
        [[nodiscard]] std::string GetPlatform();
        [[nodiscard]] PlayerRank GetPlayerRank();
    };

} // namespace IL2CPP::VRChat
