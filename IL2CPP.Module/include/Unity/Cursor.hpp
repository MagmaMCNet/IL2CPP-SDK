#pragma once
#include "Object.hpp"
#include <IL2CPP.Common/il2cpp_shared.hpp>

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

        /// Get cursor visibility.
        [[nodiscard]] static bool GetVisible() {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->cursor.m_GetVisible) return true;
            return reinterpret_cast<bool(IL2CPP_CALLTYPE)()>(fn->cursor.m_GetVisible)();
        }

        /// Set cursor visibility.
        static void SetVisible(bool visible) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->cursor.m_SetVisible) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(bool)>(fn->cursor.m_SetVisible)(visible);
        }

        // ---- Lock State ----

        /// Get the cursor lock state.
        [[nodiscard]] static CursorLockMode GetLockState() {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->cursor.m_GetLockState) return CursorLockMode::None;
            return static_cast<CursorLockMode>(reinterpret_cast<int(IL2CPP_CALLTYPE)()>(fn->cursor.m_GetLockState)());
        }

        /// Set the cursor lock state.
        static void SetLockState(CursorLockMode lockMode) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->cursor.m_SetLockState) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(int)>(fn->cursor.m_SetLockState)(static_cast<int>(lockMode));
        }

        // ---- Utility ----

        /// Lock the cursor to the center of the screen.
        static void Lock() {
            SetLockState(CursorLockMode::Locked);
        }

        /// Unlock the cursor.
        static void Unlock() {
            SetLockState(CursorLockMode::None);
        }

        /// Confine the cursor to the game window.
        static void Confine() {
            SetLockState(CursorLockMode::Confined);
        }

        /// Show the cursor.
        static void Show() {
            SetVisible(true);
        }

        /// Hide the cursor.
        static void Hide() {
            SetVisible(false);
        }

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
