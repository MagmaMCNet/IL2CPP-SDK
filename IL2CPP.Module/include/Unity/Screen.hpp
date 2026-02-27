#pragma once
#include "Object.hpp"
#include <IL2CPP.Common/il2cpp_types.hpp>
#include <IL2CPP.Common/il2cpp_shared.hpp>

// ============================================================================
//  IL2CPP.Module::Unity::Screen - Static utility class for screen information
// ============================================================================

namespace IL2CPP::Module::Unity {

    // Forward declare full screen mode enum
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

        // ---- Screen Dimensions ----

        /// Get the current screen width in pixels.
        [[nodiscard]] static int GetWidth() {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->screen.m_GetWidth) return 0;
            return reinterpret_cast<int(IL2CPP_CALLTYPE)()>(fn->screen.m_GetWidth)();
        }

        /// Get the current screen height in pixels.
        [[nodiscard]] static int GetHeight() {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->screen.m_GetHeight) return 0;
            return reinterpret_cast<int(IL2CPP_CALLTYPE)()>(fn->screen.m_GetHeight)();
        }

        /// Get the screen DPI.
        [[nodiscard]] static float GetDpi() {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->screen.m_GetDpi) return 96.f;
            return reinterpret_cast<float(IL2CPP_CALLTYPE)()>(fn->screen.m_GetDpi)();
        }

        // ---- Full Screen ----

        /// Check if the application is in full screen mode.
        [[nodiscard]] static bool GetFullScreen() {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->screen.m_GetFullScreen) return false;
            return reinterpret_cast<bool(IL2CPP_CALLTYPE)()>(fn->screen.m_GetFullScreen)();
        }

        /// Set full screen mode.
        static void SetFullScreen(bool fullScreen) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->screen.m_SetFullScreen) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(bool)>(fn->screen.m_SetFullScreen)(fullScreen);
        }

        /// Get the current full screen mode.
        [[nodiscard]] static FullScreenMode GetFullScreenMode() {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->screen.m_GetFullScreenMode) return FullScreenMode::Windowed;
            return static_cast<FullScreenMode>(reinterpret_cast<int(IL2CPP_CALLTYPE)()>(fn->screen.m_GetFullScreenMode)());
        }

        /// Set the full screen mode.
        static void SetFullScreenMode(FullScreenMode mode) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->screen.m_SetFullScreenMode) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(int)>(fn->screen.m_SetFullScreenMode)(static_cast<int>(mode));
        }

        // ---- Resolution ----

        /// Get the current screen resolution.
        [[nodiscard]] static Resolution GetCurrentResolution() {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->screen.m_GetCurrentResolution) return Resolution{ 0, 0, 0 };
            Resolution r;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(Resolution*)>(fn->screen.m_GetCurrentResolution)(&r);
            return r;
        }

        /// Set the screen resolution.
        static void SetResolution(int width, int height, bool fullScreen, int refreshRate = 0) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->screen.m_SetResolution) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(int, int, bool, int)>(fn->screen.m_SetResolution)(width, height, fullScreen, refreshRate);
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
