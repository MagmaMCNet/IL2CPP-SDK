#include <VRChat/PlayerNameplate.hpp>
#include <VRChat/HostBridge.hpp>

namespace IL2CPP::VRChat {

    namespace {
        std::optional<unix_nameplate_offsets> nameplate_table() {
            return Bridge::Offsets<unix_nameplate_offsets>(unix_offsets_nameplate);
        }
    }

#define UNIX_NAMEPLATE_CHILD(getter, member)                                    \
    IL2CPP::Module::Unity::GameObject PlayerNameplate::getter() {               \
        if (!valid()) return {};                                                \
        const auto o = nameplate_table();                                       \
        if (!o) return {};                                                      \
        return IL2CPP::Module::Unity::GameObject(                               \
            Bridge::MemberAt(m_native, o->member));                             \
    }

    UNIX_NAMEPLATE_CHILD(GetContents,           gameobject_contents)
    UNIX_NAMEPLATE_CHILD(GetMainContainer,      gameobject_main_container)
    UNIX_NAMEPLATE_CHILD(GetTextContainer,      gameobject_text_container)
    UNIX_NAMEPLATE_CHILD(GetSubText,            gameobject_sub_text)
    UNIX_NAMEPLATE_CHILD(GetPronouns,           gameobject_pronouns)
    UNIX_NAMEPLATE_CHILD(GetIcon,               gameobject_icon)
    UNIX_NAMEPLATE_CHILD(GetPlatform,           gameobject_platform)
    UNIX_NAMEPLATE_CHILD(GetFriendIcon,         gameobject_friend_icon)
    UNIX_NAMEPLATE_CHILD(GetDevBanner,          gameobject_dev_banner)
    UNIX_NAMEPLATE_CHILD(GetDevIcon,            gameobject_dev_icon)
    UNIX_NAMEPLATE_CHILD(GetQuickStats,         gameobject_quick_stats)
    UNIX_NAMEPLATE_CHILD(GetInteractionStatus,  gameobject_interaction_status)
    UNIX_NAMEPLATE_CHILD(GetPlayerStatusIcons,  gameobject_player_status_icons)
    UNIX_NAMEPLATE_CHILD(GetUserMuted,          gameobject_user_muted)
    UNIX_NAMEPLATE_CHILD(GetUserVolume,         gameobject_user_volume)
    UNIX_NAMEPLATE_CHILD(GetListenBlocked,      gameobject_listen_blocked)
    UNIX_NAMEPLATE_CHILD(GetEarmuffsIcon,       gameobject_earmuffs_icon)
    UNIX_NAMEPLATE_CHILD(GetFocusViewIcon,      gameobject_focus_view_icon)
    UNIX_NAMEPLATE_CHILD(GetGroupInfo,          gameobject_group_info)
    UNIX_NAMEPLATE_CHILD(GetAvatarProgress,     gameobject_avatar_progress)

#undef UNIX_NAMEPLATE_CHILD

    bool PlayerNameplate::HasChildObjects() {
        const auto o = nameplate_table();
        return o && o->gameobject_contents > 0;
    }

} // namespace IL2CPP::VRChat
