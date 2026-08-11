#include <VRChat/PlayerNameplate.hpp>
#include <VRChat/VRCPlayer.hpp>
#include <bootstrap_internal.hpp>

namespace IL2CPP::VRChat {

    namespace {
        // offset 0 means the member is absent from this build's nameplate.
        void* member_at(void* self, int offset) {
            if (!self || offset <= 0) return nullptr;
            return *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(self) + offset);
        }

        const Bootstrap::PlayerNameplateData* nameplate_data() {
            if (!Bootstrap::Module::is_connected()) return nullptr;
            return Bootstrap::Module::get_vtable()->get_nameplate_data();
        }
    }

#define UNIX_NAMEPLATE_MEMBER(type, getter, member)     \
    type PlayerNameplate::getter() {                    \
        if (!valid()) return {};                        \
        const auto* data = nameplate_data();            \
        if (!data) return {};                           \
        return type(member_at(m_native, data->member)); \
    }

#define UNIX_NAMEPLATE_CHILD(getter, member) \
    UNIX_NAMEPLATE_MEMBER(IL2CPP::Module::Unity::GameObject, getter, member)

    UNIX_NAMEPLATE_CHILD(GetContents,           gameObject_contents)
    UNIX_NAMEPLATE_CHILD(GetMainContainer,      gameObject_mainContainer)
    UNIX_NAMEPLATE_CHILD(GetTextContainer,      gameObject_textContainer)
    UNIX_NAMEPLATE_CHILD(GetSubText,            gameObject_subText)
    UNIX_NAMEPLATE_CHILD(GetPronouns,           gameObject_pronouns)
    UNIX_NAMEPLATE_CHILD(GetIcon,               gameObject_icon)
    UNIX_NAMEPLATE_CHILD(GetPlatform,           gameObject_platform)
    UNIX_NAMEPLATE_CHILD(GetFriendIcon,         gameObject_friendIcon)
    UNIX_NAMEPLATE_CHILD(GetDevBanner,          gameObject_devBanner)
    UNIX_NAMEPLATE_CHILD(GetDevIcon,            gameObject_devIcon)
    UNIX_NAMEPLATE_CHILD(GetQuickStats,         gameObject_quickStats)
    UNIX_NAMEPLATE_CHILD(GetInteractionStatus,  gameObject_interactionStatus)
    UNIX_NAMEPLATE_CHILD(GetPlayerStatusIcons,  gameObject_playerStatusIcons)
    UNIX_NAMEPLATE_CHILD(GetUserMuted,          gameObject_userMuted)
    UNIX_NAMEPLATE_CHILD(GetUserVolume,         gameObject_userVolume)
    UNIX_NAMEPLATE_CHILD(GetListenBlocked,      gameObject_listenBlocked)
    UNIX_NAMEPLATE_CHILD(GetEarmuffsIcon,       gameObject_earmuffsIcon)
    UNIX_NAMEPLATE_CHILD(GetFocusViewIcon,      gameObject_focusViewIcon)
    UNIX_NAMEPLATE_CHILD(GetGroupInfo,          gameObject_groupInfo)
    UNIX_NAMEPLATE_CHILD(GetAvatarProgress,     gameObject_avatarProgress)
    UNIX_NAMEPLATE_CHILD(GetRootObject,         gameObject_root)

    UNIX_NAMEPLATE_MEMBER(IL2CPP::Module::ManagedObject,       GetFragment,       fragment)
    UNIX_NAMEPLATE_MEMBER(IL2CPP::Module::ManagedObject,       GetContent,        content)
    UNIX_NAMEPLATE_MEMBER(IL2CPP::Module::ManagedObject,       GetIcons,          icons)
    UNIX_NAMEPLATE_MEMBER(IL2CPP::Module::ManagedObject,       GetPositioner,     positioner)
    UNIX_NAMEPLATE_MEMBER(IL2CPP::Module::Unity::RectTransform, GetChatBubbleRect, rectTransform)
    UNIX_NAMEPLATE_MEMBER(VRCPlayer,                            GetVRCPlayer,      vrcPlayer)

#undef UNIX_NAMEPLATE_CHILD
#undef UNIX_NAMEPLATE_MEMBER

    bool PlayerNameplate::HasChildObjects() {
        const auto* data = nameplate_data();
        return data && data->gameObject_contents > 0;
    }

} // namespace IL2CPP::VRChat
