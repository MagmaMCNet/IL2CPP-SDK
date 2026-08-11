#pragma once
#include <cstdint>

/// VRChat runtime type descriptors.
/// `void*` fields are IL2CPP class/singleton pointers.
/// `int` fields are byte offsets into IL2CPP instances.
namespace Bootstrap {

    enum class PlayerEvent : uint8_t {
        Awake = 0,
        Join = 1,
        JoinComplete = 2,
        Leave = 3,
        Unknown = 255
    };

    struct PlayerNameplateData {
        void* Class;
        int gameObject_contents;
        int gameObject_subText;
        int gameObject_textContainer;
        int gameObject_mainContainer;
        int gameObject_icon;
        int gameObject_quickStats;
        int gameObject_platform;
        int gameObject_interactionStatus;
        int gameObject_pronouns;
        int gameObject_playerStatusIcons;
        int gameObject_userMuted;
        int gameObject_userVolume;
        int gameObject_listenBlocked;
        int gameObject_earmuffsIcon;
        int gameObject_focusViewIcon;
        int gameObject_devBanner;
        int gameObject_devIcon;
        int gameObject_groupInfo;
        int gameObject_avatarProgress;
        int gameObject_friendIcon;

        // Rewritten nameplate contents. The child GameObjects moved behind a UI
        // fragment, so on those builds the gameObject_* offsets above stay 0 and
        // these are filled instead -- and the other way round on older builds.
        // Appended, never reordered: this struct is shared ABI.
        int fragment;
        int content;
        int icons;
        int gameObject_root;
        int positioner;
        int rectTransform;
        int vrcPlayer;
    };

    struct PlayerData {
        void* Class;
        void* Singleton;
        int VRCPlayerApi;
        int VRCPlayer;
        int APIUser;
        int USpeaker;

        // Builds that expose LocalPlayer as a static property instead of a field
        // leave Singleton null and fill these in: native code pointer + the
        // MethodInfo* the thunk takes as its only argument.
        void* get_LocalPlayer;
        void* get_LocalPlayerMethod;
    };

    struct VRCPlayerData {
        void* Class;
        void* Singleton;
        int VRCPlayerApi;
        int Player;
        int PlayerNameplate;
        int PoseRecorder;
        int Serializer;
        int SyncPhysics;
        int ApiAvatar;
        int ApiAvatarFallback;

        void* Color_Administrator;
        void* Color_Friend;
        void* Color_Visitor;
        void* Color_NewUser;
        void* Color_User;
        void* Color_KnownUser;
        void* Color_Trusted;
        void* Color_Nuisance;

        int gameObject_nameplate;
        int gameObject_avatar;

        int Animator;   // appended, never reordered: shared ABI

        // String property getters as il2cppMethodInfo* -- feed straight to
        // MethodHandler::invoke, no per-call name lookup (the names are
        // obfuscated anyway). Null when the property did not resolve.
        void* get_username;
        void* get_displayName;
        void* get_userId;
        void* get_pronouns;
    };

    struct LoadBalancingClientData {
        void* Class;
        void* OnEvent;
        void* OpRaiseEvent;
        int   photonPeerOffset;             // LoadBalancingClient.field_PhotonPeer_0

        // Singleton holder: a class with a single static Photon.Realtime.LoadBalancingClient field.
        void* SingletonHolderClass;
        int   singletonHolderStaticOffset;  // offset of the static field within static-data

        // PhotonPeer inherits PeerBase.roundTripTime (Single, ms).
        void* PhotonPeerClass;
        int   roundTripTimeOffset;
    };

    struct FlatBufferNetworkSerializerData {
        void* Class;
        int RequireFastRate;
    };

    struct PhotonViewData {
        void* Class;
        int ViewId;
    };

    struct VRCPlayerStepHeightData {
        void* Class;
        int maxStepHeight;
        int stepUpThreshold;
        int offsetDistance;
        int characterController;
        int groundedLayers;
    };

    struct VRCMotionStateData {
        void* Class;
        int characterController;
    };

    struct ONSPAudioData {
        void* Class;
        int audioSource;
        int onspLowPassFilter;
        int onspAudioSource;
    };

    struct RoomManagerData {
        void* Class;
        int apiWorld;
        int apiWorldInstance;
    };

    struct VRCRectMask2DData {
        void* Class;
        int mask;
        int clippingEnabled;
    };

    struct VRCDroneData {
        void* Class;
        int vrcPickup;
        int trailRenderer;
        int worldCollider;
        int pickupCollider;
        int PlayerOwner;
    };

} // namespace Bootstrap
