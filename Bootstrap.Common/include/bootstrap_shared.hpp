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
    constexpr uint32_t vtable_version = 6;
    
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
    };

} // namespace Bootstrap
