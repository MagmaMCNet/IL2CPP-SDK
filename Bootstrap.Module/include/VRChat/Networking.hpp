#pragma once

#include "VRCPlayerApi.hpp"
#include <IL2CPP.Module/include/il2cpp_module.hpp>
#include <IL2CPP.Module/include/ManagedObject.hpp>
#include <cstdint>
#include <string_view>

namespace IL2CPP::VRChat {

    class Networking {
    public:
        // Network State
        [[nodiscard]] static bool IsNetworkSettled();
        [[nodiscard]] static bool IsMaster();
        [[nodiscard]] static bool IsClogged();
        [[nodiscard]] static bool IsInstanceOwner();

        // Player Queries
        [[nodiscard]] static VRCPlayerApi GetLocalPlayer();
        [[nodiscard]] static VRCPlayerApi GetMaster();
        [[nodiscard]] static VRCPlayerApi GetInstanceOwnerPlayer();

        // Time
        [[nodiscard]] static double GetServerTimeInSeconds();
        [[nodiscard]] static int GetServerTimeInMilliseconds();
        [[nodiscard]] static double CalculateServerDeltaTime(double timeInSeconds, double previousTimeInSeconds);
        [[nodiscard]] static int64_t GetNetworkDateTime();

        // Room
        static bool GoToRoom(const std::string& roomID);

        // RPC
        static void RPC(RpcDestination targetClients, IL2CPP::Module::Unity::GameObject targetObject,
                        std::string_view methodName, void* parameters = nullptr);
        static void RPC(VRCPlayerApi targetPlayer, IL2CPP::Module::Unity::GameObject targetObject,
                        std::string_view methodName, void* parameters = nullptr);

        // Event Dispatcher
        [[nodiscard]] static IL2CPP::Module::ManagedObject GetEventDispatcher();

        // Ownership
        [[nodiscard]] static bool IsOwner(VRCPlayerApi player, IL2CPP::Module::Unity::GameObject obj);
        [[nodiscard]] static bool IsOwner(IL2CPP::Module::Unity::GameObject obj);
        [[nodiscard]] static VRCPlayerApi GetOwner(IL2CPP::Module::Unity::GameObject obj);
        static void SetOwner(VRCPlayerApi player, IL2CPP::Module::Unity::GameObject obj);

        // Object Queries
        [[nodiscard]] static bool IsObjectReady(IL2CPP::Module::Unity::GameObject obj);
        [[nodiscard]] static std::string GetUniqueName(IL2CPP::Module::Unity::GameObject obj);
        [[nodiscard]] static float SimulationTime(IL2CPP::Module::Unity::GameObject target);
        [[nodiscard]] static float SimulationTime(VRCPlayerApi target);
        static void Destroy(IL2CPP::Module::Unity::GameObject obj);

        // Storage
        static void RequestStorageUsageUpdate();
        [[nodiscard]] static int GetPlayerDataStorageLimit();
        [[nodiscard]] static int GetPlayerObjectStorageLimit();
        [[nodiscard]] static int GetPlayerDataStorageUsage(VRCPlayerApi target);
        [[nodiscard]] static int GetPlayerObjectStorageUsage(VRCPlayerApi target);

    private:
        static IL2CPP::Module::Class klass();
    };

} // namespace IL2CPP::VRChat
