#pragma once
#include "../MethodHandler.hpp"

// ============================================================================
//  IL2CPP.Module::Unity::Time - Static utility class
// ============================================================================

namespace IL2CPP::Module::Unity {

    class Time {
    public:
        Time() = delete;

        [[nodiscard]] static float GetTime() {
            static auto m = MethodHandler::resolve("UnityEngine.Time", "get_time", 0);
            return MethodHandler::invoke<float>(m, nullptr);
        }
        [[nodiscard]] static double GetTimeAsDouble() {
            static auto m = MethodHandler::resolve("UnityEngine.Time", "get_timeAsDouble", 0);
            return MethodHandler::invoke<double>(m, nullptr);
        }
        [[nodiscard]] static float GetDeltaTime() {
            static auto m = MethodHandler::resolve("UnityEngine.Time", "get_deltaTime", 0);
            return MethodHandler::invoke<float>(m, nullptr);
        }
        [[nodiscard]] static float GetFixedDeltaTime() {
            static auto m = MethodHandler::resolve("UnityEngine.Time", "get_fixedDeltaTime", 0);
            return MethodHandler::invoke<float>(m, nullptr);
        }
        [[nodiscard]] static float GetUnscaledDeltaTime() {
            static auto m = MethodHandler::resolve("UnityEngine.Time", "get_unscaledDeltaTime", 0);
            return MethodHandler::invoke<float>(m, nullptr);
        }
        [[nodiscard]] static float GetUnscaledTime() {
            static auto m = MethodHandler::resolve("UnityEngine.Time", "get_unscaledTime", 0);
            return MethodHandler::invoke<float>(m, nullptr);
        }
        [[nodiscard]] static float GetFixedTime() {
            static auto m = MethodHandler::resolve("UnityEngine.Time", "get_fixedTime", 0);
            return MethodHandler::invoke<float>(m, nullptr);
        }
        [[nodiscard]] static float GetTimeScale() {
            static auto m = MethodHandler::resolve("UnityEngine.Time", "get_timeScale", 0);
            return MethodHandler::invoke<float>(m, nullptr);
        }
        static void SetTimeScale(float scale) {
            static auto m = MethodHandler::resolve("UnityEngine.Time", "set_timeScale", 1);
            void* params[] = { &scale };
            MethodHandler::invoke(m, nullptr, params);
        }
        [[nodiscard]] static int GetFrameCount() {
            static auto m = MethodHandler::resolve("UnityEngine.Time", "get_frameCount", 0);
            return MethodHandler::invoke<int>(m, nullptr);
        }
        [[nodiscard]] static float GetRealtimeSinceStartup() {
            static auto m = MethodHandler::resolve("UnityEngine.Time", "get_realtimeSinceStartup", 0);
            return MethodHandler::invoke<float>(m, nullptr);
        }
        [[nodiscard]] static double GetRealtimeSinceStartupAsDouble() {
            static auto m = MethodHandler::resolve("UnityEngine.Time", "get_realtimeSinceStartupAsDouble", 0);
            return MethodHandler::invoke<double>(m, nullptr);
        }
        [[nodiscard]] static float GetSmoothDeltaTime() {
            static auto m = MethodHandler::resolve("UnityEngine.Time", "get_smoothDeltaTime", 0);
            return MethodHandler::invoke<float>(m, nullptr);
        }
        [[nodiscard]] static float GetMaximumDeltaTime() {
            static auto m = MethodHandler::resolve("UnityEngine.Time", "get_maximumDeltaTime", 0);
            return MethodHandler::invoke<float>(m, nullptr);
        }
        [[nodiscard]] static float GetTimeSinceLevelLoad() {
            static auto m = MethodHandler::resolve("UnityEngine.Time", "get_timeSinceLevelLoad", 0);
            return MethodHandler::invoke<float>(m, nullptr);
        }
        [[nodiscard]] static double GetTimeSinceLevelLoadAsDouble() {
            static auto m = MethodHandler::resolve("UnityEngine.Time", "get_timeSinceLevelLoadAsDouble", 0);
            return MethodHandler::invoke<double>(m, nullptr);
        }
        [[nodiscard]] static double GetFixedTimeAsDouble() {
            static auto m = MethodHandler::resolve("UnityEngine.Time", "get_fixedTimeAsDouble", 0);
            return MethodHandler::invoke<double>(m, nullptr);
        }
        [[nodiscard]] static double GetUnscaledTimeAsDouble() {
            static auto m = MethodHandler::resolve("UnityEngine.Time", "get_unscaledTimeAsDouble", 0);
            return MethodHandler::invoke<double>(m, nullptr);
        }
        [[nodiscard]] static float GetFixedUnscaledTime() {
            static auto m = MethodHandler::resolve("UnityEngine.Time", "get_fixedUnscaledTime", 0);
            return MethodHandler::invoke<float>(m, nullptr);
        }
        [[nodiscard]] static double GetFixedUnscaledTimeAsDouble() {
            static auto m = MethodHandler::resolve("UnityEngine.Time", "get_fixedUnscaledTimeAsDouble", 0);
            return MethodHandler::invoke<double>(m, nullptr);
        }
        [[nodiscard]] static float GetFixedUnscaledDeltaTime() {
            static auto m = MethodHandler::resolve("UnityEngine.Time", "get_fixedUnscaledDeltaTime", 0);
            return MethodHandler::invoke<float>(m, nullptr);
        }
        [[nodiscard]] static int GetRenderedFrameCount() {
            static auto m = MethodHandler::resolve("UnityEngine.Time", "get_renderedFrameCount", 0);
            return MethodHandler::invoke<int>(m, nullptr);
        }
        [[nodiscard]] static float GetCaptureDeltaTime() {
            static auto m = MethodHandler::resolve("UnityEngine.Time", "get_captureDeltaTime", 0);
            return MethodHandler::invoke<float>(m, nullptr);
        }
        [[nodiscard]] static int GetCaptureFramerate() {
            static auto m = MethodHandler::resolve("UnityEngine.Time", "get_captureFramerate", 0);
            return MethodHandler::invoke<int>(m, nullptr);
        }

        // ---- Legacy snake_case aliases (deprecated) ----
        [[deprecated("Use GetTime()")]] [[nodiscard]] static float get_time() { return GetTime(); }
        [[deprecated("Use GetTimeAsDouble()")]] [[nodiscard]] static double get_time_as_double() { return GetTimeAsDouble(); }
        [[deprecated("Use GetDeltaTime()")]] [[nodiscard]] static float get_delta_time() { return GetDeltaTime(); }
        [[deprecated("Use GetFixedDeltaTime()")]] [[nodiscard]] static float get_fixed_delta_time() { return GetFixedDeltaTime(); }
        [[deprecated("Use GetUnscaledDeltaTime()")]] [[nodiscard]] static float get_unscaled_delta_time() { return GetUnscaledDeltaTime(); }
        [[deprecated("Use GetUnscaledTime()")]] [[nodiscard]] static float get_unscaled_time() { return GetUnscaledTime(); }
        [[deprecated("Use GetFixedTime()")]] [[nodiscard]] static float get_fixed_time() { return GetFixedTime(); }
        [[deprecated("Use GetTimeScale()")]] [[nodiscard]] static float get_time_scale() { return GetTimeScale(); }
        [[deprecated("Use SetTimeScale()")]] static void set_time_scale(float s) { SetTimeScale(s); }
        [[deprecated("Use GetFrameCount()")]] [[nodiscard]] static int get_frame_count() { return GetFrameCount(); }
        [[deprecated("Use GetRealtimeSinceStartup()")]] [[nodiscard]] static float get_realtime_since_startup() { return GetRealtimeSinceStartup(); }
    };

} // namespace IL2CPP::Module::Unity
