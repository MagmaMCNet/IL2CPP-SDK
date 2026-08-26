#pragma once

#include "VRC_Interactable.hpp"
#include "Enums.hpp"
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

namespace IL2CPP::VRChat {

    struct UdonSymbol {
        std::string name;
        uint32_t    address = 0;
        std::string typeName;
    };

    enum class UdonValueKind : uint8_t {
        Unknown,
        Null,
        Bool,
        Integer,
        Unsigned,
        Float,
        String,
        Object,
    };

    struct UdonVariable {
        std::string   symbol;
        uint32_t      address = 0;
        std::string   typeName;
        std::string   display;
        UdonValueKind kind = UdonValueKind::Unknown;
        int64_t       integer = 0;
        double        number = 0.0;
        void*         boxed = nullptr;
        bool          initialized = false;
    };

    struct UdonCachedExtern {
        uint32_t    address = 0;
        std::string signature;
        void*       delegateObject = nullptr;
        void*       methodPointer = nullptr;
        int32_t     parameterCount = 0;
    };

    class UdonBehaviour : public VRC_Interactable {
    public:
        using VRC_Interactable::VRC_Interactable;

        [[nodiscard]] bool GetSynchronizePosition();
        [[nodiscard]] bool GetSynchronizeAnimation();
        [[nodiscard]] bool GetReliable();
        [[nodiscard]] SyncType GetSyncMethod();
        [[nodiscard]] bool GetIsReady();
        [[nodiscard]] bool GetHasError();
        [[nodiscard]] bool GetInitialized();

        void SendCustomEvent(std::string_view eventName);
        void SendCustomNetworkEvent(NetworkEventTarget target, std::string_view eventName);
        void RequestSerialization();
        void SendCustomEventDelayedSeconds(std::string_view eventName, float delaySeconds, EventTiming eventTiming = EventTiming::Update);
        void SendCustomEventDelayedFrames(std::string_view eventName, int delayFrames, EventTiming eventTiming = EventTiming::Update);

        [[nodiscard]] std::string GetInteractionText();
        void SetInteractionText(std::string_view text);

        void SetProgramVariable(std::string_view symbolName, void* value);
        [[nodiscard]] void* GetProgramVariable(std::string_view symbolName);
        [[nodiscard]] bool TryGetVariableValue(std::string_view symbolName, void** value);
        [[nodiscard]] bool TrySetVariableValue(std::string_view symbolName, void* value);

        /// <summary>Get the IUdonProgram this behaviour runs, or null when no program is loaded.</summary>
        [[nodiscard]] void* GetProgram() const;

        /// <summary>Get the live IUdonHeap, preferring the VM's heap over the program's.</summary>
        [[nodiscard]] void* GetHeap() const;

        /// <summary>Get the program's instruction set identifier, e.g. "UdonVM".</summary>
        [[nodiscard]] std::string GetInstructionSetIdentifier() const;

        /// <summary>List every entry point the program declares, including internal ones.</summary>
        [[nodiscard]] std::vector<std::string> GetEventNames() const;

        /// <summary>List the entry points that are exported, i.e. callable over the network.</summary>
        [[nodiscard]] std::vector<std::string> GetNetworkedEventNames() const;

        /// <summary>Whether the program declares an entry point with this name.</summary>
        [[nodiscard]] bool HasEvent(std::string_view eventName) const;

        /// <summary>List every entry point with the code address its event starts at.</summary>
        [[nodiscard]] std::vector<UdonSymbol> GetEntryPoints() const;

        /// <summary>List every program symbol with its heap address and declared type.</summary>
        [[nodiscard]] std::vector<UdonSymbol> GetSymbols() const;

        /// <summary>List the exported symbols, i.e. the program's public variables.</summary>
        [[nodiscard]] std::vector<std::string> GetPublicVariableNames() const;

        /// <summary>Resolve a symbol name to its heap address.</summary>
        /// <returns>False when the program has no symbol with that name.</returns>
        [[nodiscard]] bool TryGetSymbolAddress(std::string_view symbolName, uint32_t& address) const;

        /// <summary>Get the number of addressable heap slots.</summary>
        [[nodiscard]] uint32_t GetHeapCapacity() const;

        /// <summary>Read one heap slot by address, decoding the stored value to a primitive where possible.</summary>
        [[nodiscard]] UdonVariable ReadHeap(uint32_t address) const;

        /// <summary>Read the heap slot a symbol points at.</summary>
        [[nodiscard]] UdonVariable ReadVariable(std::string_view symbolName) const;

        /// <summary>Read the whole heap into a flat list, one entry per slot, decoded.</summary>
        /// <param name="namedOnly">Only return slots the symbol table has a name for.</param>
        [[nodiscard]] std::vector<UdonVariable> DumpHeap(bool namedOnly = false) const;

        /// <summary>List every heap slot holding an already-resolved extern delegate.</summary>
        [[nodiscard]] std::vector<UdonCachedExtern> GetCachedExterns() const;

        /// <summary>Write a boxed value into a heap slot, keeping the slot's declared type.</summary>
        /// <returns>False when the heap, the address, or the slot type could not be resolved.</returns>
        bool WriteHeap(uint32_t address, void* boxedValue);
    };

} // namespace IL2CPP::VRChat
