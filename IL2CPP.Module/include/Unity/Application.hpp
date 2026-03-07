#pragma once
#include "../MethodHandler.hpp"
#include <IL2CPP.Common/il2cpp_types.hpp>
#include <IL2CPP.Common/il2cpp_shared.hpp>
#include <string>
#include <string_view>

// ============================================================================
//  IL2CPP.Module::Unity::Application - Static utility class for application info
// ============================================================================

namespace IL2CPP::Module {
    [[nodiscard]] IL2CPP::il2cpp_exports const* GetExports() noexcept;
}

namespace IL2CPP::Module::Unity {

    enum class RuntimePlatform : int {
        OSXEditor = 0, OSXPlayer = 1, WindowsPlayer = 2, WindowsEditor = 7,
        IPhonePlayer = 8, Android = 11, LinuxPlayer = 13, LinuxEditor = 16,
        WebGLPlayer = 17, PS4 = 25, XboxOne = 27, Switch = 32
    };

    class Application {
    public:
        Application() = delete;

    private:
        static std::string InvokeStringGetter(const char* methodName) {
            static std::unordered_map<std::string, Method> cache;
            auto it = cache.find(methodName);
            if (it == cache.end()) {
                it = cache.emplace(methodName, MethodHandler::resolve("UnityEngine.Application", methodName, 0)).first;
            }
            void* str = MethodHandler::invoke<void*>(it->second, nullptr);
            if (!str) return "";
            int len = *reinterpret_cast<int*>(static_cast<char*>(str) + 0x10);
            if (len <= 0) return "";
            wchar_t* wstr = reinterpret_cast<wchar_t*>(static_cast<char*>(str) + 0x14);
            std::wstring ws(wstr, len);
            return std::string(ws.begin(), ws.end());
        }

    public:
        [[nodiscard]] static std::string GetDataPath() {
            static auto m = MethodHandler::resolve("UnityEngine.Application", "get_dataPath", 0);
            void* str = MethodHandler::invoke<void*>(m, nullptr);
            if (!str) return "";
            int len = *reinterpret_cast<int*>(static_cast<char*>(str) + 0x10);
            if (len <= 0) return "";
            wchar_t* wstr = reinterpret_cast<wchar_t*>(static_cast<char*>(str) + 0x14);
            std::wstring ws(wstr, len);
            return std::string(ws.begin(), ws.end());
        }

        [[nodiscard]] static std::string GetPersistentDataPath() {
            static auto m = MethodHandler::resolve("UnityEngine.Application", "get_persistentDataPath", 0);
            void* str = MethodHandler::invoke<void*>(m, nullptr);
            if (!str) return "";
            int len = *reinterpret_cast<int*>(static_cast<char*>(str) + 0x10);
            if (len <= 0) return "";
            wchar_t* wstr = reinterpret_cast<wchar_t*>(static_cast<char*>(str) + 0x14);
            std::wstring ws(wstr, len);
            return std::string(ws.begin(), ws.end());
        }

        [[nodiscard]] static std::string GetStreamingAssetsPath() {
            static auto m = MethodHandler::resolve("UnityEngine.Application", "get_streamingAssetsPath", 0);
            void* str = MethodHandler::invoke<void*>(m, nullptr);
            if (!str) return "";
            int len = *reinterpret_cast<int*>(static_cast<char*>(str) + 0x10);
            if (len <= 0) return "";
            wchar_t* wstr = reinterpret_cast<wchar_t*>(static_cast<char*>(str) + 0x14);
            std::wstring ws(wstr, len);
            return std::string(ws.begin(), ws.end());
        }

        [[nodiscard]] static bool GetIsPlaying() {
            static auto m = MethodHandler::resolve("UnityEngine.Application", "get_isPlaying", 0);
            return MethodHandler::invoke<bool>(m, nullptr);
        }

        [[nodiscard]] static bool GetIsEditor() {
            static auto m = MethodHandler::resolve("UnityEngine.Application", "get_isEditor", 0);
            return MethodHandler::invoke<bool>(m, nullptr);
        }

        [[nodiscard]] static RuntimePlatform GetPlatform() {
            static auto m = MethodHandler::resolve("UnityEngine.Application", "get_platform", 0);
            return static_cast<RuntimePlatform>(MethodHandler::invoke<int>(m, nullptr));
        }

        [[nodiscard]] static std::string GetVersion() {
            static auto m = MethodHandler::resolve("UnityEngine.Application", "get_version", 0);
            void* str = MethodHandler::invoke<void*>(m, nullptr);
            if (!str) return "";
            int len = *reinterpret_cast<int*>(static_cast<char*>(str) + 0x10);
            if (len <= 0) return "";
            wchar_t* wstr = reinterpret_cast<wchar_t*>(static_cast<char*>(str) + 0x14);
            std::wstring ws(wstr, len);
            return std::string(ws.begin(), ws.end());
        }

        [[nodiscard]] static std::string GetProductName() {
            static auto m = MethodHandler::resolve("UnityEngine.Application", "get_productName", 0);
            void* str = MethodHandler::invoke<void*>(m, nullptr);
            if (!str) return "";
            int len = *reinterpret_cast<int*>(static_cast<char*>(str) + 0x10);
            if (len <= 0) return "";
            wchar_t* wstr = reinterpret_cast<wchar_t*>(static_cast<char*>(str) + 0x14);
            std::wstring ws(wstr, len);
            return std::string(ws.begin(), ws.end());
        }

        [[nodiscard]] static std::string GetCompanyName() {
            static auto m = MethodHandler::resolve("UnityEngine.Application", "get_companyName", 0);
            void* str = MethodHandler::invoke<void*>(m, nullptr);
            if (!str) return "";
            int len = *reinterpret_cast<int*>(static_cast<char*>(str) + 0x10);
            if (len <= 0) return "";
            wchar_t* wstr = reinterpret_cast<wchar_t*>(static_cast<char*>(str) + 0x14);
            std::wstring ws(wstr, len);
            return std::string(ws.begin(), ws.end());
        }

        static void Quit() {
            static auto m = MethodHandler::resolve("UnityEngine.Application", "Quit", 0);
            MethodHandler::invoke(m, nullptr);
        }

        static void Quit(int exitCode) {
            static auto m = MethodHandler::resolve("UnityEngine.Application", "Quit", 1);
            void* params[] = { &exitCode };
            MethodHandler::invoke(m, nullptr, params);
        }

        static void OpenURL(std::string_view url) {
            static auto m = MethodHandler::resolve("UnityEngine.Application", "OpenURL", 1);
            auto* exports = GetExports();
            if (!exports || !exports->m_stringNew) return;
            void* il2cppStr = reinterpret_cast<void*(IL2CPP_CALLTYPE)(const char*)>(exports->m_stringNew)(
                std::string(url).c_str());
            void* params[] = { il2cppStr };
            MethodHandler::invoke(m, nullptr, params);
        }

        [[nodiscard]] static int GetTargetFrameRate() {
            static auto m = MethodHandler::resolve("UnityEngine.Application", "get_targetFrameRate", 0);
            return MethodHandler::invoke<int>(m, nullptr);
        }

        static void SetTargetFrameRate(int frameRate) {
            static auto m = MethodHandler::resolve("UnityEngine.Application", "set_targetFrameRate", 1);
            void* params[] = { &frameRate };
            MethodHandler::invoke(m, nullptr, params);
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
