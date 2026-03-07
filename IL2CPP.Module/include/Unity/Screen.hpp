#pragma once
#include "../MethodHandler.hpp"
#include <IL2CPP.Common/il2cpp_types.hpp>

// ============================================================================
//  IL2CPP.Module::Unity::Screen - Static utility class for screen information
// ============================================================================

namespace IL2CPP::Module::Unity {

    enum class FullScreenMode : int {
        ExclusiveFullScreen = 0,
        FullScreenWindow = 1,
        MaximizedWindow = 2,
        Windowed = 3
    };

    struct Resolution {
        int width;
        int height;
        int refreshRate;
    };

    class Screen {
    public:
        Screen() = delete;

        [[nodiscard]] static int GetWidth() {
            static auto m = MethodHandler::resolve("UnityEngine.Screen", "get_width", 0);
            return MethodHandler::invoke<int>(m, nullptr);
        }

        [[nodiscard]] static int GetHeight() {
            static auto m = MethodHandler::resolve("UnityEngine.Screen", "get_height", 0);
            return MethodHandler::invoke<int>(m, nullptr);
        }

        [[nodiscard]] static float GetDpi() {
            static auto m = MethodHandler::resolve("UnityEngine.Screen", "get_dpi", 0);
            return MethodHandler::invoke<float>(m, nullptr);
        }

        [[nodiscard]] static bool GetFullScreen() {
            static auto m = MethodHandler::resolve("UnityEngine.Screen", "get_fullScreen", 0);
            return MethodHandler::invoke<bool>(m, nullptr);
        }

        static void SetFullScreen(bool fullScreen) {
            static auto m = MethodHandler::resolve("UnityEngine.Screen", "set_fullScreen", 1);
            void* params[] = { &fullScreen };
            MethodHandler::invoke(m, nullptr, params);
        }

        [[nodiscard]] static FullScreenMode GetFullScreenMode() {
            static auto m = MethodHandler::resolve("UnityEngine.Screen", "get_fullScreenMode", 0);
            return static_cast<FullScreenMode>(MethodHandler::invoke<int>(m, nullptr));
        }

        static void SetFullScreenMode(FullScreenMode mode) {
            static auto m = MethodHandler::resolve("UnityEngine.Screen", "set_fullScreenMode", 1);
            int val = static_cast<int>(mode);
            void* params[] = { &val };
            MethodHandler::invoke(m, nullptr, params);
        }

        [[nodiscard]] static Resolution GetCurrentResolution() {
            static auto m = MethodHandler::resolve("UnityEngine.Screen", "get_currentResolution", 0);
            return MethodHandler::invoke<Resolution>(m, nullptr);
        }

        static void SetResolution(int width, int height, bool fullScreen, int refreshRate = 0) {
            static auto m = MethodHandler::resolve("UnityEngine.Screen", "SetResolution", 4);
            void* params[] = { &width, &height, &fullScreen, &refreshRate };
            MethodHandler::invoke(m, nullptr, params);
        }

        // ---- Legacy snake_case aliases (deprecated) ----
        [[deprecated("Use GetWidth()")]] [[nodiscard]] static int get_width() { return GetWidth(); }
        [[deprecated("Use GetHeight()")]] [[nodiscard]] static int get_height() { return GetHeight(); }
        [[deprecated("Use GetDpi()")]] [[nodiscard]] static float get_dpi() { return GetDpi(); }
        [[deprecated("Use GetFullScreen()")]] [[nodiscard]] static bool get_full_screen() { return GetFullScreen(); }
        [[deprecated("Use SetFullScreen()")]] static void set_full_screen(bool f) { SetFullScreen(f); }
        [[deprecated("Use GetFullScreenMode()")]] [[nodiscard]] static FullScreenMode get_full_screen_mode() { return GetFullScreenMode(); }
        [[deprecated("Use SetFullScreenMode()")]] static void set_full_screen_mode(FullScreenMode m) { SetFullScreenMode(m); }
        [[deprecated("Use GetCurrentResolution()")]] [[nodiscard]] static Resolution get_current_resolution() { return GetCurrentResolution(); }
        [[deprecated("Use SetResolution()")]] static void set_resolution(int w, int h, bool f, int r = 0) { SetResolution(w, h, f, r); }
    };

} // namespace IL2CPP::Module::Unity
