#pragma once
#include "Object.hpp"
#include <IL2CPP.Common/il2cpp_shared.hpp>

// ============================================================================
//  IL2CPP.Module::Unity::Time - Static utility class
// ============================================================================

namespace IL2CPP::Module::Unity {

    class Time {
    public:
        Time() = delete;

        [[nodiscard]] static float GetTime() {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->time.m_GetTime) return 0.f;
            return reinterpret_cast<float(IL2CPP_CALLTYPE)()>(fn->time.m_GetTime)();
        }
        [[nodiscard]] static double GetTimeAsDouble() {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->time.m_GetTimeAsDouble) return 0.0;
            return reinterpret_cast<double(IL2CPP_CALLTYPE)()>(fn->time.m_GetTimeAsDouble)();
        }
        [[nodiscard]] static float GetDeltaTime() {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->time.m_GetDeltaTime) return 0.f;
            return reinterpret_cast<float(IL2CPP_CALLTYPE)()>(fn->time.m_GetDeltaTime)();
        }
        [[nodiscard]] static float GetFixedDeltaTime() {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->time.m_GetFixedDeltaTime) return 0.f;
            return reinterpret_cast<float(IL2CPP_CALLTYPE)()>(fn->time.m_GetFixedDeltaTime)();
        }
        [[nodiscard]] static float GetUnscaledDeltaTime() {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->time.m_GetUnscaledDeltaTime) return 0.f;
            return reinterpret_cast<float(IL2CPP_CALLTYPE)()>(fn->time.m_GetUnscaledDeltaTime)();
        }
        [[nodiscard]] static float GetUnscaledTime() {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->time.m_GetUnscaledTime) return 0.f;
            return reinterpret_cast<float(IL2CPP_CALLTYPE)()>(fn->time.m_GetUnscaledTime)();
        }
        [[nodiscard]] static float GetFixedTime() {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->time.m_GetFixedTime) return 0.f;
            return reinterpret_cast<float(IL2CPP_CALLTYPE)()>(fn->time.m_GetFixedTime)();
        }
        [[nodiscard]] static float GetTimeScale() {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->time.m_GetTimeScale) return 1.f;
            return reinterpret_cast<float(IL2CPP_CALLTYPE)()>(fn->time.m_GetTimeScale)();
        }
        static void SetTimeScale(float scale) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->time.m_SetTimeScale) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(float)>(fn->time.m_SetTimeScale)(scale);
        }
        [[nodiscard]] static int GetFrameCount() {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->time.m_GetFrameCount) return 0;
            return reinterpret_cast<int(IL2CPP_CALLTYPE)()>(fn->time.m_GetFrameCount)();
        }
        [[nodiscard]] static float GetRealtimeSinceStartup() {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->time.m_GetRealtimeSinceStartup) return 0.f;
            return reinterpret_cast<float(IL2CPP_CALLTYPE)()>(fn->time.m_GetRealtimeSinceStartup)();
        }
        [[nodiscard]] static double GetRealtimeSinceStartupAsDouble() {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->time.m_GetRealtimeSinceStartupAsDouble) return 0.0;
            return reinterpret_cast<double(IL2CPP_CALLTYPE)()>(fn->time.m_GetRealtimeSinceStartupAsDouble)();
        }
        [[nodiscard]] static float GetSmoothDeltaTime() {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->time.m_GetSmoothDeltaTime) return 0.f;
            return reinterpret_cast<float(IL2CPP_CALLTYPE)()>(fn->time.m_GetSmoothDeltaTime)();
        }
        [[nodiscard]] static float GetMaximumDeltaTime() {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->time.m_GetMaximumDeltaTime) return 0.f;
            return reinterpret_cast<float(IL2CPP_CALLTYPE)()>(fn->time.m_GetMaximumDeltaTime)();
        }

        // ---- Time Since Level Load ----
        [[nodiscard]] static float GetTimeSinceLevelLoad() {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->time.m_GetTimeSinceLevelLoad) return 0.f;
            return reinterpret_cast<float(IL2CPP_CALLTYPE)()>(fn->time.m_GetTimeSinceLevelLoad)();
        }
        [[nodiscard]] static double GetTimeSinceLevelLoadAsDouble() {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->time.m_GetTimeSinceLevelLoadAsDouble) return 0.0;
            return reinterpret_cast<double(IL2CPP_CALLTYPE)()>(fn->time.m_GetTimeSinceLevelLoadAsDouble)();
        }

        // ---- Fixed Time Variants ----
        [[nodiscard]] static double GetFixedTimeAsDouble() {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->time.m_GetFixedTimeAsDouble) return 0.0;
            return reinterpret_cast<double(IL2CPP_CALLTYPE)()>(fn->time.m_GetFixedTimeAsDouble)();
        }

        // ---- Unscaled Time Variants ----
        [[nodiscard]] static double GetUnscaledTimeAsDouble() {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->time.m_GetUnscaledTimeAsDouble) return 0.0;
            return reinterpret_cast<double(IL2CPP_CALLTYPE)()>(fn->time.m_GetUnscaledTimeAsDouble)();
        }

        [[nodiscard]] static float GetFixedUnscaledTime() {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->time.m_GetFixedUnscaledTime) return 0.f;
            return reinterpret_cast<float(IL2CPP_CALLTYPE)()>(fn->time.m_GetFixedUnscaledTime)();
        }
        [[nodiscard]] static double GetFixedUnscaledTimeAsDouble() {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->time.m_GetFixedUnscaledTimeAsDouble) return 0.0;
            return reinterpret_cast<double(IL2CPP_CALLTYPE)()>(fn->time.m_GetFixedUnscaledTimeAsDouble)();
        }

        [[nodiscard]] static float GetFixedUnscaledDeltaTime() {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->time.m_GetFixedUnscaledDeltaTime) return 0.f;
            return reinterpret_cast<float(IL2CPP_CALLTYPE)()>(fn->time.m_GetFixedUnscaledDeltaTime)();
        }

        // ---- Frame Counts ----
        [[nodiscard]] static int GetRenderedFrameCount() {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->time.m_GetRenderedFrameCount) return 0;
            return reinterpret_cast<int(IL2CPP_CALLTYPE)()>(fn->time.m_GetRenderedFrameCount)();
        }

        // ---- Capture ----
        [[nodiscard]] static float GetCaptureDeltaTime() {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->time.m_GetCaptureDeltaTime) return 0.f;
            return reinterpret_cast<float(IL2CPP_CALLTYPE)()>(fn->time.m_GetCaptureDeltaTime)();
        }
        [[nodiscard]] static int GetCaptureFramerate() {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->time.m_GetCaptureFramerate) return 0;
            return reinterpret_cast<int(IL2CPP_CALLTYPE)()>(fn->time.m_GetCaptureFramerate)();
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
