#include <VRChat/UdonBehaviour.hpp>
#include <IL2CPP.Module/include/MethodHandler.hpp>
#include <IL2CPP.Module/include/System/String.hpp>
#include <IL2CPP.Module/include/System/Array.hpp>
#include <IL2CPP.Module/include/ManagedObject.hpp>
#include <cstring>
#include <format>
#include <unordered_map>

namespace IL2CPP::VRChat {

    using IL2CPP::Module::Class;
    using IL2CPP::Module::Field;
    using IL2CPP::Module::ManagedObject;
    using IL2CPP::Module::Method;
    using IL2CPP::Module::MethodHandler;
    using IL2CPP::Module::Type;
    using IL2CPP::Module::System::String;

    namespace {

        enum : int {
            kTypeBoolean = 0x02, kTypeChar = 0x03,
            kTypeI1 = 0x04, kTypeU1 = 0x05, kTypeI2 = 0x06, kTypeU2 = 0x07,
            kTypeI4 = 0x08, kTypeU4 = 0x09, kTypeI8 = 0x0a, kTypeU8 = 0x0b,
            kTypeR4 = 0x0c, kTypeR8 = 0x0d, kTypeString = 0x0e,
            kTypeValueType = 0x11, kTypeClass = 0x12, kTypeArray = 0x14,
            kTypeI = 0x18, kTypeU = 0x19, kTypeObject = 0x1c, kTypeSzArray = 0x1d,
        };

        ManagedObject AutoProperty(ManagedObject obj, const char* name, const char* backingField) {
            if (!obj) return ManagedObject{};
            if (void* v = obj.get_property<void*>(name)) return ManagedObject{ v };
            return ManagedObject{ obj.get_field<void*>(backingField) };
        }

        ManagedObject EntryPointsOf(void* program) {
            return AutoProperty(ManagedObject{ program }, "EntryPoints", "<EntryPoints>k__BackingField");
        }

        ManagedObject SymbolTableOf(void* program) {
            return AutoProperty(ManagedObject{ program }, "SymbolTable", "<SymbolTable>k__BackingField");
        }

        std::vector<std::string> ReadSymbols(ManagedObject table, const char* field, const char* method) {
            std::vector<std::string> out;
            if (!table) return out;

            void* raw = table.get_field<void*>(field);
            if (!raw) {
                // ImmutableArray<string> is a one-field struct, so the boxed return is the String[].
                if (void* boxed = table.call_method<void*>(method, nullptr, 0))
                    raw = *reinterpret_cast<void**>(IL2CPP::Unbox(boxed));
            }

            Module::System::Array<void*> arr{ raw };
            const uintptr_t n = arr.size();
            out.reserve(static_cast<size_t>(n));
            for (uintptr_t i = 0; i < n; ++i) {
                if (void* s = arr[i]) out.push_back(String(s).to_string());
            }
            return out;
        }

        Method ResolveByReturn(const Class& klass, const char* name, int argc, const char* returnType) {
            if (!klass) return Method{};
            for (const Method& m : klass.get_methods()) {
                if (static_cast<int>(m.param_count()) != argc) continue;
                const char* n = m.name();
                const char* r = m.return_type_name();
                if (n && r && std::strcmp(n, name) == 0 && std::strcmp(r, returnType) == 0) return m;
            }
            return Method{};
        }

        std::string TypeNameOf(void* systemType) {
            if (!systemType) return {};
            Class k = Class::from_system_type(systemType);
            return k ? k.full_name() : std::string{};
        }

        void SetSigned(UdonVariable& var, int64_t value) {
            var.kind = UdonValueKind::Integer;
            var.integer = value;
            var.number = static_cast<double>(value);
            var.display = std::to_string(value);
        }

        void SetUnsigned(UdonVariable& var, uint64_t value) {
            var.kind = UdonValueKind::Unsigned;
            var.integer = static_cast<int64_t>(value);
            var.number = static_cast<double>(value);
            var.display = std::to_string(value);
        }

        void SetFloat(UdonVariable& var, double value) {
            var.kind = UdonValueKind::Float;
            var.integer = static_cast<int64_t>(value);
            var.number = value;
            var.display = std::format("{}", value);
        }

        void SetReference(UdonVariable& var, void* obj) {
            if (!obj) {
                var.kind = UdonValueKind::Null;
                var.display = "null";
                return;
            }
            var.kind = UdonValueKind::Object;
            var.boxed = obj;
            var.display = ManagedObject(obj).to_string();
        }

        // Every heap slot is a StrongBox<T>: value types sit inline at the Value offset,
        // reference types store a pointer there. The il2cpp type enum tells the two apart.
        void DecodeSlot(void* slot, UdonVariable& var) {
            ManagedObject box{ slot };
            Field value = box.get_field_info("Value");
            if (!value) return;

            Type type = value.type();
            if (!type) return;
            var.typeName = type.full_name();
            if (var.typeName.empty()) {
                if (const char* n = value.type_name()) var.typeName = n;
            }

            const int offset = value.offset();
            if (offset < 0) return;
            char* payload = static_cast<char*>(slot) + offset;

            switch (type.type_enum()) {
            case kTypeBoolean:
                var.kind = UdonValueKind::Bool;
                var.integer = *reinterpret_cast<uint8_t*>(payload) ? 1 : 0;
                var.number = static_cast<double>(var.integer);
                var.display = var.integer ? "true" : "false";
                break;
            case kTypeI1:  SetSigned(var, *reinterpret_cast<int8_t*>(payload)); break;
            case kTypeI2:  SetSigned(var, *reinterpret_cast<int16_t*>(payload)); break;
            case kTypeI4:  SetSigned(var, *reinterpret_cast<int32_t*>(payload)); break;
            case kTypeI8:
            case kTypeI:   SetSigned(var, *reinterpret_cast<int64_t*>(payload)); break;
            case kTypeU1:  SetUnsigned(var, *reinterpret_cast<uint8_t*>(payload)); break;
            case kTypeChar:
            case kTypeU2:  SetUnsigned(var, *reinterpret_cast<uint16_t*>(payload)); break;
            case kTypeU4:  SetUnsigned(var, *reinterpret_cast<uint32_t*>(payload)); break;
            case kTypeU8:
            case kTypeU:   SetUnsigned(var, *reinterpret_cast<uint64_t*>(payload)); break;
            case kTypeR4:  SetFloat(var, *reinterpret_cast<float*>(payload)); break;
            case kTypeR8:  SetFloat(var, *reinterpret_cast<double*>(payload)); break;
            case kTypeString: {
                void* str = *reinterpret_cast<void**>(payload);
                if (!str) { var.kind = UdonValueKind::Null; var.display = "null"; break; }
                var.kind = UdonValueKind::String;
                var.boxed = str;
                var.display = String(str).to_string();
                break;
            }
            case kTypeValueType: {
                Class klass = type.get_class();
                if (!klass) break;
                ManagedObject boxed = ManagedObject::box_value(klass, payload);
                if (!boxed) break;
                var.kind = UdonValueKind::Object;
                var.boxed = boxed.raw();
                var.display = boxed.to_string();
                break;
            }
            case kTypeClass:
            case kTypeObject:
            case kTypeArray:
            case kTypeSzArray:
                SetReference(var, *reinterpret_cast<void**>(payload));
                break;
            default:
                break;
            }
        }

        Module::System::Array<void*> HeapSlots(void* heap) {
            if (!heap) return Module::System::Array<void*>{};
            return Module::System::Array<void*>{ ManagedObject(heap).get_field<void*>("_heap") };
        }

        UdonVariable ReadSlot(Module::System::Array<void*> slots, uint32_t address) {
            UdonVariable var;
            var.address = address;
            if (address >= slots.size()) return var;
            void* slot = slots[address];
            if (!slot) return var;
            var.initialized = true;
            DecodeSlot(slot, var);
            return var;
        }

        // Generic instantiations can be either a value or a reference type, so hand those
        // back to the heap itself, which boxes them correctly.
        void DecodeThroughApi(void* heap, UdonVariable& var) {
            ManagedObject obj{ heap };
            if (!obj) return;
            // GetHeapVariable has a generic twin of the same arity; only one returns System.Object.
            static Method getValue = ResolveByReturn(obj.get_class(), "GetHeapVariable", 1, "Object");
            static Method getType  = ResolveByReturn(obj.get_class(), "GetHeapVariableType", 1, "Type");

            void* params[1] = { &var.address };
            if (var.typeName.empty())
                var.typeName = TypeNameOf(MethodHandler::invoke<void*>(getType, heap, params));
            SetReference(var, MethodHandler::invoke<void*>(getValue, heap, params));
        }

        uint32_t AddressOf(ManagedObject symbolTable, std::string_view symbolName, bool& found) {
            uint32_t address = 0;
            found = false;
            if (!symbolTable) return 0;
            auto str = String::create(symbolName);
            void* params[2] = { str.raw(), &address };
            found = symbolTable.call_method<bool>("TryGetAddressFromSymbol", params, 2);
            return found ? address : 0;
        }

    } // namespace

    bool UdonBehaviour::GetSynchronizePosition() {
        if (!valid()) return false;
        return get_field<bool>("SynchronizePosition");
    }

    bool UdonBehaviour::GetSynchronizeAnimation() {
        if (!valid()) return false;
        return get_field<bool>("SynchronizeAnimation");
    }

    bool UdonBehaviour::GetReliable() {
        if (!valid()) return false;
        return get_field<bool>("Reliable");
    }

    SyncType UdonBehaviour::GetSyncMethod() {
        if (!valid()) return SyncType::Unknown;
        return get_field<SyncType>("_syncMethod");
    }

    bool UdonBehaviour::GetIsReady() {
        if (!valid()) return false;
        return get_field<bool>("_isReady");
    }

    bool UdonBehaviour::GetHasError() {
        if (!valid()) return false;
        return get_field<bool>("_hasError");
    }

    bool UdonBehaviour::GetInitialized() {
        if (!valid()) return false;
        return get_field<bool>("_initialized");
    }

    void UdonBehaviour::SendCustomEvent(std::string_view eventName) {
        if (!valid()) return;
        static auto m = MethodHandler::resolve("VRC.Udon.UdonBehaviour", "SendCustomEvent", 1);
        auto str = String::create(eventName);
        void* params[1] = { str.raw() };
        MethodHandler::invoke<void>(m, raw(), params);
    }

    void UdonBehaviour::SendCustomNetworkEvent(NetworkEventTarget target, std::string_view eventName) {
        if (!valid()) return;
        static auto m = MethodHandler::resolve("VRC.Udon.UdonBehaviour", "SendCustomNetworkEvent", 2);
        auto str = String::create(eventName);
        int iTarget = static_cast<int>(target);
        void* params[2] = { &iTarget, str.raw() };
        MethodHandler::invoke<void>(m, raw(), params);
    }

    void UdonBehaviour::RequestSerialization() {
        if (!valid()) return;
        static auto m = MethodHandler::resolve("VRC.Udon.UdonBehaviour", "RequestSerialization", 0);
        MethodHandler::invoke<void>(m, raw());
    }

    void UdonBehaviour::SendCustomEventDelayedSeconds(std::string_view eventName, float delaySeconds, EventTiming eventTiming) {
        if (!valid()) return;
        static auto m = MethodHandler::resolve("VRC.Udon.UdonBehaviour", "SendCustomEventDelayedSeconds", 3);
        auto str = String::create(eventName);
        int iTiming = static_cast<int>(eventTiming);
        void* params[3] = { str.raw(), &delaySeconds, &iTiming };
        MethodHandler::invoke<void>(m, raw(), params);
    }

    void UdonBehaviour::SendCustomEventDelayedFrames(std::string_view eventName, int delayFrames, EventTiming eventTiming) {
        if (!valid()) return;
        static auto m = MethodHandler::resolve("VRC.Udon.UdonBehaviour", "SendCustomEventDelayedFrames", 3);
        auto str = String::create(eventName);
        int iTiming = static_cast<int>(eventTiming);
        void* params[3] = { str.raw(), &delayFrames, &iTiming };
        MethodHandler::invoke<void>(m, raw(), params);
    }

    std::string UdonBehaviour::GetInteractionText() {
        if (!valid()) return "";
        static auto m = MethodHandler::resolve("VRC.Udon.UdonBehaviour", "get_InteractionText", 0);
        void* str = MethodHandler::invoke<void*>(m, raw());
        return str ? String(str).to_string() : "";
    }

    void UdonBehaviour::SetInteractionText(std::string_view text) {
        if (!valid()) return;
        static auto m = MethodHandler::resolve("VRC.Udon.UdonBehaviour", "set_InteractionText", 1);
        auto str = String::create(text);
        void* params[1] = { str.raw() };
        MethodHandler::invoke<void>(m, raw(), params);
    }

    void UdonBehaviour::SetProgramVariable(std::string_view symbolName, void* value) {
        uint32_t address = 0;
        if (!TryGetSymbolAddress(symbolName, address)) return;
        WriteHeap(address, value);
    }

    void* UdonBehaviour::GetProgramVariable(std::string_view symbolName) {
        UdonVariable var;
        if (!TryGetSymbolAddress(symbolName, var.address)) return nullptr;
        DecodeThroughApi(GetHeap(), var);
        return var.boxed;
    }

    bool UdonBehaviour::TryGetVariableValue(std::string_view symbolName, void** value) {
        if (!valid() || !value) return false;
        auto* table = get_field<void*>("publicVariables");
        if (!table) return false;
        ManagedObject tableObj(table);
        auto str = String::create(symbolName);
        void* params[2] = { str.raw(), value };
        return tableObj.call_method<bool>("TryGetVariableValue", params, 2);
    }

    bool UdonBehaviour::TrySetVariableValue(std::string_view symbolName, void* value) {
        if (!valid()) return false;
        auto* table = get_field<void*>("publicVariables");
        if (!table) return false;
        ManagedObject tableObj(table);
        auto str = String::create(symbolName);
        void* params[2] = { str.raw(), value };
        return tableObj.call_method<bool>("TrySetVariableValue", params, 2);
    }

    void* UdonBehaviour::GetProgram() const {
        if (!valid()) return nullptr;
        return get_field<void*>("_program");
    }

    void* UdonBehaviour::GetHeap() const {
        if (!valid()) return nullptr;
        ManagedObject vm{ get_field<void*>("_udonVM") };
        if (vm) {
            if (void* h = vm.get_field<void*>("_heap")) return h;
            if (void* h = vm.call_method<void*>("InspectHeap", nullptr, 0)) return h;
        }
        return AutoProperty(ManagedObject{ GetProgram() }, "Heap", "<Heap>k__BackingField").raw();
    }

    std::string UdonBehaviour::GetInstructionSetIdentifier() const {
        ManagedObject id = AutoProperty(ManagedObject{ GetProgram() },
                                        "InstructionSetIdentifier", "<InstructionSetIdentifier>k__BackingField");
        return id ? String(id.raw()).to_string() : std::string{};
    }

    std::vector<std::string> UdonBehaviour::GetEventNames() const {
        return ReadSymbols(EntryPointsOf(GetProgram()), "_symbols", "GetSymbols");
    }

    std::vector<std::string> UdonBehaviour::GetNetworkedEventNames() const {
        return ReadSymbols(EntryPointsOf(GetProgram()), "_exportedSymbols", "GetExportedSymbols");
    }

    bool UdonBehaviour::HasEvent(std::string_view eventName) const {
        ManagedObject entry = EntryPointsOf(GetProgram());
        if (!entry) return false;
        auto str = String::create(eventName);
        void* params[1] = { str.raw() };
        return entry.call_method<bool>("HasAddressForSymbol", params, 1);
    }

    std::vector<UdonSymbol> UdonBehaviour::GetEntryPoints() const {
        std::vector<UdonSymbol> out;
        ManagedObject table = EntryPointsOf(GetProgram());
        if (!table) return out;

        auto names = ReadSymbols(table, "_symbols", "GetSymbols");
        out.reserve(names.size());
        for (auto& name : names) {
            UdonSymbol sym;
            sym.name = std::move(name);

            bool found = false;
            sym.address = AddressOf(table, sym.name, found);
            if (!found) continue;
            out.push_back(std::move(sym));
        }
        return out;
    }

    std::vector<UdonSymbol> UdonBehaviour::GetSymbols() const {
        std::vector<UdonSymbol> out;
        ManagedObject table = SymbolTableOf(GetProgram());
        if (!table) return out;

        auto names = ReadSymbols(table, "_symbols", "GetSymbols");
        out.reserve(names.size());
        for (auto& name : names) {
            UdonSymbol sym;
            sym.name = std::move(name);

            auto str = String::create(sym.name);
            void* params[1] = { str.raw() };
            sym.typeName = TypeNameOf(table.call_method<void*>("GetSymbolType", params, 1));

            bool found = false;
            sym.address = AddressOf(table, sym.name, found);
            out.push_back(std::move(sym));
        }
        return out;
    }

    std::vector<std::string> UdonBehaviour::GetPublicVariableNames() const {
        return ReadSymbols(SymbolTableOf(GetProgram()), "_exportedSymbols", "GetExportedSymbols");
    }

    bool UdonBehaviour::TryGetSymbolAddress(std::string_view symbolName, uint32_t& address) const {
        bool found = false;
        address = AddressOf(SymbolTableOf(GetProgram()), symbolName, found);
        return found;
    }

    uint32_t UdonBehaviour::GetHeapCapacity() const {
        return static_cast<uint32_t>(HeapSlots(GetHeap()).size());
    }

    UdonVariable UdonBehaviour::ReadHeap(uint32_t address) const {
        void* heap = GetHeap();
        UdonVariable var = ReadSlot(HeapSlots(heap), address);
        if (var.kind == UdonValueKind::Unknown && var.initialized) DecodeThroughApi(heap, var);
        return var;
    }

    UdonVariable UdonBehaviour::ReadVariable(std::string_view symbolName) const {
        uint32_t address = 0;
        if (!TryGetSymbolAddress(symbolName, address)) return {};
        UdonVariable var = ReadHeap(address);
        var.symbol.assign(symbolName);
        return var;
    }

    std::vector<UdonVariable> UdonBehaviour::DumpHeap(bool namedOnly) const {
        std::vector<UdonVariable> out;

        void* heap = GetHeap();
        auto slots = HeapSlots(heap);
        const uintptr_t capacity = slots.size();
        if (capacity == 0) return out;

        std::unordered_map<uint32_t, std::string> names;
        for (auto& sym : GetSymbols()) names.emplace(sym.address, std::move(sym.name));

        out.reserve(namedOnly ? names.size() : static_cast<size_t>(capacity));
        for (uint32_t address = 0; address < capacity; ++address) {
            auto it = names.find(address);
            if (namedOnly && it == names.end()) continue;

            UdonVariable var = ReadSlot(slots, address);
            if (var.kind == UdonValueKind::Unknown && var.initialized) DecodeThroughApi(heap, var);
            if (it != names.end()) var.symbol = it->second;
            out.push_back(std::move(var));
        }
        return out;
    }

    std::vector<UdonCachedExtern> UdonBehaviour::GetCachedExterns() const {
        std::vector<UdonCachedExtern> out;

        auto slots = HeapSlots(GetHeap());
        const uintptr_t capacity = slots.size();
        for (uint32_t address = 0; address < capacity; ++address) {
            void* slot = slots[address];
            if (!slot) continue;

            Field value = ManagedObject(slot).get_field_info("Value");
            if (!value || value.offset() < 0) continue;

            Type valueType = value.type();
            if (!valueType) continue;
            const int typeEnum = valueType.type_enum();
            if (typeEnum != kTypeClass && typeEnum != kTypeObject) continue;

            void* cached = *reinterpret_cast<void**>(static_cast<char*>(slot) + value.offset());
            if (!Module::IsValidPointer(cached)) continue;

            // The slot's declared type is not proof of what it holds, and these offsets are
            // read raw, so the runtime class is checked before anything is dereferenced.
            ManagedObject obj{ cached };
            Class cachedClass = obj.get_class();
            if (!cachedClass) continue;
            const char* className = cachedClass.name();
            if (!className || std::strcmp(className, "CachedUdonExternDelegate") != 0) continue;

            static void* resolvedFor = nullptr;
            static Field signatureField;
            static Field delegateField;
            static Field countField;
            if (resolvedFor != cachedClass.raw()) {
                Field s = obj.get_field_info("externSignature");
                Field d = obj.get_field_info("externDelegate");
                Field c = obj.get_field_info("parameterCount");
                if (!d || d.offset() < 0) continue;
                signatureField = s;
                delegateField = d;
                countField = c;
                resolvedFor = cachedClass.raw();
            }
            if (!delegateField || delegateField.offset() < 0) continue;

            void* del = *reinterpret_cast<void**>(static_cast<char*>(cached) + delegateField.offset());
            if (!Module::IsValidPointer(del)) continue;

            void* fn = *reinterpret_cast<void**>(static_cast<char*>(del) + Module::g_layoutOffsets.delegateMethodPtr);
            if (!Module::IsValidPointer(fn)) continue;

            UdonCachedExtern entry;
            entry.address = address;
            entry.delegateObject = del;
            entry.methodPointer = fn;
            if (signatureField && signatureField.offset() >= 0) {
                if (void* str = *reinterpret_cast<void**>(static_cast<char*>(cached) + signatureField.offset()))
                    entry.signature = String(str).to_string();
            }
            if (countField && countField.offset() >= 0)
                entry.parameterCount = *reinterpret_cast<int32_t*>(static_cast<char*>(cached) + countField.offset());
            out.push_back(std::move(entry));
        }
        return out;
    }

    bool UdonBehaviour::WriteHeap(uint32_t address, void* boxedValue) {
        ManagedObject heap{ GetHeap() };
        if (!heap) return false;

        static Method getType = ResolveByReturn(heap.get_class(), "GetHeapVariableType", 1, "Type");
        static Method setValue = ResolveByReturn(heap.get_class(), "SetHeapVariable", 3, "Void");
        if (!setValue) return false;

        void* typeParams[1] = { &address };
        void* type = MethodHandler::invoke<void*>(getType, heap.raw(), typeParams);
        if (!type) return false;

        void* params[3] = { &address, boxedValue, type };
        MethodHandler::invoke<void>(setValue, heap.raw(), params);
        return true;
    }

} // namespace IL2CPP::VRChat
