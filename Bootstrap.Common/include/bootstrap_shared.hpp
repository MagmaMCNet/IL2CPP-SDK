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
    constexpr uint32_t vtable_version = 4;
    
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
    };

} // namespace Bootstrap
