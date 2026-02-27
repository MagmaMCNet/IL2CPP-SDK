#include <include\logger_module.hpp>
#include <Windows.h>
#include <atomic>
#include <string>


namespace Logger::Module {

    namespace {

        struct ConnectionState {
            std::atomic<bool>   connected{ false };
            HANDLE              shared_memory_handle = nullptr;
            LoggerVtable const* vtable = nullptr;
        };

        ConnectionState g_conn;

    }

    bool Connect() {
        if (g_conn.connected.exchange(true, std::memory_order_acq_rel)) {
            return true;
        }

        std::wstring memName = std::wstring(shared_memory_prefix) + 
                               std::to_wstring(GetCurrentProcessId()) + 
                               shared_memory_suffix;

        g_conn.shared_memory_handle = OpenFileMappingW(FILE_MAP_READ, FALSE, memName.c_str());


        if (!g_conn.shared_memory_handle) {
            g_conn.connected.store(false, std::memory_order_release);
            return false;
        }

        g_conn.vtable = static_cast<LoggerVtable const*>(
            MapViewOfFile(g_conn.shared_memory_handle, FILE_MAP_READ, 0, 0, sizeof(LoggerVtable))
            );

        if (!g_conn.vtable || g_conn.vtable->version != vtable_version) {
            if (g_conn.vtable) {
                UnmapViewOfFile(const_cast<LoggerVtable*>(g_conn.vtable));
                g_conn.vtable = nullptr;
            }
            CloseHandle(g_conn.shared_memory_handle);
            g_conn.shared_memory_handle = nullptr;
            g_conn.connected.store(false, std::memory_order_release);
            return false;
        }

        return true;
    }

    void Disconnect() {
        if (!g_conn.connected.exchange(false, std::memory_order_acq_rel)) {
            return;
        }

        if (g_conn.vtable) {
            UnmapViewOfFile(const_cast<LoggerVtable*>(g_conn.vtable));
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

    void flush() {
        if (is_connected() && g_conn.vtable->flush) {
            g_conn.vtable->flush();
        }
    }

    Logger::Logger(std::string_view name) : m_name(name) {
        if (!is_connected() && !Connect()) return;

        m_id = g_conn.vtable->register_module(m_name.data(), static_cast<uint32_t>(m_name.size()));
    }

    Logger::~Logger() {
        if (m_id != invalid_id && is_connected()) {
            g_conn.vtable->unregister_module(m_id);
        }
    }

    Logger::Logger(Logger&& other) noexcept
        : m_id(std::exchange(other.m_id, invalid_id))
        , m_name(std::move(other.m_name)) {
    }

    Logger& Logger::operator=(Logger&& other) noexcept {
        if (this != &other) {
            if (m_id != invalid_id && is_connected()) {
                g_conn.vtable->unregister_module(m_id);
            }
            m_id = std::exchange(other.m_id, invalid_id);
            m_name = std::move(other.m_name);
        }
        return *this;
    }

    bool Logger::valid() const noexcept {
        return m_id != invalid_id && is_connected();
    }

    uint32_t Logger::id() const noexcept {
        return m_id;
    }

    std::string_view Logger::name() const noexcept {
        return m_name;
    }

    Submodule Logger::create_submodule(std::string_view name) {
        return Submodule(*this, name);
    }

    void Logger::set_mask(LevelMask mask) {
        if (valid()) {
            g_conn.vtable->set_module_mask(m_id, mask);
        }
    }

    void Logger::set_color(Color fg, Color bg) {
        if (valid()) {
            g_conn.vtable->set_module_color(m_id, fg, bg);
        }
    }

    bool Logger::is_enabled(Level lvl) const noexcept {
        return valid() && g_conn.vtable->is_enabled(lvl, { m_id, invalid_id });
    }

    void Logger::log(Level lvl, std::string_view message, std::source_location loc) const {
        if (!valid()) return;

        LogEntry entry{
            .lvl = lvl,
            .id = { m_id, invalid_id },
            .message = message.data(),
            .message_length = static_cast<uint32_t>(message.size()),
            .file = loc.file_name(),
            .line = loc.line(),
            .function = loc.function_name()
        };

        g_conn.vtable->log(&entry);
    }

    void Logger::trace(std::string_view msg, std::source_location loc) const { log(Level::trace, msg, loc); }
    void Logger::debug(std::string_view msg, std::source_location loc) const { log(Level::debug, msg, loc); }
    void Logger::info(std::string_view msg, std::source_location loc) const { log(Level::info, msg, loc); }
    void Logger::warn(std::string_view msg, std::source_location loc) const { log(Level::warn, msg, loc); }
    void Logger::error(std::string_view msg, std::source_location loc) const { log(Level::error, msg, loc); }
    void Logger::fatal(std::string_view msg, std::source_location loc) const { log(Level::fatal, msg, loc); }

    Submodule::Submodule(Logger const& parent, std::string_view name)
        : m_module_id(parent.m_id)
        , m_name(name) {
        if (!is_connected() || m_module_id == invalid_id) return;

        m_submodule_id = g_conn.vtable->register_submodule(m_module_id, m_name.data(), static_cast<uint32_t>(m_name.size()));
    }

    Submodule::~Submodule() {
        if (m_submodule_id != invalid_id && is_connected()) {
            g_conn.vtable->unregister_submodule(m_module_id, m_submodule_id);
        }
    }

    Submodule::Submodule(Submodule&& other) noexcept
        : m_module_id(std::exchange(other.m_module_id, invalid_id))
        , m_submodule_id(std::exchange(other.m_submodule_id, invalid_id))
        , m_name(std::move(other.m_name)) {
    }

    Submodule& Submodule::operator=(Submodule&& other) noexcept {
        if (this != &other) {
            if (m_submodule_id != invalid_id && is_connected()) {
                g_conn.vtable->unregister_submodule(m_module_id, m_submodule_id);
            }
            m_module_id = std::exchange(other.m_module_id, invalid_id);
            m_submodule_id = std::exchange(other.m_submodule_id, invalid_id);
            m_name = std::move(other.m_name);
        }
        return *this;
    }

    bool Submodule::valid() const noexcept {
        return m_module_id != invalid_id && m_submodule_id != invalid_id && is_connected();
    }

    ModuleId Submodule::id() const noexcept {
        return { m_module_id, m_submodule_id };
    }

    std::string_view Submodule::name() const noexcept {
        return m_name;
    }

    void Submodule::set_mask(LevelMask mask) {
        if (valid()) {
            g_conn.vtable->set_submodule_mask(m_module_id, m_submodule_id, mask);
        }
    }

    void Submodule::set_color(Color fg, Color bg) {
        if (valid()) {
            g_conn.vtable->set_submodule_color(m_module_id, m_submodule_id, fg, bg);
        }
    }

    bool Submodule::is_enabled(Level lvl) const noexcept {
        return valid() && g_conn.vtable->is_enabled(lvl, { m_module_id, m_submodule_id });
    }

    void Submodule::log(Level lvl, std::string_view message, std::source_location loc) const {
        if (!valid()) return;

        LogEntry entry{
            .lvl = lvl,
            .id = { m_module_id, m_submodule_id },
            .message = message.data(),
            .message_length = static_cast<uint32_t>(message.size()),
            .file = loc.file_name(),
            .line = loc.line(),
            .function = loc.function_name()
        };

        g_conn.vtable->log(&entry);
    }

    void Submodule::trace(std::string_view msg, std::source_location loc) const { log(Level::trace, msg, loc); }
    void Submodule::debug(std::string_view msg, std::source_location loc) const { log(Level::debug, msg, loc); }
    void Submodule::info(std::string_view msg, std::source_location loc) const { log(Level::info, msg, loc); }
    void Submodule::warn(std::string_view msg, std::source_location loc) const { log(Level::warn, msg, loc); }
    void Submodule::error(std::string_view msg, std::source_location loc) const { log(Level::error, msg, loc); }
    void Submodule::fatal(std::string_view msg, std::source_location loc) const { log(Level::fatal, msg, loc); }

}