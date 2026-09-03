#pragma once
#include "../MethodHandler.hpp"

namespace IL2CPP::Module::Unity {

    enum class CursorLockMode : int {
        None = 0,       // Cursor is free to move
        Locked = 1,     // Cursor is locked to center of screen
        Confined = 2    // Cursor is confined to game window
    };

    class Cursor {
    public:
        Cursor() = delete;

    private:
        enum Slot { GetVis = 0, SetVis, GetLock, SetLock, SlotCount };

        // Resolution is retried until it succeeds: a first call made before
        // UnityEngine.CoreModule is up would otherwise cache a null forever.
        [[nodiscard]] static Method& Resolved(Slot slot) {
            static Method cache[SlotCount];
            if (!cache[slot]) {
                const char* name = slot == GetVis  ? IL2CPP_STR("get_visible")
                                 : slot == SetVis  ? IL2CPP_STR("set_visible")
                                 : slot == GetLock ? IL2CPP_STR("get_lockState")
                                                   : IL2CPP_STR("set_lockState");
                const int argc = (slot == GetVis || slot == GetLock) ? 0 : 1;
                cache[slot] = MethodHandler::resolve(IL2CPP_STR("UnityEngine.Cursor"), name, argc);
            }
            return cache[slot];
        }

    public:
        /// <summary>Whether the cursor setters have resolved yet.</summary>
        [[nodiscard]] static bool IsAvailable() { return static_cast<bool>(Resolved(SetLock)); }

        [[nodiscard]] static bool GetVisible() {
            Method& m = Resolved(GetVis);
            return m ? MethodHandler::invoke<bool>(m, nullptr) : false;
        }

        static void SetVisible(bool visible) {
            Method& m = Resolved(SetVis);
            if (!m) return;
            void* params[] = { &visible };
            MethodHandler::invoke(m, nullptr, params);
        }

        [[nodiscard]] static CursorLockMode GetLockState() {
            Method& m = Resolved(GetLock);
            if (!m) return CursorLockMode::None;
            return static_cast<CursorLockMode>(MethodHandler::invoke<int>(m, nullptr));
        }

        static void SetLockState(CursorLockMode lockMode) {
            Method& m = Resolved(SetLock);
            if (!m) return;
            int val = static_cast<int>(lockMode);
            void* params[] = { &val };
            MethodHandler::invoke(m, nullptr, params);
        }

        static void Lock() { SetLockState(CursorLockMode::Locked); }
        static void Unlock() { SetLockState(CursorLockMode::None); }
        static void Confine() { SetLockState(CursorLockMode::Confined); }
        static void Show() { SetVisible(true); }
        static void Hide() { SetVisible(false); }
    };

} // namespace IL2CPP::Module::Unity
