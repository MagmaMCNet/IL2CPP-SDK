#pragma once
#include "Object.hpp"
#include <IL2CPP.Common/il2cpp_types.hpp>
#include <IL2CPP.Common/il2cpp_shared.hpp>
#include <string>

// ============================================================================
//  IL2CPP.Module::Unity::Input - Static utility class
// ============================================================================

namespace IL2CPP::Module::Unity {

    class Input {
    public:
        Input() = delete;

        [[nodiscard]] static float GetAxis(std::string_view axisName) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->input.m_GetAxis) return 0.f;
            auto* exports = GetExports();
            if (!exports || !exports->m_stringNew) return 0.f;
            void* str = reinterpret_cast<void*(IL2CPP_CALLTYPE)(const char*)>(exports->m_stringNew)(
                std::string(axisName).c_str());
            return reinterpret_cast<float(IL2CPP_CALLTYPE)(void*)>(fn->input.m_GetAxis)(str);
        }

        [[nodiscard]] static float GetAxisRaw(std::string_view axisName) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->input.m_GetAxisRaw) return 0.f;
            auto* exports = GetExports();
            if (!exports || !exports->m_stringNew) return 0.f;
            void* str = reinterpret_cast<void*(IL2CPP_CALLTYPE)(const char*)>(exports->m_stringNew)(
                std::string(axisName).c_str());
            return reinterpret_cast<float(IL2CPP_CALLTYPE)(void*)>(fn->input.m_GetAxisRaw)(str);
        }

        [[nodiscard]] static bool GetKey(KeyCode key) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->input.m_GetKey) return false;
            return reinterpret_cast<bool(IL2CPP_CALLTYPE)(int)>(fn->input.m_GetKey)(static_cast<int>(key));
        }

        [[nodiscard]] static bool GetKeyDown(KeyCode key) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->input.m_GetKeyDown) return false;
            return reinterpret_cast<bool(IL2CPP_CALLTYPE)(int)>(fn->input.m_GetKeyDown)(static_cast<int>(key));
        }

        [[nodiscard]] static bool GetKeyUp(KeyCode key) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->input.m_GetKeyUp) return false;
            return reinterpret_cast<bool(IL2CPP_CALLTYPE)(int)>(fn->input.m_GetKeyUp)(static_cast<int>(key));
        }

        [[nodiscard]] static bool GetMouseButton(int button) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->input.m_GetMouseButton) return false;
            return reinterpret_cast<bool(IL2CPP_CALLTYPE)(int)>(fn->input.m_GetMouseButton)(button);
        }

        [[nodiscard]] static bool GetMouseButtonDown(int button) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->input.m_GetMouseButtonDown) return false;
            return reinterpret_cast<bool(IL2CPP_CALLTYPE)(int)>(fn->input.m_GetMouseButtonDown)(button);
        }

        [[nodiscard]] static bool GetMouseButtonUp(int button) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->input.m_GetMouseButtonUp) return false;
            return reinterpret_cast<bool(IL2CPP_CALLTYPE)(int)>(fn->input.m_GetMouseButtonUp)(button);
        }

        [[nodiscard]] static bool GetAnyKey() {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->input.m_GetAnyKey) return false;
            return reinterpret_cast<bool(IL2CPP_CALLTYPE)()>(fn->input.m_GetAnyKey)();
        }

        [[nodiscard]] static bool GetAnyKeyDown() {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->input.m_GetAnyKeyDown) return false;
            return reinterpret_cast<bool(IL2CPP_CALLTYPE)()>(fn->input.m_GetAnyKeyDown)();
        }

        [[nodiscard]] static Vector3 GetMousePosition() {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->input.m_GetMousePosition) return Vector3{};
            Vector3 v;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(Vector3*)>(fn->input.m_GetMousePosition)(&v);
            return v;
        }

        [[nodiscard]] static Vector2 GetMouseScrollDelta() {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->input.m_GetMouseScrollDelta) return Vector2{};
            Vector2 v;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(Vector2*)>(fn->input.m_GetMouseScrollDelta)(&v);
            return v;
        }

        [[nodiscard]] static bool GetMousePresent() {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->input.m_GetMousePresent) return false;
            return reinterpret_cast<bool(IL2CPP_CALLTYPE)()>(fn->input.m_GetMousePresent)();
        }

        // ---- Button Input (by name) ----
        [[nodiscard]] static bool GetButton(std::string_view buttonName) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->input.m_GetButton) return false;
            auto* exports = GetExports();
            if (!exports || !exports->m_stringNew) return false;
            void* str = reinterpret_cast<void*(IL2CPP_CALLTYPE)(const char*)>(exports->m_stringNew)(
                std::string(buttonName).c_str());
            return reinterpret_cast<bool(IL2CPP_CALLTYPE)(void*)>(fn->input.m_GetButton)(str);
        }

        [[nodiscard]] static bool GetButtonDown(std::string_view buttonName) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->input.m_GetButtonDown) return false;
            auto* exports = GetExports();
            if (!exports || !exports->m_stringNew) return false;
            void* str = reinterpret_cast<void*(IL2CPP_CALLTYPE)(const char*)>(exports->m_stringNew)(
                std::string(buttonName).c_str());
            return reinterpret_cast<bool(IL2CPP_CALLTYPE)(void*)>(fn->input.m_GetButtonDown)(str);
        }

        [[nodiscard]] static bool GetButtonUp(std::string_view buttonName) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->input.m_GetButtonUp) return false;
            auto* exports = GetExports();
            if (!exports || !exports->m_stringNew) return false;
            void* str = reinterpret_cast<void*(IL2CPP_CALLTYPE)(const char*)>(exports->m_stringNew)(
                std::string(buttonName).c_str());
            return reinterpret_cast<bool(IL2CPP_CALLTYPE)(void*)>(fn->input.m_GetButtonUp)(str);
        }

        // ---- Touch Input ----
        [[nodiscard]] static int GetTouchCount() {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->input.m_GetTouchCount) return 0;
            return reinterpret_cast<int(IL2CPP_CALLTYPE)()>(fn->input.m_GetTouchCount)();
        }

        [[nodiscard]] static bool IsTouchSupported() {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->input.m_GetTouchPresent) return false;
            return reinterpret_cast<bool(IL2CPP_CALLTYPE)()>(fn->input.m_GetTouchPresent)();
        }

        // ---- Acceleration (mobile devices) ----
        [[nodiscard]] static Vector3 GetAcceleration() {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->input.m_GetAcceleration) return Vector3{};
            Vector3 v;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(Vector3*)>(fn->input.m_GetAcceleration)(&v);
            return v;
        }

        // ---- Legacy snake_case aliases (deprecated) ----
        [[deprecated("Use GetAxis()")]] [[nodiscard]] static float get_axis(std::string_view a) { return GetAxis(a); }
        [[deprecated("Use GetAxisRaw()")]] [[nodiscard]] static float get_axis_raw(std::string_view a) { return GetAxisRaw(a); }
        [[deprecated("Use GetKey()")]] [[nodiscard]] static bool get_key(KeyCode k) { return GetKey(k); }
        [[deprecated("Use GetKeyDown()")]] [[nodiscard]] static bool get_key_down(KeyCode k) { return GetKeyDown(k); }
        [[deprecated("Use GetKeyUp()")]] [[nodiscard]] static bool get_key_up(KeyCode k) { return GetKeyUp(k); }
        [[deprecated("Use GetMouseButton()")]] [[nodiscard]] static bool get_mouse_button(int b) { return GetMouseButton(b); }
        [[deprecated("Use GetMouseButtonDown()")]] [[nodiscard]] static bool get_mouse_button_down(int b) { return GetMouseButtonDown(b); }
        [[deprecated("Use GetMouseButtonUp()")]] [[nodiscard]] static bool get_mouse_button_up(int b) { return GetMouseButtonUp(b); }
        [[deprecated("Use GetAnyKey()")]] [[nodiscard]] static bool get_any_key() { return GetAnyKey(); }
        [[deprecated("Use GetAnyKeyDown()")]] [[nodiscard]] static bool get_any_key_down() { return GetAnyKeyDown(); }
        [[deprecated("Use GetMousePosition()")]] [[nodiscard]] static Vector3 get_mouse_position() { return GetMousePosition(); }
        [[deprecated("Use GetMouseScrollDelta()")]] [[nodiscard]] static Vector2 get_mouse_scroll_delta() { return GetMouseScrollDelta(); }
        [[deprecated("Use GetMousePresent()")]] [[nodiscard]] static bool get_mouse_present() { return GetMousePresent(); }
        [[deprecated("Use GetButton()")]] [[nodiscard]] static bool get_button(std::string_view b) { return GetButton(b); }
        [[deprecated("Use GetButtonDown()")]] [[nodiscard]] static bool get_button_down(std::string_view b) { return GetButtonDown(b); }
        [[deprecated("Use GetButtonUp()")]] [[nodiscard]] static bool get_button_up(std::string_view b) { return GetButtonUp(b); }
        [[deprecated("Use GetTouchCount()")]] [[nodiscard]] static int get_touch_count() { return GetTouchCount(); }
        [[deprecated("Use IsTouchSupported()")]] [[nodiscard]] static bool is_touch_supported() { return IsTouchSupported(); }
        [[deprecated("Use GetAcceleration()")]] [[nodiscard]] static Vector3 get_acceleration() { return GetAcceleration(); }
    };

} // namespace IL2CPP::Module::Unity
