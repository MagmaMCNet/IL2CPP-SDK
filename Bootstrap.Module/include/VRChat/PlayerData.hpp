#pragma once

#include "VRCPlayerApi.hpp"
#include <IL2CPP.Module/include/il2cpp_module.hpp>
#include <IL2CPP.Common/il2cpp_shared.hpp>
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

namespace IL2CPP::VRChat {

    class PlayerData {
    public:
        [[nodiscard]] static bool HasKey(VRCPlayerApi player, std::string_view key);
        [[nodiscard]] static std::vector<std::string> GetKeys(VRCPlayerApi player);
        [[nodiscard]] static std::string GetTypeName(VRCPlayerApi player, std::string_view key);

        [[nodiscard]] static int GetInt(VRCPlayerApi player, std::string_view key);
        [[nodiscard]] static float GetFloat(VRCPlayerApi player, std::string_view key);
        [[nodiscard]] static std::string GetString(VRCPlayerApi player, std::string_view key);
        [[nodiscard]] static bool GetBool(VRCPlayerApi player, std::string_view key);
        [[nodiscard]] static int64_t GetLong(VRCPlayerApi player, std::string_view key);
        [[nodiscard]] static double GetDouble(VRCPlayerApi player, std::string_view key);
        [[nodiscard]] static IL2CPP::Vector3 GetVector3(VRCPlayerApi player, std::string_view key);
        [[nodiscard]] static IL2CPP::Quaternion GetQuaternion(VRCPlayerApi player, std::string_view key);
        [[nodiscard]] static IL2CPP::Color GetColor(VRCPlayerApi player, std::string_view key);

        static void SetInt(std::string_view key, int value);
        static void SetFloat(std::string_view key, float value);
        static void SetString(std::string_view key, std::string_view value);
        static void SetBool(std::string_view key, bool value);
        static void SetLong(std::string_view key, int64_t value);
        static void SetDouble(std::string_view key, double value);
        static void SetVector3(std::string_view key, IL2CPP::Vector3 value);
        static void SetQuaternion(std::string_view key, IL2CPP::Quaternion value);
        static void SetColor(std::string_view key, IL2CPP::Color value);
    };

} // namespace IL2CPP::VRChat
