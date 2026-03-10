#pragma once

// ============================================================================
//  bootstrap_shared.hpp - Shared types for Bootstrap vtable (Bootstrap DLL
//  implements, Bootstrap.Module consumes via shared memory)
// ============================================================================

#include <cstdint>
#include "vrc_types.hpp"
#include "sdk_version.hpp"

namespace Bootstrap {

    constexpr uint32_t invalid_id = ~0u;
    constexpr uint32_t vtable_version = 10;
    
    // Shared memory prefix + suffix - append PID between them for multi-instance support
    constexpr wchar_t const* shared_memory_prefix = L"Local\\UNIx_PID_";
    constexpr wchar_t const* shared_memory_suffix = L"_Core";



    // Unity LogType: 0=Error, 1=Assert, 2=Warning, 3=Log, 4=Exception
    enum class UnityLogType : int { Error = 0, Assert, Warning, Log, Exception };

    struct UnityConsoleOptions {
        bool enable_colors;
        bool enable_file_logging;
        bool enable_trace;       // show stack trace for error/warn/assert/exception
        bool enable_info_trace;  // also show stack trace for info (default off)
        bool deobfuscate_names;
        bool enable_quickmenu_logging;
        wchar_t log_file_path[260];  // MAX_PATH
    };

    // C-style callback: msg, msg_len, stack, stack_len, log_type
    using fn_log_callback = void(__cdecl*)(char const* msg, uint32_t msg_len,
        char const* stack, uint32_t stack_len, UnityLogType log_type);

    using fn_register_module = uint32_t(__cdecl*)(char const* name, uint32_t name_len, uint32_t sdk_ver);
    using fn_unregister_module = void(__cdecl*)(uint32_t module_id);

    // Rendering
    using fn_render_callback = void(__cdecl*)();
    using fn_register_render_callback = uint32_t(__cdecl*)(uint32_t module_id, fn_render_callback callback);
    using fn_unregister_render_callback = void(__cdecl*)(uint32_t module_id, uint32_t callback_id);
    using fn_get_imgui_context = void*(__cdecl*)();

    // Unity Console
    using fn_register_log_callback = uint32_t(__cdecl*)(uint32_t module_id, fn_log_callback callback);
    using fn_unregister_log_callback = void(__cdecl*)(uint32_t module_id, uint32_t callback_id);
    using fn_get_console_options = void(__cdecl*)(UnityConsoleOptions* out);
    using fn_set_console_options = void(__cdecl*)(UnityConsoleOptions const* opts);

    // Unity Explorer (void* = IL2CPP object pointers)
    using fn_show_gameobject_in_explorer = void(__cdecl*)(void* gameObject);
    using fn_show_component_in_explorer = void(__cdecl*)(void* component);
    using fn_explorer_navigate_callback = void(__cdecl*)(void* gameObject, void* component);
    using fn_register_explorer_callback = uint32_t(__cdecl*)(uint32_t module_id, fn_explorer_navigate_callback cb);
    using fn_unregister_explorer_callback = void(__cdecl*)(uint32_t module_id, uint32_t callback_id);

    // VRChat Data
    using fn_get_vrc_player_data = VRCPlayerData const* (__cdecl*)();
    using fn_get_player_data = PlayerData const* (__cdecl*)();
    using fn_get_nameplate_data = PlayerNameplateData const* (__cdecl*)();
    using fn_get_local_player = void* (__cdecl*)();
    using fn_get_local_player_api = void* (__cdecl*)();
    using fn_get_local_vrc_player = void* (__cdecl*)();

    // VRChat Events
    using fn_player_simple_callback = void(__cdecl*)(void* player);
    using fn_register_player_event = uint32_t(__cdecl*)(uint32_t module_id, PlayerEvent event, fn_player_simple_callback cb);
    using fn_unregister_player_event = void(__cdecl*)(uint32_t module_id, uint32_t callback_id);
    using fn_invoke_player_event = void(__cdecl*)(void* player, PlayerEvent event);

    // Config — per-module persistent key-value store
    using fn_config_set_int    = void(__cdecl*)(uint32_t module_id, char const* key, uint32_t key_len, int32_t value);
    using fn_config_get_int    = int32_t(__cdecl*)(uint32_t module_id, char const* key, uint32_t key_len, int32_t default_val);
    using fn_config_set_float  = void(__cdecl*)(uint32_t module_id, char const* key, uint32_t key_len, float value);
    using fn_config_get_float  = float(__cdecl*)(uint32_t module_id, char const* key, uint32_t key_len, float default_val);
    using fn_config_set_string = void(__cdecl*)(uint32_t module_id, char const* key, uint32_t key_len, char const* val, uint32_t val_len);
    using fn_config_get_string = uint32_t(__cdecl*)(uint32_t module_id, char const* key, uint32_t key_len, char* out_buf, uint32_t buf_size);
    using fn_config_set_bool   = void(__cdecl*)(uint32_t module_id, char const* key, uint32_t key_len, bool value);
    using fn_config_get_bool   = bool(__cdecl*)(uint32_t module_id, char const* key, uint32_t key_len, bool default_val);
    using fn_config_save       = void(__cdecl*)(uint32_t module_id);
    using fn_config_has_key    = bool(__cdecl*)(uint32_t module_id, char const* key, uint32_t key_len);
    using fn_config_remove_key = void(__cdecl*)(uint32_t module_id, char const* key, uint32_t key_len);

    // Message bus — broadcast pub/sub between mods
    using fn_message_callback    = void(__cdecl*)(uint32_t sender_module_id,
        char const* topic, uint32_t topic_len,
        uint8_t const* data, uint32_t data_len);
    using fn_subscribe_message   = uint32_t(__cdecl*)(uint32_t module_id, char const* topic, uint32_t topic_len, fn_message_callback cb);
    using fn_unsubscribe_message = void(__cdecl*)(uint32_t module_id, uint32_t subscription_id);
    using fn_publish_message     = void(__cdecl*)(uint32_t module_id, char const* topic, uint32_t topic_len, uint8_t const* data, uint32_t data_len);

    // QuickMenu API
    using fn_menu_button_callback = void(__cdecl*)(uint32_t button_id);
    using fn_menu_toggle_callback = void(__cdecl*)(uint32_t button_id, bool is_on);
    using fn_menu_slider_callback = void(__cdecl*)(uint32_t slider_id, float value);
    using fn_menu_enum_callback   = void(__cdecl*)(uint32_t selector_id, int32_t index);
    using fn_qm_create_page       = uint32_t(__cdecl*)(uint32_t module_id,
        char const* name, uint32_t name_len, char const* tooltip, uint32_t tooltip_len);
    using fn_qm_create_sub_page   = uint32_t(__cdecl*)(uint32_t module_id,
        uint32_t parent_page_id, char const* name, uint32_t name_len);
    using fn_qm_remove_page       = void(__cdecl*)(uint32_t module_id, uint32_t page_id);
    using fn_qm_add_button        = uint32_t(__cdecl*)(uint32_t module_id, uint32_t page_id,
        char const* text, uint32_t text_len, fn_menu_button_callback callback);
    using fn_qm_remove_button     = void(__cdecl*)(uint32_t module_id, uint32_t button_id);
    using fn_qm_set_button_text   = void(__cdecl*)(uint32_t module_id, uint32_t button_id,
        char const* text, uint32_t text_len);
    using fn_qm_navigate_to       = void(__cdecl*)(uint32_t page_id);
    using fn_qm_navigate_back     = void(__cdecl*)();
    using fn_qm_is_ready          = bool(__cdecl*)();

    // QuickMenu — toggles, icons, colors, badges (v6)
    using fn_qm_add_toggle        = uint32_t(__cdecl*)(uint32_t module_id, uint32_t page_id,
        char const* text, uint32_t text_len, bool default_state, fn_menu_toggle_callback callback,
        char const* config_key, uint32_t config_key_len);
    using fn_qm_set_toggle_state  = void(__cdecl*)(uint32_t module_id, uint32_t button_id, bool state);
    using fn_qm_get_toggle_state  = bool(__cdecl*)(uint32_t module_id, uint32_t button_id);
    using fn_qm_set_button_icon_ptr = void(__cdecl*)(uint32_t module_id, uint32_t button_id, void* sprite_ptr);
    using fn_qm_set_button_icon_vrc = void(__cdecl*)(uint32_t module_id, uint32_t button_id, int32_t sprite_id);
    using fn_qm_set_button_color  = void(__cdecl*)(uint32_t module_id, uint32_t button_id,
        float r, float g, float b, float a);
    using fn_qm_set_page_title    = void(__cdecl*)(uint32_t module_id, uint32_t page_id,
        char const* title, uint32_t title_len);
    using fn_qm_set_page_icon_ptr = void(__cdecl*)(uint32_t module_id, uint32_t page_id, void* sprite_ptr);
    using fn_qm_set_page_icon_vrc = void(__cdecl*)(uint32_t module_id, uint32_t page_id, int32_t sprite_id);
    using fn_qm_set_page_badge    = void(__cdecl*)(uint32_t module_id, uint32_t page_id, bool visible,
        char const* text, uint32_t text_len, float const* bg_rgba);

    // QuickMenu v7 — enable/disable, visibility, sub-page nav, sprite utility
    using fn_qm_set_button_enabled    = void(__cdecl*)(uint32_t module_id, uint32_t button_id, bool enabled);
    using fn_qm_set_button_visible    = void(__cdecl*)(uint32_t module_id, uint32_t button_id, bool visible);
    using fn_qm_get_subpage_nav_button = uint32_t(__cdecl*)(uint32_t module_id, uint32_t sub_page_id);
    using fn_qm_set_subpage_nav_text  = void(__cdecl*)(uint32_t module_id, uint32_t sub_page_id,
        char const* text, uint32_t text_len);
    using fn_qm_set_subpage_nav_icon_vrc = void(__cdecl*)(uint32_t module_id, uint32_t sub_page_id, int32_t sprite_id);
    using fn_qm_set_image_sprite      = void(__cdecl*)(void* image_component, int32_t sprite_id);

    // QuickMenu v8 — foldouts, settings toggles, enum selectors, sliders, separators
    using fn_qm_add_foldout           = uint32_t(__cdecl*)(uint32_t module_id, uint32_t page_id,
        char const* title, uint32_t title_len, bool default_expanded, bool show_background);
    using fn_qm_set_foldout_expanded  = void(__cdecl*)(uint32_t module_id, uint32_t foldout_id, bool expanded);
    using fn_qm_get_foldout_expanded  = bool(__cdecl*)(uint32_t module_id, uint32_t foldout_id);
    using fn_qm_add_settings_toggle   = uint32_t(__cdecl*)(uint32_t module_id, uint32_t foldout_id,
        char const* text, uint32_t text_len, bool default_state, fn_menu_toggle_callback callback,
        char const* config_key, uint32_t config_key_len, bool show_sub_element_indicator);
    using fn_qm_add_enum_selector     = uint32_t(__cdecl*)(uint32_t module_id, uint32_t foldout_id,
        char const* label, uint32_t label_len, char const* const* options, uint32_t option_count,
        int32_t default_index, fn_menu_enum_callback callback,
        char const* config_key, uint32_t config_key_len, bool show_sub_element_indicator);
    using fn_qm_set_enum_index        = void(__cdecl*)(uint32_t module_id, uint32_t selector_id, int32_t index);
    using fn_qm_get_enum_index        = int32_t(__cdecl*)(uint32_t module_id, uint32_t selector_id);
    using fn_qm_add_slider            = uint32_t(__cdecl*)(uint32_t module_id, uint32_t foldout_id,
        char const* label, uint32_t label_len, float min_val, float max_val, float default_val,
        fn_menu_slider_callback callback, char const* config_key, uint32_t config_key_len,
        char const* format_str, uint32_t format_str_len, bool show_sub_element_indicator);
    using fn_qm_set_slider_value      = void(__cdecl*)(uint32_t module_id, uint32_t slider_id, float value);
    using fn_qm_get_slider_value      = float(__cdecl*)(uint32_t module_id, uint32_t slider_id);
    using fn_qm_add_separator         = uint32_t(__cdecl*)(uint32_t module_id, uint32_t foldout_id);

    // TweenService v9
    using fn_tween_anchored_position = uint32_t(__cdecl*)(uint32_t module_id,
        void* rect_transform, float from_x, float from_y, float to_x, float to_y,
        float duration_ms, int32_t ease_type);
    using fn_tween_local_position = uint32_t(__cdecl*)(uint32_t module_id,
        void* transform, float from_x, float from_y, float from_z,
        float to_x, float to_y, float to_z, float duration_ms, int32_t ease_type);
    using fn_tween_local_scale = uint32_t(__cdecl*)(uint32_t module_id,
        void* transform, float from_x, float from_y, float from_z,
        float to_x, float to_y, float to_z, float duration_ms, int32_t ease_type);
    using fn_tween_cancel = void(__cdecl*)(uint32_t tween_id);
    using fn_tween_cancel_all = void(__cdecl*)(uint32_t module_id);

    // NameplateService v10
    using fn_np_create_plate = uint32_t(__cdecl*)(uint32_t module_id, void* player,
        float pos_x, float pos_y, float pos_z,
        char const* label, uint32_t label_len,
        char const* tag, uint32_t tag_len,
        char* out_plate_id, uint32_t plate_id_buf_size);
    using fn_np_destroy_plate = void(__cdecl*)(uint32_t module_id, void* player,
        char const* plate_id, uint32_t plate_id_len);
    using fn_np_destroy_plates_by_tag = void(__cdecl*)(uint32_t module_id, void* player,
        char const* tag_prefix, uint32_t tag_prefix_len);
    using fn_np_set_plate_text = void(__cdecl*)(uint32_t module_id, void* player,
        char const* plate_id, uint32_t plate_id_len,
        char const* text, uint32_t text_len);
    using fn_np_set_plate_text_color = void(__cdecl*)(uint32_t module_id, void* player,
        char const* plate_id, uint32_t plate_id_len,
        float r, float g, float b, float a);
    using fn_np_set_plate_icon_color = void(__cdecl*)(uint32_t module_id, void* player,
        char const* plate_id, uint32_t plate_id_len,
        float r, float g, float b, float a);
    using fn_np_set_plate_position = void(__cdecl*)(uint32_t module_id, void* player,
        char const* plate_id, uint32_t plate_id_len,
        float x, float y, float z);

    // ClientUsage v10
    using fn_cu_register_client = void(__cdecl*)(uint32_t module_id,
        char const* client_name, uint32_t client_name_len,
        char const* api_key, uint32_t api_key_len);
    using fn_cu_is_client_registered = bool(__cdecl*)(
        char const* client_name, uint32_t client_name_len);

    // TweenService additions v10
    using fn_tween_completion_callback = void(__cdecl*)(uint32_t tween_id);

    using fn_tween_float = uint32_t(__cdecl*)(uint32_t module_id,
        float from, float to, float duration_ms, int32_t ease_type,
        fn_tween_completion_callback on_complete);

    using fn_tween_cancel_all_for_target = void(__cdecl*)(void* target_ptr);

    using fn_tween_anchored_position_ex = uint32_t(__cdecl*)(uint32_t module_id,
        void* rect_transform, float from_x, float from_y, float to_x, float to_y,
        float duration_ms, int32_t ease_type, fn_tween_completion_callback on_complete);
    using fn_tween_local_position_ex = uint32_t(__cdecl*)(uint32_t module_id,
        void* transform, float from_x, float from_y, float from_z,
        float to_x, float to_y, float to_z,
        float duration_ms, int32_t ease_type, fn_tween_completion_callback on_complete);
    using fn_tween_local_scale_ex = uint32_t(__cdecl*)(uint32_t module_id,
        void* transform, float from_x, float from_y, float from_z,
        float to_x, float to_y, float to_z,
        float duration_ms, int32_t ease_type, fn_tween_completion_callback on_complete);

    // PerformanceModule v10
    enum class PerfSetting : int32_t {
        MasterTextureLimit = 0,
        AntiAliasing = 1,
        ShadowResolution = 2,
        PixelLightCount = 3,
        ShaderMaxLOD = 4,
        VSyncCount = 5,
        // float settings
        StreamingMipmapsBudget = 100,
        LodBias = 101
    };

    using fn_perf_get_int = int32_t(__cdecl*)(int32_t setting_id);
    using fn_perf_set_int = void(__cdecl*)(int32_t setting_id, int32_t value);
    using fn_perf_get_float = float(__cdecl*)(int32_t setting_id);
    using fn_perf_set_float = void(__cdecl*)(int32_t setting_id, float value);
    using fn_perf_force_gc = void(__cdecl*)(int32_t generation);
    using fn_perf_full_cleanup = void(__cdecl*)();
    using fn_perf_set_camera_rendering_path = void(__cdecl*)(void* camera, int32_t path);
    using fn_perf_get_camera_rendering_path = int32_t(__cdecl*)(void* camera);

    // Sprite enum — VRC built-ins + Bundle sprites (mirrors internal VRCSprite)
    enum class Sprite : int32_t {
        Rocket, Notification, MapIcon, Sound,
        VRCPlus, VRCPlusExperiment, Store, Settings, Report,
        Planet, Avatars, Social, Groups, Home, Reload, Target, Shield, Calibrate, SitStand,
        Screenshot, Light, MultiLayer, Gallery, Folder,
        Gift, UserIcon, Prints, Camera, Emojis, Stickers,
        Drone, CameraDolly, SelfieExpression, Backgrounds,
        UIThemes, ManageSubscription,
        MicOff, TeleportTo, TeleportToMe,
        KickUser, BanUser, GainUp, GainDown, Logout,

        // Bundle sprites (loaded from embedded unixdefaults asset bundle)
        Bundle_BatteryFull, Bundle_FileCss, Bundle_ThermometerCold, Bundle_FileCloud,
        Bundle_Stack, Bundle_BatteryVerticalFull, Bundle_Vision, Bundle_Bookmarks,
        Bundle_EggCrack, Bundle_HeartHalf, Bundle_Boot, Bundle_FileSql,
        Bundle_ArrowBendLeftUp, Bundle_Alien, Bundle_EyeSlash, Bundle_FilePdf,
        Bundle_Recycle, Bundle_Virus, Bundle_FileVue, Bundle_Bread,
        Bundle_CellSignalX, Bundle_CodesandboxLogo, Bundle_BatteryVerticalEmpty, Bundle_Bell,
        Bundle_StackMinus, Bundle_WarningDiamond, Bundle_FileMagnifyingGlass, Bundle_Files,
        Bundle_ArrowArcLeft, Bundle_FlyingSaucer, Bundle_BatteryEmpty, Bundle_ArrowCircleLeft,
        Bundle_BracketsCurly, Bundle_BatteryVerticalHigh, Bundle_FilePng, Bundle_WifiNone,
        Bundle_BatteryPlus, Bundle_ArrowsInCardinal, Bundle_SealQuestion, Bundle_Books,
        Bundle_HandPeace, Bundle_ArrowLineUpRight, Bundle_FileLock, Bundle_ArrowBendUpRight,
        Bundle_BatteryWarning, Bundle_Spinner, Bundle_FalloutShelter, Bundle_FileTs,
        Bundle_Coins, Bundle_DotsThreeOutlineVertical, Bundle_Wall, Bundle_Thermometer,
        Bundle_ArrowULeftDown, Bundle_Book, Bundle_SpeakerX, Bundle_ArrowBendDownRight,
        Bundle_StackSimple, Bundle_Bandaids, Bundle_ArrowFatLineUp, Bundle_BookOpen,
        Bundle_Ear, Bundle_FileXls, Bundle_Prohibit, Bundle_FileCsv,
        Bundle_BookmarkSimple, Bundle_Selection, Bundle_Browsers, Bundle_ArrowLeft,
        Bundle_ArrowLineDown, Bundle_Balloon, Bundle_ArrowsOutLineVertical, Bundle_BracketsSquare,
        Bundle_CellSignalNone, Bundle_BatteryVerticalLow, Bundle_Video, Bundle_EarSlash,
        Bundle_FileJsx, Bundle_SpeakerSlash, Bundle_WarningCircle, Bundle_SecurityCamera,
        Bundle_CellSignalSlash, Bundle_Egg, Bundle_FileIni, Bundle_ArrowFatUp,
        Bundle_Rocket, Bundle_BookmarksSimple, Bundle_ArrowFatDown, Bundle_ArrowBendUpLeft,
        Bundle_BatteryLow, Bundle_StarHalf, Bundle_Fish, Bundle_SpeakerNone,
        Bundle_Biohazard, Bundle_File, Bundle_Seal, Bundle_FileCode,
        Bundle_BellSlash, Bundle_WifiX, Bundle_FileArrowDown, Bundle_GenderMale,
        Bundle_Bluetooth, Bundle_Coin, Bundle_FileJpg, Bundle_FileMinus,
        Bundle_XCircle, Bundle_IdentificationCards, Bundle_FileImage, Bundle_FileText,
        Bundle_HeartBreak, Bundle_SealWarning, Bundle_TriangleDashed, Bundle_Wallet,
        Bundle_ArrowLineDownLeft, Bundle_ArrowLineLeft, Bundle_StackPlus, Bundle_ArrowFatLeft,
        Bundle_BellSimple, Bundle_Diamond, Bundle_Pulse, Bundle_ArrowBendLeftDown,
        Bundle_ArrowFatRight, Bundle_BatteryPlusVertical, Bundle_ArrowLineUpLeft, Bundle_FileCpp,
        Bundle_ThermometerHot, Bundle_CellSignalMedium, Bundle_SpeakerLow, Bundle_WifiSlash,
        Bundle_ArrowArcRight, Bundle_VinylRecord, Bundle_BracketsAngle, Bundle_Feather,
        Bundle_BatteryHigh, Bundle_ArrowSquareIn, Bundle_BluetoothConnected, Bundle_Brain,
        Bundle_CheckFat, Bundle_ArrowsHorizontal, Bundle_Flashlight, Bundle_ArrowCircleDown,
        Bundle_Service, Bundle_AirplaneTilt, Bundle_ArrowFatLinesRight, Bundle_ArrowCounterClockwise,
        Bundle_Fingerprint, Bundle_Flask, Bundle_Check, Bundle_DotsThreeVertical,
        Bundle_Triangle, Bundle_CloudArrowUp, Bundle_HandFist, Bundle_Snowflake,
        Bundle_ArrowFatLineDown, Bundle_FileArchive, Bundle_FileC, Bundle_FileTxt,
        Bundle_HandsClapping, Bundle_BatteryVerticalMedium, Bundle_ArrowBendDownLeft, Bundle_FileRs,
        Bundle_FileAudio, Bundle_CellSignalHigh, Bundle_FileZip, Bundle_CodeSimple,
        Bundle_SpinnerGap, Bundle_Gear, Bundle_ArrowsDownUp, Bundle_ArrowRight,
        Bundle_ArrowFatLineLeft, Bundle_BatteryMedium, Bundle_CloudArrowDown, Bundle_Toolbox,
        Bundle_Heart, Bundle_ChartLineUp, Bundle_ArrowUDownRight, Bundle_FileHtml,
        Bundle_PuzzlePiece, Bundle_ArrowCircleUp, Bundle_ArrowBendRightUp, Bundle_FileJs,
        Bundle_Control, Bundle_Waves, Bundle_ArrowCircleRight, Bundle_SpeakerHigh,
        Bundle_TextT, Bundle_WashingMachine, Bundle_ArrowLineUp, Bundle_WifiHigh,
        Bundle_ArrowFatLinesLeft, Bundle_FileSvg, Bundle_HandHeart, Bundle_ArrowsInLineHorizontal,
        Bundle_FileArrowUp, Bundle_SealPercent, Bundle_Checks, Bundle_Drop,
        Bundle_GenderFemale, Bundle_ArrowLineRight, Bundle_FileDoc, Bundle_FileMd,
        Bundle_Cloud, Bundle_ArrowsIn, Bundle_FilePlus, Bundle_FolderX,
        Bundle_FileX, Bundle_FileVideo, Bundle_DotsThreeOutline, Bundle_HandPalm,
        Bundle_ArrowFatLinesUp, Bundle_Ghost, Bundle_ArrowLineDownRight, Bundle_Nut,
        Bundle_ArrowsClockwise, Bundle_CheckCircle, Bundle_SlidersHorizontal, Bundle_Bomb,
        Bundle_ArrowBendRightDown, Bundle_Bug, Bundle_Power, Bundle_CellSignalFull,
        Bundle_WarningSign, Bundle_BatteryChargingVertical, Bundle_Bone, Bundle_ArrowFatLineRight,
        Bundle_ArrowFatLinesDown, Bundle_FileTsx, Bundle_Shield, Bundle_WarningOctagon,
        Bundle_WifiMedium, Bundle_ChartLine, Bundle_X, Bundle_Hexagon,
        Bundle_BracketsRound, Bundle_Handshake, Bundle_HeartStraightBreak, Bundle_Sliders,
        Bundle_FilePpt, Bundle_FirstAidKit, Bundle_Airplane, Bundle_ArrowSquareDown,
        Bundle_StarFour, Bundle_ArrowsOut, Bundle_CellSignalLow, Bundle_CornersIn,
        Bundle_Detector, Bundle_FilePy, Bundle_SealCheck, Bundle_Star,
        Bundle_Translate, Bundle_ChartLineDown, Bundle_LocationMarker, Bundle_BookBookmark,
        Bundle_Sun, Bundle_DropSimple, Bundle_Bookmark, Bundle_ArrowsCounterClockwise,
        Bundle_TrafficCone, Bundle_ArrowUDownLeft, Bundle_BellSimpleSlash, Bundle_Fan,
        Bundle_Flame, Bundle_ArrowClockwise, Bundle_FileCSharp, Bundle_TextTSlash,
        Bundle_BatteryWarningVertical, Bundle_CodepenLogo, Bundle_ArrowsLeftRight, Bundle_HandGrabbing,
        Bundle_BugBeetle, Bundle_FirstAid, Bundle_SelectionAll, Bundle_ArrowsMerge,
        Bundle_Heartbeat, Bundle_StarAndCrescent, Bundle_HeartStraight, Bundle_BellRinging,
        Bundle_ArrowsOutCardinal, Bundle_HandPointing, Bundle_Certificate, Bundle_DropSlash,
        Bundle_ArrowsInLineVertical, Bundle_FileDashed, Bundle_Scroll, Bundle_SketchLogo,
        Bundle_Binary, Bundle_ArrowsInSimple, Bundle_ArrowsOutLineHorizontal, Bundle_BatteryCharging,
        Bundle_BellSimpleRinging,

        _COUNT
    };

    struct BootstrapVtable {
        uint32_t version;
        fn_register_module register_module;
        fn_unregister_module unregister_module;
        fn_register_render_callback register_render_callback;
        fn_unregister_render_callback unregister_render_callback;
        fn_get_imgui_context get_imgui_context;
        fn_register_log_callback register_log_callback;
        fn_unregister_log_callback unregister_log_callback;
        fn_get_console_options get_console_options;
        fn_set_console_options set_console_options;
        fn_show_gameobject_in_explorer show_gameobject_in_explorer;
        fn_show_component_in_explorer show_component_in_explorer;
        fn_register_explorer_callback register_explorer_callback;
        fn_unregister_explorer_callback unregister_explorer_callback;

        // VRChat
        fn_get_vrc_player_data get_vrc_player_data;
        fn_get_player_data get_player_data;
        fn_get_nameplate_data get_nameplate_data;
        fn_get_local_player get_local_player;
        fn_get_local_player_api get_local_player_api;
        fn_get_local_vrc_player get_local_vrc_player;
        fn_register_player_event register_player_event;
        fn_unregister_player_event unregister_player_event;
        fn_invoke_player_event invoke_player_event;

        // Config
        fn_config_set_int config_set_int;
        fn_config_get_int config_get_int;
        fn_config_set_float config_set_float;
        fn_config_get_float config_get_float;
        fn_config_set_string config_set_string;
        fn_config_get_string config_get_string;
        fn_config_set_bool config_set_bool;
        fn_config_get_bool config_get_bool;
        fn_config_save config_save;
        fn_config_has_key config_has_key;
        fn_config_remove_key config_remove_key;

        // Message bus
        fn_subscribe_message subscribe_message;
        fn_unsubscribe_message unsubscribe_message;
        fn_publish_message publish_message;

        // QuickMenu
        fn_qm_create_page qm_create_page;
        fn_qm_create_sub_page qm_create_sub_page;
        fn_qm_remove_page qm_remove_page;
        fn_qm_add_button qm_add_button;
        fn_qm_remove_button qm_remove_button;
        fn_qm_set_button_text qm_set_button_text;
        fn_qm_navigate_to qm_navigate_to;
        fn_qm_navigate_back qm_navigate_back;
        fn_qm_is_ready qm_is_ready;

        // QuickMenu — toggles, icons, colors, badges (v6)
        fn_qm_add_toggle qm_add_toggle;
        fn_qm_set_toggle_state qm_set_toggle_state;
        fn_qm_get_toggle_state qm_get_toggle_state;
        fn_qm_set_button_icon_ptr qm_set_button_icon_ptr;
        fn_qm_set_button_icon_vrc qm_set_button_icon_vrc;
        fn_qm_set_button_color qm_set_button_color;
        fn_qm_set_page_title qm_set_page_title;
        fn_qm_set_page_icon_ptr qm_set_page_icon_ptr;
        fn_qm_set_page_icon_vrc qm_set_page_icon_vrc;
        fn_qm_set_page_badge qm_set_page_badge;

        // QuickMenu v7 — enable/disable, visibility, sub-page nav, sprite utility
        fn_qm_set_button_enabled qm_set_button_enabled;
        fn_qm_set_button_visible qm_set_button_visible;
        fn_qm_get_subpage_nav_button qm_get_subpage_nav_button;
        fn_qm_set_subpage_nav_text qm_set_subpage_nav_text;
        fn_qm_set_subpage_nav_icon_vrc qm_set_subpage_nav_icon_vrc;
        fn_qm_set_image_sprite qm_set_image_sprite;

        // QuickMenu v8 — foldouts, settings toggles, enum selectors, sliders, separators
        fn_qm_add_foldout qm_add_foldout;
        fn_qm_set_foldout_expanded qm_set_foldout_expanded;
        fn_qm_get_foldout_expanded qm_get_foldout_expanded;
        fn_qm_add_settings_toggle qm_add_settings_toggle;
        fn_qm_add_enum_selector qm_add_enum_selector;
        fn_qm_set_enum_index qm_set_enum_index;
        fn_qm_get_enum_index qm_get_enum_index;
        fn_qm_add_slider qm_add_slider;
        fn_qm_set_slider_value qm_set_slider_value;
        fn_qm_get_slider_value qm_get_slider_value;
        fn_qm_add_separator qm_add_separator;

        // TweenService v9
        fn_tween_anchored_position tween_anchored_position;
        fn_tween_local_position tween_local_position;
        fn_tween_local_scale tween_local_scale;
        fn_tween_cancel tween_cancel;
        fn_tween_cancel_all tween_cancel_all;

        // NameplateService v10
        fn_np_create_plate np_create_plate;
        fn_np_destroy_plate np_destroy_plate;
        fn_np_destroy_plates_by_tag np_destroy_plates_by_tag;
        fn_np_set_plate_text np_set_plate_text;
        fn_np_set_plate_text_color np_set_plate_text_color;
        fn_np_set_plate_icon_color np_set_plate_icon_color;
        fn_np_set_plate_position np_set_plate_position;

        // ClientUsage v10
        fn_cu_register_client cu_register_client;
        fn_cu_is_client_registered cu_is_client_registered;

        // TweenService additions v10
        fn_tween_float tween_float;
        fn_tween_cancel_all_for_target tween_cancel_all_for_target;
        fn_tween_anchored_position_ex tween_anchored_position_ex;
        fn_tween_local_position_ex tween_local_position_ex;
        fn_tween_local_scale_ex tween_local_scale_ex;

        // PerformanceModule v10
        fn_perf_get_int perf_get_int;
        fn_perf_set_int perf_set_int;
        fn_perf_get_float perf_get_float;
        fn_perf_set_float perf_set_float;
        fn_perf_force_gc perf_force_gc;
        fn_perf_full_cleanup perf_full_cleanup;
    };

} // namespace Bootstrap
