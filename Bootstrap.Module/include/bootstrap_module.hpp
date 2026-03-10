#pragma once

// ============================================================================
//  bootstrap_module.hpp - Public API for mod developers
//
//  Connect to Bootstrap shared memory, access Unity Console and Unity Explorer.
//  VRChat class wrappers are in the VRChat/ subdirectory (IL2CPP::VRChat namespace).
//
//  Usage:
//      Bootstrap::Module::Connect();
//      Bootstrap::Module::BootstrapModule mod("MyMod");
//      auto& console = Bootstrap::Module::UnityConsole::Get();
//      console.set_enable_colors(true);
//      uint32_t cid = console.register_callback(mod.id(), my_log_callback);
//
//      // VRChat classes:
//      auto player = IL2CPP::VRChat::VRCPlayerApi::GetLocalPlayer();
//      auto name = player.GetDisplayName();
// ============================================================================

#include <Bootstrap.Common/include/bootstrap_shared.hpp>
#include <IL2CPP.Module/include/il2cpp_module.hpp>
#include <string_view>
#include <string>

// VRChat class wrappers (IL2CPP::VRChat namespace)
#include "VRChat/VRChat.hpp"

namespace Bootstrap::Module {

    [[nodiscard]] bool Connect();
    void Disconnect();
    [[nodiscard]] bool is_connected() noexcept;

    class BootstrapModule {
    public:
        BootstrapModule() = default;
        explicit BootstrapModule(std::string_view name);
        ~BootstrapModule();

        BootstrapModule(BootstrapModule const&) = delete;
        BootstrapModule& operator=(BootstrapModule const&) = delete;
        BootstrapModule(BootstrapModule&& other) noexcept;
        BootstrapModule& operator=(BootstrapModule&& other) noexcept;

        [[nodiscard]] bool valid() const noexcept;
        [[nodiscard]] uint32_t id() const noexcept;
        [[nodiscard]] std::string_view name() const noexcept;

    private:
        uint32_t m_id = invalid_id;
        std::string m_name;

        friend class UnityConsole;
        friend class UnityExplorer;
    };

    class UnityConsole {
    public:
        static UnityConsole& Get();

        void set_enable_colors(bool enable);
        void set_file_logging(bool enable, std::wstring_view path = L"");
        void set_enable_trace(bool enable);
        void set_enable_info_trace(bool enable);
        void set_deobfuscate_names(bool enable);

        void get_options(Bootstrap::UnityConsoleOptions* out);
        void set_options(Bootstrap::UnityConsoleOptions const* opts);

        uint32_t register_callback(uint32_t module_id, Bootstrap::fn_log_callback callback);
        void unregister_callback(uint32_t module_id, uint32_t callback_id);

        [[nodiscard]] bool valid() const noexcept;

    private:
        UnityConsole() = default;
    };

    class UnityExplorer {
    public:
        static UnityExplorer& Get();

        void show_game_object(void* gameObject);
        void show_component(void* component);

        uint32_t register_on_navigate(uint32_t module_id, Bootstrap::fn_explorer_navigate_callback callback);
        void unregister_on_navigate(uint32_t module_id, uint32_t callback_id);

        [[nodiscard]] bool valid() const noexcept;

    private:
        UnityExplorer() = default;
    };

    class Rendering {
    public:
        static Rendering& Get();

        uint32_t register_callback(uint32_t module_id, Bootstrap::fn_render_callback callback);
        void unregister_callback(uint32_t module_id, uint32_t callback_id);

        void* get_imgui_context();

        [[nodiscard]] bool valid() const noexcept;

    private:
        Rendering() = default;
    };

    class ModuleConfig {
    public:
        explicit ModuleConfig(uint32_t module_id);

        void set_int(std::string_view key, int32_t value);
        int32_t get_int(std::string_view key, int32_t default_val = 0);
        void set_float(std::string_view key, float value);
        float get_float(std::string_view key, float default_val = 0.f);
        void set_string(std::string_view key, std::string_view value);
        std::string get_string(std::string_view key, std::string_view default_val = "");
        void set_bool(std::string_view key, bool value);
        bool get_bool(std::string_view key, bool default_val = false);
        void save();
        bool has_key(std::string_view key);
        void remove_key(std::string_view key);

    private:
        uint32_t m_module_id;
    };

    class MessageBus {
    public:
        static MessageBus& Get();

        uint32_t subscribe(uint32_t module_id, std::string_view topic, Bootstrap::fn_message_callback cb);
        void unsubscribe(uint32_t module_id, uint32_t subscription_id);
        void publish(uint32_t module_id, std::string_view topic, const void* data, uint32_t data_len);
        void publish(uint32_t module_id, std::string_view topic, std::string_view message);

    private:
        MessageBus() = default;
    };

    class QuickMenu {
    public:
        static QuickMenu& Get();

        [[nodiscard]] bool valid() const noexcept;
        [[nodiscard]] bool is_ready();

        uint32_t create_page(uint32_t module_id, std::string_view name, std::string_view tooltip = "");
        uint32_t create_sub_page(uint32_t module_id, uint32_t parent_page_id, std::string_view name);
        void remove_page(uint32_t module_id, uint32_t page_id);

        uint32_t add_button(uint32_t module_id, uint32_t page_id, std::string_view text,
                            Bootstrap::fn_menu_button_callback callback);
        void remove_button(uint32_t module_id, uint32_t button_id);
        void set_button_text(uint32_t module_id, uint32_t button_id, std::string_view text);

        // Toggle buttons
        uint32_t add_toggle(uint32_t module_id, uint32_t page_id, std::string_view text,
                            bool default_state, Bootstrap::fn_menu_toggle_callback callback,
                            std::string_view config_key = "");
        void set_toggle_state(uint32_t module_id, uint32_t button_id, bool state);
        bool get_toggle_state(uint32_t module_id, uint32_t button_id);

        // Icons & colors
        void set_button_icon(uint32_t module_id, uint32_t button_id, void* sprite_ptr);
        void set_button_icon(uint32_t module_id, uint32_t button_id, int32_t sprite_id);
        void set_button_color(uint32_t module_id, uint32_t button_id, float r, float g, float b, float a);

        // Page customization
        void set_page_title(uint32_t module_id, uint32_t page_id, std::string_view title);
        void set_page_icon(uint32_t module_id, uint32_t page_id, void* sprite_ptr);
        void set_page_icon(uint32_t module_id, uint32_t page_id, int32_t sprite_id);
        void set_page_badge(uint32_t module_id, uint32_t page_id, bool visible,
                            std::string_view text = "", float r = 0, float g = 0, float b = 0, float a = 0);
        void set_page_badge(uint32_t module_id, uint32_t page_id, bool visible, std::string_view text,
                            std::nullptr_t no_color);

        // v7 — enable/disable, visibility, sub-page nav, sprite utility
        void set_button_enabled(uint32_t module_id, uint32_t button_id, bool enabled);
        void set_button_visible(uint32_t module_id, uint32_t button_id, bool visible);
        uint32_t get_subpage_nav_button(uint32_t module_id, uint32_t sub_page_id);
        void set_subpage_nav_text(uint32_t module_id, uint32_t sub_page_id, std::string_view text);
        void set_subpage_nav_icon(uint32_t module_id, uint32_t sub_page_id, int32_t sprite_id);
        void set_image_sprite(void* image_component, int32_t sprite_id);

        // v8 — foldouts, settings toggles, enum selectors, sliders, separators
        uint32_t add_foldout(uint32_t module_id, uint32_t page_id, std::string_view title,
                             bool default_expanded = true, bool show_background = false);
        void set_foldout_expanded(uint32_t module_id, uint32_t foldout_id, bool expanded);
        bool get_foldout_expanded(uint32_t module_id, uint32_t foldout_id);

        uint32_t add_settings_toggle(uint32_t module_id, uint32_t foldout_id, std::string_view text,
                                     bool default_state, Bootstrap::fn_menu_toggle_callback callback,
                                     std::string_view config_key = "", bool show_sub_element_indicator = false);
        uint32_t add_enum_selector(uint32_t module_id, uint32_t foldout_id, std::string_view label,
                                   const char* const* options, uint32_t option_count,
                                   int32_t default_index, Bootstrap::fn_menu_enum_callback callback,
                                   std::string_view config_key = "", bool show_sub_element_indicator = false);
        void set_enum_index(uint32_t module_id, uint32_t selector_id, int32_t index);
        int32_t get_enum_index(uint32_t module_id, uint32_t selector_id);

        uint32_t add_slider(uint32_t module_id, uint32_t foldout_id, std::string_view label,
                            float min_val, float max_val, float default_val,
                            Bootstrap::fn_menu_slider_callback callback,
                            std::string_view config_key = "", std::string_view format_str = "",
                            bool show_sub_element_indicator = false);
        void set_slider_value(uint32_t module_id, uint32_t slider_id, float value);
        float get_slider_value(uint32_t module_id, uint32_t slider_id);

        uint32_t add_separator(uint32_t module_id, uint32_t foldout_id);

        void navigate_to(uint32_t page_id);
        void navigate_back();

    private:
        QuickMenu() = default;
    };

    class PlayerEvents {
    public:
        static PlayerEvents& Get();

        uint32_t register_event(uint32_t module_id, Bootstrap::PlayerEvent event,
                                Bootstrap::fn_player_simple_callback callback);
        void unregister_event(uint32_t module_id, uint32_t callback_id);
        void invoke(void* player, Bootstrap::PlayerEvent event);

        void* get_local_player();
        void* get_local_player_api();
        void* get_local_vrc_player();

    private:
        PlayerEvents() = default;
    };

    class TweenService {
    public:
        static TweenService& Get();

        uint32_t anchored_position(uint32_t module_id, void* rect_transform,
                                   float from_x, float from_y, float to_x, float to_y,
                                   float duration_ms, int32_t ease_type = 0);
        uint32_t local_position(uint32_t module_id, void* transform,
                                float from_x, float from_y, float from_z,
                                float to_x, float to_y, float to_z,
                                float duration_ms, int32_t ease_type = 0);
        uint32_t local_scale(uint32_t module_id, void* transform,
                             float from_x, float from_y, float from_z,
                             float to_x, float to_y, float to_z,
                             float duration_ms, int32_t ease_type = 0);
        void cancel(uint32_t tween_id);
        void cancel_all(uint32_t module_id);

    private:
        TweenService() = default;
    };

} // namespace Bootstrap::Module
