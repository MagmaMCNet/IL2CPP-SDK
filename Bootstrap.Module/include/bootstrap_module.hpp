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

        void navigate_to(uint32_t page_id);
        void navigate_back();

    private:
        QuickMenu() = default;
    };

} // namespace Bootstrap::Module
