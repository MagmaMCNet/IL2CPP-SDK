#include <bootstrap_module.hpp>
#include <bootstrap_internal.hpp>
#include <IL2CPP.Module/include/il2cpp_module.hpp>
#include <Windows.h>
#include <algorithm>
#include <atomic>
#include <cwchar>
#include <string>

namespace Bootstrap::Module {

    namespace {

        struct ConnectionState {
            std::atomic<bool> connected{ false };
            HANDLE shared_memory_handle = nullptr;
            Bootstrap::BootstrapVtable const* vtable = nullptr;
        };

        ConnectionState g_conn;

    }

    // Internal accessor for VRChat class implementations
    Bootstrap::BootstrapVtable const* get_vtable() noexcept {
        return g_conn.vtable;
    }

    bool Connect() {
        if (g_conn.connected.exchange(true, std::memory_order_acq_rel))
            return true;

        std::wstring memName = std::wstring(Bootstrap::shared_memory_prefix) +
                               std::to_wstring(GetCurrentProcessId()) +
                               Bootstrap::shared_memory_suffix;

        g_conn.shared_memory_handle = OpenFileMappingW(
            FILE_MAP_READ, FALSE, memName.c_str());


        if (!g_conn.shared_memory_handle) {
            g_conn.connected.store(false, std::memory_order_release);
            return false;
        }

        g_conn.vtable = static_cast<Bootstrap::BootstrapVtable const*>(
            MapViewOfFile(g_conn.shared_memory_handle, FILE_MAP_READ,
                0, 0, sizeof(Bootstrap::BootstrapVtable)));

        if (!g_conn.vtable || g_conn.vtable->version != Bootstrap::vtable_version) {
            if (g_conn.vtable) {
                UnmapViewOfFile(const_cast<Bootstrap::BootstrapVtable*>(g_conn.vtable));
                g_conn.vtable = nullptr;
            }
            CloseHandle(g_conn.shared_memory_handle);
            g_conn.shared_memory_handle = nullptr;
            g_conn.connected.store(false, std::memory_order_release);
            return false;
        }

        if (g_conn.vtable) {
            IL2CPP::Module::Connect();
        }
        return true;
    }

    void Disconnect() {
        if (!g_conn.connected.exchange(false, std::memory_order_acq_rel))
            return;

        if (g_conn.vtable) {
            UnmapViewOfFile(const_cast<Bootstrap::BootstrapVtable*>(g_conn.vtable));
            g_conn.vtable = nullptr;
        }

        if (g_conn.shared_memory_handle) {
            CloseHandle(g_conn.shared_memory_handle);
            g_conn.shared_memory_handle = nullptr;
        }
    }

    bool is_connected() noexcept {
        return g_conn.connected.load(std::memory_order_acquire) && g_conn.vtable;
    }

    BootstrapModule::BootstrapModule(std::string_view name) : m_name(name) {
        if (!is_connected() && !Connect()) return;

        m_id = g_conn.vtable->register_module(
            m_name.data(), static_cast<uint32_t>(m_name.size()), Bootstrap::sdk_version);
    }

    BootstrapModule::~BootstrapModule() {
        if (m_id != Bootstrap::invalid_id && is_connected()) {
            g_conn.vtable->unregister_module(m_id);
        }
    }

    BootstrapModule::BootstrapModule(BootstrapModule&& other) noexcept
        : m_id(std::exchange(other.m_id, Bootstrap::invalid_id))
        , m_name(std::move(other.m_name)) {
    }

    BootstrapModule& BootstrapModule::operator=(BootstrapModule&& other) noexcept {
        if (this != &other) {
            if (m_id != Bootstrap::invalid_id && is_connected()) {
                g_conn.vtable->unregister_module(m_id);
            }
            m_id = std::exchange(other.m_id, Bootstrap::invalid_id);
            m_name = std::move(other.m_name);
        }
        return *this;
    }

    bool BootstrapModule::valid() const noexcept {
        return m_id != Bootstrap::invalid_id && is_connected();
    }

    uint32_t BootstrapModule::id() const noexcept {
        return m_id;
    }

    std::string_view BootstrapModule::name() const noexcept {
        return m_name;
    }

    UnityConsole& UnityConsole::Get() {
        static UnityConsole instance;
        return instance;
    }

    bool UnityConsole::valid() const noexcept {
        return is_connected();
    }

    void UnityConsole::set_enable_colors(bool enable) {
        if (!valid()) return;
        Bootstrap::UnityConsoleOptions opts{};
        g_conn.vtable->get_console_options(&opts);
        opts.enable_colors = enable;
        g_conn.vtable->set_console_options(&opts);
    }

    void UnityConsole::set_file_logging(bool enable, std::wstring_view path) {
        if (!valid()) return;
        Bootstrap::UnityConsoleOptions opts{};
        g_conn.vtable->get_console_options(&opts);
        opts.enable_file_logging = enable;
        if (!path.empty()) {
            size_t copyLen = (std::min)(path.size(), static_cast<size_t>(259));
            wcsncpy_s(opts.log_file_path, 260, path.data(), copyLen);
        }
        g_conn.vtable->set_console_options(&opts);
    }

    void UnityConsole::set_enable_trace(bool enable) {
        if (!valid()) return;
        Bootstrap::UnityConsoleOptions opts{};
        g_conn.vtable->get_console_options(&opts);
        opts.enable_trace = enable;
        g_conn.vtable->set_console_options(&opts);
    }

    void UnityConsole::set_enable_info_trace(bool enable) {
        if (!valid()) return;
        Bootstrap::UnityConsoleOptions opts{};
        g_conn.vtable->get_console_options(&opts);
        opts.enable_info_trace = enable;
        g_conn.vtable->set_console_options(&opts);
    }

    void UnityConsole::set_deobfuscate_names(bool enable) {
        if (!valid()) return;
        Bootstrap::UnityConsoleOptions opts{};
        g_conn.vtable->get_console_options(&opts);
        opts.deobfuscate_names = enable;
        g_conn.vtable->set_console_options(&opts);
    }

    void UnityConsole::get_options(Bootstrap::UnityConsoleOptions* out) {
        if (!valid() || !out) return;
        g_conn.vtable->get_console_options(out);
    }

    void UnityConsole::set_options(Bootstrap::UnityConsoleOptions const* opts) {
        if (!valid() || !opts) return;
        g_conn.vtable->set_console_options(opts);
    }

    uint32_t UnityConsole::register_callback(uint32_t module_id, Bootstrap::fn_log_callback callback) {
        if (!valid() || !callback) return Bootstrap::invalid_id;
        return g_conn.vtable->register_log_callback(module_id, callback);
    }

    void UnityConsole::unregister_callback(uint32_t module_id, uint32_t callback_id) {
        if (!valid()) return;
        g_conn.vtable->unregister_log_callback(module_id, callback_id);
    }

    UnityExplorer& UnityExplorer::Get() {
        static UnityExplorer instance;
        return instance;
    }

    bool UnityExplorer::valid() const noexcept {
        return is_connected();
    }

    void UnityExplorer::show_game_object(void* gameObject) {
        if (!valid() || !gameObject) return;
        g_conn.vtable->show_gameobject_in_explorer(gameObject);
    }

    void UnityExplorer::show_component(void* component) {
        if (!valid() || !component) return;
        g_conn.vtable->show_component_in_explorer(component);
    }

    uint32_t UnityExplorer::register_on_navigate(uint32_t module_id, Bootstrap::fn_explorer_navigate_callback callback) {
        if (!valid() || !callback) return Bootstrap::invalid_id;
        return g_conn.vtable->register_explorer_callback(module_id, callback);
    }

    void UnityExplorer::unregister_on_navigate(uint32_t module_id, uint32_t callback_id) {
        if (!valid()) return;
        g_conn.vtable->unregister_explorer_callback(module_id, callback_id);
    }

    // ---- Rendering ----

    Rendering& Rendering::Get() {
        static Rendering instance;
        return instance;
    }

    bool Rendering::valid() const noexcept {
        return is_connected();
    }

    uint32_t Rendering::register_callback(uint32_t module_id, Bootstrap::fn_render_callback callback) {
        if (!valid() || !callback) return Bootstrap::invalid_id;
        return g_conn.vtable->register_render_callback(module_id, callback);
    }

    void Rendering::unregister_callback(uint32_t module_id, uint32_t callback_id) {
        if (!valid()) return;
        g_conn.vtable->unregister_render_callback(module_id, callback_id);
    }

    void* Rendering::get_imgui_context() {
        if (!valid()) return nullptr;
        return g_conn.vtable->get_imgui_context();
    }

}
