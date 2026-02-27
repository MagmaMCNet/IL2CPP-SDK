#pragma once
#include "Object.hpp"
#include <IL2CPP.Common/il2cpp_types.hpp>
#include <IL2CPP.Common/il2cpp_shared.hpp>
#include <string>
#include <string_view>

// ============================================================================
//  IL2CPP.Module::Unity::Application - Static utility class for application info
// ============================================================================

namespace IL2CPP::Module::Unity {

    enum class RuntimePlatform : int {
        OSXEditor = 0,
        OSXPlayer = 1,
        WindowsPlayer = 2,
        WindowsEditor = 7,
        IPhonePlayer = 8,
        Android = 11,
        LinuxPlayer = 13,
        LinuxEditor = 16,
        WebGLPlayer = 17,
        PS4 = 25,
        XboxOne = 27,
        Switch = 32
    };

    class Application {
    public:
        Application() = delete;

        // ---- Paths ----

        /// Get the data path (read-only).
        [[nodiscard]] static std::string GetDataPath() {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->application.m_GetDataPath) return "";
            auto* str = reinterpret_cast<void*(IL2CPP_CALLTYPE)()>(fn->application.m_GetDataPath)();
            if (!str) return "";
            int len = *reinterpret_cast<int*>(static_cast<char*>(str) + 0x10);
            if (len <= 0) return "";
            wchar_t* wstr = reinterpret_cast<wchar_t*>(static_cast<char*>(str) + 0x14);
            std::wstring ws(wstr, len);
            return std::string(ws.begin(), ws.end());
        }

        /// Get the persistent data path (read-write).
        [[nodiscard]] static std::string GetPersistentDataPath() {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->application.m_GetPersistentDataPath) return "";
            auto* str = reinterpret_cast<void*(IL2CPP_CALLTYPE)()>(fn->application.m_GetPersistentDataPath)();
            if (!str) return "";
            int len = *reinterpret_cast<int*>(static_cast<char*>(str) + 0x10);
            if (len <= 0) return "";
            wchar_t* wstr = reinterpret_cast<wchar_t*>(static_cast<char*>(str) + 0x14);
            std::wstring ws(wstr, len);
            return std::string(ws.begin(), ws.end());
        }

        /// Get the streaming assets path.
        [[nodiscard]] static std::string GetStreamingAssetsPath() {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->application.m_GetStreamingAssetsPath) return "";
            auto* str = reinterpret_cast<void*(IL2CPP_CALLTYPE)()>(fn->application.m_GetStreamingAssetsPath)();
            if (!str) return "";
            int len = *reinterpret_cast<int*>(static_cast<char*>(str) + 0x10);
            if (len <= 0) return "";
            wchar_t* wstr = reinterpret_cast<wchar_t*>(static_cast<char*>(str) + 0x14);
            std::wstring ws(wstr, len);
            return std::string(ws.begin(), ws.end());
        }

        // ---- State ----

        /// Check if the application is playing.
        [[nodiscard]] static bool GetIsPlaying() {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->application.m_GetIsPlaying) return true;
            return reinterpret_cast<bool(IL2CPP_CALLTYPE)()>(fn->application.m_GetIsPlaying)();
        }

        /// Check if running in the Unity editor.
        [[nodiscard]] static bool GetIsEditor() {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->application.m_GetIsEditor) return false;
            return reinterpret_cast<bool(IL2CPP_CALLTYPE)()>(fn->application.m_GetIsEditor)();
        }

        /// Get the runtime platform.
        [[nodiscard]] static RuntimePlatform GetPlatform() {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->application.m_GetPlatform) return RuntimePlatform::WindowsPlayer;
            return static_cast<RuntimePlatform>(reinterpret_cast<int(IL2CPP_CALLTYPE)()>(fn->application.m_GetPlatform)());
        }

        // ---- Version Info ----

        /// Get the application version string.
        [[nodiscard]] static std::string GetVersion() {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->application.m_GetVersion) return "";
            auto* str = reinterpret_cast<void*(IL2CPP_CALLTYPE)()>(fn->application.m_GetVersion)();
            if (!str) return "";
            int len = *reinterpret_cast<int*>(static_cast<char*>(str) + 0x10);
            if (len <= 0) return "";
            wchar_t* wstr = reinterpret_cast<wchar_t*>(static_cast<char*>(str) + 0x14);
            std::wstring ws(wstr, len);
            return std::string(ws.begin(), ws.end());
        }

        /// Get the product name.
        [[nodiscard]] static std::string GetProductName() {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->application.m_GetProductName) return "";
            auto* str = reinterpret_cast<void*(IL2CPP_CALLTYPE)()>(fn->application.m_GetProductName)();
            if (!str) return "";
            int len = *reinterpret_cast<int*>(static_cast<char*>(str) + 0x10);
            if (len <= 0) return "";
            wchar_t* wstr = reinterpret_cast<wchar_t*>(static_cast<char*>(str) + 0x14);
            std::wstring ws(wstr, len);
            return std::string(ws.begin(), ws.end());
        }

        /// Get the company name.
        [[nodiscard]] static std::string GetCompanyName() {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->application.m_GetCompanyName) return "";
            auto* str = reinterpret_cast<void*(IL2CPP_CALLTYPE)()>(fn->application.m_GetCompanyName)();
            if (!str) return "";
            int len = *reinterpret_cast<int*>(static_cast<char*>(str) + 0x10);
            if (len <= 0) return "";
            wchar_t* wstr = reinterpret_cast<wchar_t*>(static_cast<char*>(str) + 0x14);
            std::wstring ws(wstr, len);
            return std::string(ws.begin(), ws.end());
        }

        // ---- Control ----

        /// Quit the application.
        static void Quit() {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->application.m_Quit) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)()>(fn->application.m_Quit)();
        }

        /// Quit the application with an exit code.
        static void Quit(int exitCode) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->application.m_QuitWithExitCode) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(int)>(fn->application.m_QuitWithExitCode)(exitCode);
        }

        /// Open a URL in the default browser.
        static void OpenURL(std::string_view url) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->application.m_OpenURL) return;
            auto* exports = GetExports();
            if (!exports || !exports->m_stringNew) return;
            void* il2cppStr = reinterpret_cast<void*(IL2CPP_CALLTYPE)(const char*)>(exports->m_stringNew)(
                std::string(url).c_str());
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*)>(fn->application.m_OpenURL)(il2cppStr);
        }

        // ---- Frame Rate ----

        /// Get the target frame rate (-1 = vsync, 0 = uncapped).
        [[nodiscard]] static int GetTargetFrameRate() {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->application.m_GetTargetFrameRate) return -1;
            return reinterpret_cast<int(IL2CPP_CALLTYPE)()>(fn->application.m_GetTargetFrameRate)();
        }

        /// Set the target frame rate.
        static void SetTargetFrameRate(int frameRate) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->application.m_SetTargetFrameRate) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(int)>(fn->application.m_SetTargetFrameRate)(frameRate);
        }

        // ---- Legacy snake_case aliases (deprecated) ----
        [[deprecated("Use GetDataPath()")]] [[nodiscard]] static std::string get_data_path() { return GetDataPath(); }
        [[deprecated("Use GetPersistentDataPath()")]] [[nodiscard]] static std::string get_persistent_data_path() { return GetPersistentDataPath(); }
        [[deprecated("Use GetStreamingAssetsPath()")]] [[nodiscard]] static std::string get_streaming_assets_path() { return GetStreamingAssetsPath(); }
        [[deprecated("Use GetIsPlaying()")]] [[nodiscard]] static bool get_is_playing() { return GetIsPlaying(); }
        [[deprecated("Use GetIsEditor()")]] [[nodiscard]] static bool get_is_editor() { return GetIsEditor(); }
        [[deprecated("Use GetPlatform()")]] [[nodiscard]] static RuntimePlatform get_platform() { return GetPlatform(); }
        [[deprecated("Use GetVersion()")]] [[nodiscard]] static std::string get_version() { return GetVersion(); }
        [[deprecated("Use GetProductName()")]] [[nodiscard]] static std::string get_product_name() { return GetProductName(); }
        [[deprecated("Use GetCompanyName()")]] [[nodiscard]] static std::string get_company_name() { return GetCompanyName(); }
        [[deprecated("Use Quit()")]] static void quit() { Quit(); }
        [[deprecated("Use OpenURL()")]] static void open_url(std::string_view u) { OpenURL(u); }
        [[deprecated("Use GetTargetFrameRate()")]] [[nodiscard]] static int get_target_frame_rate() { return GetTargetFrameRate(); }
        [[deprecated("Use SetTargetFrameRate()")]] static void set_target_frame_rate(int f) { SetTargetFrameRate(f); }
    };

} // namespace IL2CPP::Module::Unity
