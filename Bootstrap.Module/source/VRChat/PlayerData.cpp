#include <VRChat/PlayerData.hpp>
#include <IL2CPP.Module/include/MethodHandler.hpp>
#include <IL2CPP.Module/include/System/String.hpp>
#include <IL2CPP.Module/include/System/Array.hpp>

namespace IL2CPP::VRChat {

    using IL2CPP::Module::MethodHandler;

    static constexpr const char* kPlayerDataClass = "VRC.SDK3.Persistence.PlayerData";

    template<typename T>
    static T PlayerData_Get(const char* method, VRCPlayerApi player, std::string_view key) {
        if (!player) return T{};
        auto m = MethodHandler::resolve(kPlayerDataClass, method, 2);
        if (!m) return T{};
        auto str = IL2CPP::Module::System::String::create(key);
        void* params[2] = { player.raw(), str.raw() };
        return MethodHandler::invoke<T>(m, nullptr, params);
    }

    template<typename T>
    static void PlayerData_Set(const char* method, std::string_view key, T value) {
        auto m = MethodHandler::resolve(kPlayerDataClass, method, 2);
        if (!m) return;
        auto str = IL2CPP::Module::System::String::create(key);
        void* params[2] = { str.raw(), &value };
        MethodHandler::invoke<void>(m, nullptr, params);
    }

    bool PlayerData::HasKey(VRCPlayerApi player, std::string_view key) {
        return PlayerData_Get<bool>("HasKey", player, key);
    }

    std::vector<std::string> PlayerData::GetKeys(VRCPlayerApi player) {
        if (!player) return {};
        auto m = MethodHandler::resolve(kPlayerDataClass, "GetKeys", 1);
        if (!m) return {};
        void* params[1] = { player.raw() };
        void* raw = MethodHandler::invoke<void*>(m, nullptr, params);
        if (!raw) return {};
        IL2CPP::Module::System::Array<void*> arr{ raw };
        std::vector<std::string> out;
        out.reserve(arr.size());
        for (void* s : arr.as_span())
            if (s) out.push_back(IL2CPP::Module::System::String(s).to_string());
        return out;
    }

    std::string PlayerData::GetTypeName(VRCPlayerApi player, std::string_view key) {
        void* type = PlayerData_Get<void*>("GetType", player, key);
        if (!type) return {};
        auto klass = IL2CPP::Module::Class::from_system_type(type);
        return klass ? klass.full_name() : std::string{};
    }

    int PlayerData::GetInt(VRCPlayerApi player, std::string_view key) { return PlayerData_Get<int>("GetInt", player, key); }
    float PlayerData::GetFloat(VRCPlayerApi player, std::string_view key) { return PlayerData_Get<float>("GetFloat", player, key); }
    bool PlayerData::GetBool(VRCPlayerApi player, std::string_view key) { return PlayerData_Get<bool>("GetBool", player, key); }
    int64_t PlayerData::GetLong(VRCPlayerApi player, std::string_view key) { return PlayerData_Get<int64_t>("GetLong", player, key); }
    double PlayerData::GetDouble(VRCPlayerApi player, std::string_view key) { return PlayerData_Get<double>("GetDouble", player, key); }
    IL2CPP::Vector3 PlayerData::GetVector3(VRCPlayerApi player, std::string_view key) { return PlayerData_Get<IL2CPP::Vector3>("GetVector3", player, key); }
    IL2CPP::Quaternion PlayerData::GetQuaternion(VRCPlayerApi player, std::string_view key) { return PlayerData_Get<IL2CPP::Quaternion>("GetQuaternion", player, key); }
    IL2CPP::Color PlayerData::GetColor(VRCPlayerApi player, std::string_view key) { return PlayerData_Get<IL2CPP::Color>("GetColor", player, key); }

    std::string PlayerData::GetString(VRCPlayerApi player, std::string_view key) {
        void* s = PlayerData_Get<void*>("GetString", player, key);
        return s ? IL2CPP::Module::System::String(s).to_string() : std::string{};
    }

    void PlayerData::SetInt(std::string_view key, int value) { PlayerData_Set("SetInt", key, value); }
    void PlayerData::SetFloat(std::string_view key, float value) { PlayerData_Set("SetFloat", key, value); }
    void PlayerData::SetBool(std::string_view key, bool value) { PlayerData_Set("SetBool", key, value); }
    void PlayerData::SetLong(std::string_view key, int64_t value) { PlayerData_Set("SetLong", key, value); }
    void PlayerData::SetDouble(std::string_view key, double value) { PlayerData_Set("SetDouble", key, value); }
    void PlayerData::SetVector3(std::string_view key, IL2CPP::Vector3 value) { PlayerData_Set("SetVector3", key, value); }
    void PlayerData::SetQuaternion(std::string_view key, IL2CPP::Quaternion value) { PlayerData_Set("SetQuaternion", key, value); }
    void PlayerData::SetColor(std::string_view key, IL2CPP::Color value) { PlayerData_Set("SetColor", key, value); }

    void PlayerData::SetString(std::string_view key, std::string_view value) {
        auto m = MethodHandler::resolve(kPlayerDataClass, "SetString", 2);
        if (!m) return;
        auto k = IL2CPP::Module::System::String::create(key);
        auto v = IL2CPP::Module::System::String::create(value);
        void* params[2] = { k.raw(), v.raw() };
        MethodHandler::invoke<void>(m, nullptr, params);
    }

} // namespace IL2CPP::VRChat
