#include <include/VRChat/Networking.hpp>

namespace IL2CPP::VRChat {

    IL2CPP::Module::Class Networking::klass() {
        static auto c = IL2CPP::Module::Class::find("VRC.SDKBase.Networking");
        return c;
    }

    bool Networking::IsNetworkSettled() {
        auto k = klass();
        if (!k) return false;
        auto f = k.get_field("IsNetworkSettled");
        if (!f) return false;
        bool val = false;
        f.get_static_value(&val);
        return val;
    }

    bool Networking::IsMaster() {
        auto k = klass();
        if (!k) return false;
        auto f = k.get_field("IsMaster");
        if (!f) return false;
        bool val = false;
        f.get_static_value(&val);
        return val;
    }

    bool Networking::IsClogged() {
        auto k = klass();
        if (!k) return false;
        auto f = k.get_field("IsClogged");
        if (!f) return false;
        bool val = false;
        f.get_static_value(&val);
        return val;
    }

    bool Networking::IsInstanceOwner() {
        auto k = klass();
        if (!k) return false;
        auto f = k.get_field("IsInstanceOwner");
        if (!f) return false;
        bool val = false;
        f.get_static_value(&val);
        return val;
    }

    VRCPlayerApi Networking::GetLocalPlayer() {
        auto k = klass();
        if (!k) return {};
        auto f = k.get_field("LocalPlayer");
        if (!f) return {};
        void* val = nullptr;
        f.get_static_value(&val);
        return VRCPlayerApi(val);
    }

    VRCPlayerApi Networking::GetMaster() {
        auto k = klass();
        if (!k) return {};
        auto f = k.get_field("Master");
        if (!f) return {};
        void* val = nullptr;
        f.get_static_value(&val);
        return VRCPlayerApi(val);
    }

    double Networking::GetServerTimeInSeconds() {
        auto k = klass();
        if (!k) return 0.0;
        auto m = k.get_method("GetServerTimeInSeconds", 0);
        if (!m) return 0.0;
        void* result = m.invoke(nullptr, nullptr);
        return result ? *reinterpret_cast<double*>(IL2CPP::Unbox(result)) : 0.0;
    }

    int Networking::GetServerTimeInMilliseconds() {
        auto k = klass();
        if (!k) return 0;
        auto m = k.get_method("GetServerTimeInMilliseconds", 0);
        if (!m) return 0;
        void* result = m.invoke(nullptr, nullptr);
        return result ? *reinterpret_cast<int*>(IL2CPP::Unbox(result)) : 0;
    }

    bool Networking::IsOwner(VRCPlayerApi player, IL2CPP::Module::Unity::GameObject obj) {
        auto k = klass();
        if (!k) return false;
        auto m = k.get_method("IsOwner", 2);
        if (!m) return false;
        void* params[2] = { player.raw(), obj.raw() };
        void* result = m.invoke(nullptr, params);
        return result ? *reinterpret_cast<bool*>(IL2CPP::Unbox(result)) : false;
    }

    bool Networking::IsOwner(IL2CPP::Module::Unity::GameObject obj) {
        auto k = klass();
        if (!k) return false;
        auto m = k.get_method("IsOwner", 1);
        if (!m) return false;
        void* params[1] = { obj.raw() };
        void* result = m.invoke(nullptr, params);
        return result ? *reinterpret_cast<bool*>(IL2CPP::Unbox(result)) : false;
    }

    VRCPlayerApi Networking::GetOwner(IL2CPP::Module::Unity::GameObject obj) {
        auto k = klass();
        if (!k) return {};
        auto m = k.get_method("GetOwner", 1);
        if (!m) return {};
        void* params[1] = { obj.raw() };
        void* result = m.invoke(nullptr, params);
        return result ? VRCPlayerApi(result) : VRCPlayerApi();
    }

    void Networking::SetOwner(VRCPlayerApi player, IL2CPP::Module::Unity::GameObject obj) {
        auto k = klass();
        if (!k) return;
        auto m = k.get_method("SetOwner", 2);
        if (!m) return;
        void* params[2] = { player.raw(), obj.raw() };
        m.invoke(nullptr, params);
    }

} // namespace IL2CPP::VRChat
