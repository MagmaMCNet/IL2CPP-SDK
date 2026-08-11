#pragma once

#include <IL2CPP.Module/include/il2cpp_module.hpp>

namespace IL2CPP::VRChat {

    class VRCPlayer;

    class PlayerNameplate : public IL2CPP::Module::Unity::MonoBehaviour {
    public:
        using MonoBehaviour::MonoBehaviour;

        /// <summary>True on builds whose nameplate still exposes the child
        /// GameObjects directly. When false the Get*() child accessors below all
        /// return an invalid object and the fragment/content members apply instead.</summary>
        [[nodiscard]] bool HasChildObjects();

        [[nodiscard]] IL2CPP::Module::Unity::GameObject GetContents();
        [[nodiscard]] IL2CPP::Module::Unity::GameObject GetMainContainer();
        [[nodiscard]] IL2CPP::Module::Unity::GameObject GetTextContainer();

        [[nodiscard]] IL2CPP::Module::Unity::GameObject GetSubText();
        [[nodiscard]] IL2CPP::Module::Unity::GameObject GetPronouns();

        [[nodiscard]] IL2CPP::Module::Unity::GameObject GetIcon();
        [[nodiscard]] IL2CPP::Module::Unity::GameObject GetPlatform();
        [[nodiscard]] IL2CPP::Module::Unity::GameObject GetFriendIcon();
        [[nodiscard]] IL2CPP::Module::Unity::GameObject GetDevBanner();
        [[nodiscard]] IL2CPP::Module::Unity::GameObject GetDevIcon();

        [[nodiscard]] IL2CPP::Module::Unity::GameObject GetQuickStats();
        [[nodiscard]] IL2CPP::Module::Unity::GameObject GetInteractionStatus();
        [[nodiscard]] IL2CPP::Module::Unity::GameObject GetPlayerStatusIcons();
        [[nodiscard]] IL2CPP::Module::Unity::GameObject GetUserMuted();
        [[nodiscard]] IL2CPP::Module::Unity::GameObject GetUserVolume();
        [[nodiscard]] IL2CPP::Module::Unity::GameObject GetListenBlocked();
        [[nodiscard]] IL2CPP::Module::Unity::GameObject GetEarmuffsIcon();
        [[nodiscard]] IL2CPP::Module::Unity::GameObject GetFocusViewIcon();

        [[nodiscard]] IL2CPP::Module::Unity::GameObject GetGroupInfo();
        [[nodiscard]] IL2CPP::Module::Unity::GameObject GetAvatarProgress();

        // Rewritten-nameplate members. Invalid on builds where HasChildObjects()
        // is true, and vice versa.
        [[nodiscard]] IL2CPP::Module::Unity::GameObject GetRootObject();
        [[nodiscard]] IL2CPP::Module::ManagedObject GetFragment();
        [[nodiscard]] IL2CPP::Module::ManagedObject GetContent();
        [[nodiscard]] IL2CPP::Module::ManagedObject GetIcons();
        [[nodiscard]] IL2CPP::Module::ManagedObject GetPositioner();
        [[nodiscard]] IL2CPP::Module::Unity::RectTransform GetChatBubbleRect();
        [[nodiscard]] VRCPlayer GetVRCPlayer();
    };

} // namespace IL2CPP::VRChat
