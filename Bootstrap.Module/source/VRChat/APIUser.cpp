#include <include/VRChat/APIUser.hpp>
#include <include/VRChat/ApiBadge.hpp>
#include <IL2CPP.Module/include/System/String.hpp>
#include <IL2CPP.Module/include/System/List.hpp>

namespace IL2CPP::VRChat {

    namespace {
        std::vector<std::string> collect_string_list(IL2CPP::Module::ManagedObject const& obj, std::string_view methodName) {
            std::vector<std::string> result;
            if (!obj.valid()) return result;
            auto* listPtr = obj.call_method<void*>(methodName);
            if (!listPtr) return result;
            IL2CPP::Module::System::List<void*> list(listPtr);
            int cnt = list.count();
            for (int i = 0; i < cnt; ++i) {
                auto* elemPtr = list.try_at(static_cast<uintptr_t>(i));
                if (elemPtr && *elemPtr) {
                    result.push_back(IL2CPP::Module::System::String(*elemPtr).to_string());
                }
            }
            return result;
        }
    }

    std::string APIUser::GetDisplayName() {
        return call_string_method("get_displayName");
    }

    std::string APIUser::GetUsername() {
        return call_string_method("get_username");
    }

    std::string APIUser::GetPronouns() {
        return call_string_method("get_pronouns");
    }

    std::string APIUser::GetBio() {
        return call_string_method("get_bio");
    }

    std::vector<std::string> APIUser::GetBioLinks() {
        return collect_string_list(*this, "get_bioLinks");
    }

    std::string APIUser::GetStatus() {
        return call_string_method("get_status");
    }

    std::string APIUser::GetStatusDescription() {
        return call_string_method("get_statusDescription");
    }

    std::vector<std::string> APIUser::GetTags() {
        return collect_string_list(*this, "get_tags");
    }

    std::string APIUser::GetNote() {
        return call_string_method("get_note");
    }

    std::string APIUser::GetUserLanguageCode() {
        return call_string_method("get_userLanguageCode");
    }

    std::string APIUser::GetAvatarId() {
        return call_string_method("get_avatarId");
    }

    std::string APIUser::GetFallbackId() {
        return call_string_method("get_fallbackId");
    }

    std::string APIUser::GetCurrentAvatarImageUrl() {
        return call_string_method("get_currentAvatarImageUrl");
    }

    std::string APIUser::GetCurrentAvatarThumbnailImageUrl() {
        return call_string_method("get_currentAvatarThumbnailImageUrl");
    }

    std::vector<std::string> APIUser::GetCurrentAvatarTags() {
        return collect_string_list(*this, "get_currentAvatarTags");
    }

    bool APIUser::GetAllowAvatarCopying() {
        if (!valid()) return false;
        return call_method<bool>("get_allowAvatarCopying");
    }

    std::string APIUser::GetUserIcon() {
        return call_string_method("get_userIcon");
    }

    std::string APIUser::GetProfilePicOverride() {
        return call_string_method("get_profilePicOverride");
    }

    std::string APIUser::GetIconUrl() {
        return call_string_method("get_iconUrl");
    }

    std::string APIUser::GetThumbnailUrl() {
        return call_string_method("get_thumbnailUrl");
    }

    bool APIUser::GetIsFriend() {
        if (!valid()) return false;
        return call_method<bool>("get_isFriend");
    }

    std::string APIUser::GetLocation() {
        return call_string_method("get_location");
    }

    std::vector<ApiBadge> APIUser::GetBadges() {
        std::vector<ApiBadge> result;
        if (!valid()) return result;
        auto* listPtr = call_method<void*>("get_badges");
        if (!listPtr) return result;
        IL2CPP::Module::System::List<void*> list(listPtr);
        int cnt = list.count();
        for (int i = 0; i < cnt; ++i) {
            auto* elemPtr = list.try_at(static_cast<uintptr_t>(i));
            if (elemPtr && *elemPtr) {
                result.push_back(ApiBadge(*elemPtr));
            }
        }
        return result;
    }

    bool APIUser::GetAgeVerified() {
        if (!valid()) return false;
        return call_method<bool>("get_ageVerified");
    }

    bool APIUser::GetIsAdult() {
        if (!valid()) return false;
        return call_method<bool>("get_isAdult");
    }

    bool APIUser::GetIsOnMobile() {
        if (!valid()) return false;
        return call_method<bool>("get_IsOnMobile");
    }

    std::string APIUser::GetLast_platform() {
        return call_string_method("get_last_platform");
    }

    std::string APIUser::GetPlatform() {
        return call_string_method("get_platform");
    }

    PlayerRank APIUser::GetPlayerRank() {
        static constexpr std::pair<const char*, int> ranks[] = {
            {"system_trust_troll", 6},
            {"system_trust_veteran", 4},
            {"system_trust_trusted", 3},
            {"system_trust_known", 2},
            {"system_trust_basic", 1}
        };
        auto tags = GetTags();

        for (auto [tag, rank] : ranks) {
            if (std::ranges::find(tags, tag) != tags.end()) {
                return static_cast<PlayerRank>(rank);
            }
        }

        return PlayerRank::Visitor;
    }
} // namespace IL2CPP::VRChat
