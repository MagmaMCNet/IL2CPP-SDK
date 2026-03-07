#pragma once
#include "../MethodHandler.hpp"

// ============================================================================
//  IL2CPP.Module::Unity::Cursor - Static utility class for cursor control
// ============================================================================

namespace IL2CPP::Module::Unity {

    enum class CursorLockMode : int {
        None = 0,       // Cursor is free to move
        Locked = 1,     // Cursor is locked to center of screen
        Confined = 2    // Cursor is confined to game window
    };

    class Cursor {
    public:
        Cursor() = delete;

        // ---- Visibility ----

        [[nodiscard]] static bool GetVisible() {
            static auto m = MethodHandler::resolve("UnityEngine.Cursor", "get_visible", 0);
            return MethodHandler::invoke<bool>(m, nullptr);
        }

        static void SetVisible(bool visible) {
            static auto m = MethodHandler::resolve("UnityEngine.Cursor", "set_visible", 1);
            void* params[] = { &visible };
            MethodHandler::invoke(m, nullptr, params);
        }

        // ---- Lock State ----

        [[nodiscard]] static CursorLockMode GetLockState() {
            static auto m = MethodHandler::resolve("UnityEngine.Cursor", "get_lockState", 0);
            return static_cast<CursorLockMode>(MethodHandler::invoke<int>(m, nullptr));
        }

        static void SetLockState(CursorLockMode lockMode) {
            static auto m = MethodHandler::resolve("UnityEngine.Cursor", "set_lockState", 1);
            int val = static_cast<int>(lockMode);
            void* params[] = { &val };
            MethodHandler::invoke(m, nullptr, params);
        }

        // ---- Utility ----
        static void Lock() { SetLockState(CursorLockMode::Locked); }
        static void Unlock() { SetLockState(CursorLockMode::None); }
        static void Confine() { SetLockState(CursorLockMode::Confined); }
        static void Show() { SetVisible(true); }
        static void Hide() { SetVisible(false); }

        // ---- Legacy snake_case aliases (deprecated) ----
        [[deprecated("Use GetVisible()")]] [[nodiscard]] static bool get_visible() { return GetVisible(); }
        [[deprecated("Use SetVisible()")]] static void set_visible(bool v) { SetVisible(v); }
        [[deprecated("Use GetLockState()")]] [[nodiscard]] static CursorLockMode get_lock_state() { return GetLockState(); }
        [[deprecated("Use SetLockState()")]] static void set_lock_state(CursorLockMode m) { SetLockState(m); }
        [[deprecated("Use Lock()")]] static void lock() { Lock(); }
        [[deprecated("Use Unlock()")]] static void unlock() { Unlock(); }
        [[deprecated("Use Confine()")]] static void confine() { Confine(); }
        [[deprecated("Use Show()")]] static void show() { Show(); }
        [[deprecated("Use Hide()")]] static void hide() { Hide(); }
    };

} // namespace IL2CPP::Module::Unity
