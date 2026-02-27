#include <include/il2cpp_module.hpp>
#include <IL2CPP.Common/il2cpp_unity_shared.hpp>
#include <Windows.h>
#include <atomic>
#include <string>


namespace IL2CPP::Module {

    namespace {

        struct ConnectionState {
            std::atomic<bool>           connected{ false };
            HANDLE                      shared_memory_handle = nullptr;
            IL2CPP::il2cpp_exports const*       exports = nullptr;
            HANDLE                      unity_memory_handle = nullptr;
            unity_functions const*      unity = nullptr;
        };

        ConnectionState g_conn;

    }

    bool Connect() {
        if (g_conn.connected.exchange(true, std::memory_order_acq_rel))
            return true;

        std::wstring memName = std::wstring(exports_shared_prefix) + 
                               std::to_wstring(GetCurrentProcessId()) + 
                               exports_shared_suffix;

        g_conn.shared_memory_handle = OpenFileMappingW(
            FILE_MAP_READ, FALSE, memName.c_str());


        if (!g_conn.shared_memory_handle) {
            g_conn.connected.store(false, std::memory_order_release);
            return false;
        }

        g_conn.exports = static_cast<IL2CPP::il2cpp_exports const*>(
            MapViewOfFile(g_conn.shared_memory_handle,
                FILE_MAP_READ, 0, 0, sizeof(il2cpp_exports)));

        if (!g_conn.exports || g_conn.exports->m_uVersion != exports_version) {
            if (g_conn.exports) {
                UnmapViewOfFile(const_cast<IL2CPP::il2cpp_exports*>(g_conn.exports));
                g_conn.exports = nullptr;
            }
            CloseHandle(g_conn.shared_memory_handle);
            g_conn.shared_memory_handle = nullptr;
            g_conn.connected.store(false, std::memory_order_release);
            return false;
        }

        std::wstring unityMemName = std::wstring(unity_shared_prefix) + 
                                    std::to_wstring(GetCurrentProcessId()) + 
                                    unity_shared_suffix;

        g_conn.unity_memory_handle = OpenFileMappingW(
            FILE_MAP_READ, FALSE, unityMemName.c_str());


        if (g_conn.unity_memory_handle) {
            g_conn.unity = static_cast<unity_functions const*>(
                MapViewOfFile(g_conn.unity_memory_handle,
                    FILE_MAP_READ, 0, 0, sizeof(unity_functions)));

            if (!g_conn.unity || g_conn.unity->m_uVersion != unity_version) {
                if (g_conn.unity) {
                    UnmapViewOfFile(const_cast<unity_functions*>(g_conn.unity));
                    g_conn.unity = nullptr;
                }
                CloseHandle(g_conn.unity_memory_handle);
                g_conn.unity_memory_handle = nullptr;
            }
        }

        return true;
    }

    void Disconnect() {
        if (!g_conn.connected.exchange(false, std::memory_order_acq_rel))
            return;

        if (g_conn.unity) {
            UnmapViewOfFile(const_cast<unity_functions*>(g_conn.unity));
            g_conn.unity = nullptr;
        }
        if (g_conn.unity_memory_handle) {
            CloseHandle(g_conn.unity_memory_handle);
            g_conn.unity_memory_handle = nullptr;
        }

        if (g_conn.exports) {
            UnmapViewOfFile(const_cast<IL2CPP::il2cpp_exports*>(g_conn.exports));
            g_conn.exports = nullptr;
        }
        if (g_conn.shared_memory_handle) {
            CloseHandle(g_conn.shared_memory_handle);
            g_conn.shared_memory_handle = nullptr;
        }
    }

    [[nodiscard]] bool IsConnected() noexcept {
        return g_conn.connected.load(std::memory_order_acquire) && g_conn.exports;
    }

    [[nodiscard]] IL2CPP::il2cpp_exports const* GetExports() noexcept {
        return g_conn.exports;
    }

    namespace {
        extern "C" inline IL2CPP::il2cpp_exports const* E() {
            return g_conn.exports;
        }
    }

    void* GetDomain() {
        if (!E() || !E()->m_domainGet) return nullptr;
        return reinterpret_cast<void*(IL2CPP_CALLTYPE)()>(E()->m_domainGet)();
    }

    il2cppAssembly** GetAssemblies(size_t* count) {
        if (!E() || !E()->m_domainGetAssemblies) return nullptr;
        return reinterpret_cast<il2cppAssembly**(IL2CPP_CALLTYPE)(void*, size_t*)>(
            E()->m_domainGetAssemblies)(GetDomain(), count);
    }

    void* ThreadAttach(void* domain) {
        if (!E() || !E()->m_threadAttach) return nullptr;
        return reinterpret_cast<void*(IL2CPP_CALLTYPE)(void*)>(E()->m_threadAttach)(domain);
    }

    void ThreadDetach(void* thread) {
        if (!E() || !E()->m_threadDetach) return;
        reinterpret_cast<void(IL2CPP_CALLTYPE)(void*)>(E()->m_threadDetach)(thread);
    }

    // ========================================================================
    //  Class Lookup
    // ========================================================================

    il2cppClass* FindClass(std::string_view fullName) {
        // Use Core's helper function which has caching and deobfuscation
        if (!E() || !E()->m_helperFindClass) return nullptr;
        return static_cast<il2cppClass*>(
            reinterpret_cast<void*(IL2CPP_CALLTYPE)(const char*)>(E()->m_helperFindClass)(
                std::string(fullName).c_str()));
    }

    il2cppClass* GetClassFromName(il2cppImage* image, const char* ns, const char* name) {
        if (!E() || !E()->m_classFromName) return nullptr;
        return reinterpret_cast<il2cppClass*(IL2CPP_CALLTYPE)(void*, const char*, const char*)>(
            E()->m_classFromName)(image, ns, name);
    }

    il2cppType* GetType(il2cppClass* klass) {
        if (!E() || !E()->m_classGetType || !klass) return nullptr;
        return reinterpret_cast<il2cppType*(IL2CPP_CALLTYPE)(void*)>(E()->m_classGetType)(klass);
    }

    il2cppClass* ClassFromType(il2cppType* type) {
        if (!E() || !E()->m_classFromIl2cppType || !type) return nullptr;
        return reinterpret_cast<il2cppClass*(IL2CPP_CALLTYPE)(void*)>(E()->m_classFromIl2cppType)(type);
    }

    il2cppClass* GetParent(il2cppClass* klass) {
        if (!E() || !E()->m_classGetParent || !klass) return nullptr;
        return reinterpret_cast<il2cppClass*(IL2CPP_CALLTYPE)(void*)>(E()->m_classGetParent)(klass);
    }

    il2cppSystemType* GetSystemType(il2cppClass* klass) {
        if (!E() || !E()->m_typeGetObject || !E()->m_classGetType || !klass) return nullptr;
        auto* type = reinterpret_cast<il2cppType*(IL2CPP_CALLTYPE)(void*)>(E()->m_classGetType)(klass);
        if (!type) return nullptr;
        return reinterpret_cast<il2cppSystemType*(IL2CPP_CALLTYPE)(void*)>(E()->m_typeGetObject)(type);
    }

    // ========================================================================
    //  Field API
    // ========================================================================

    il2cppFieldInfo* GetFields(il2cppClass* klass, void** iter) {
        if (!E() || !E()->m_classGetFields || !klass) return nullptr;
        return reinterpret_cast<il2cppFieldInfo*(IL2CPP_CALLTYPE)(void*, void**)>(
            E()->m_classGetFields)(klass, iter);
    }

    il2cppFieldInfo* GetFieldByName(il2cppClass* klass, const char* name) {
        if (!E() || !E()->m_classGetFieldFromName || !klass || !name) return nullptr;
        return reinterpret_cast<il2cppFieldInfo*(IL2CPP_CALLTYPE)(void*, const char*)>(
            E()->m_classGetFieldFromName)(klass, name);
    }

    int GetFieldOffset(il2cppClass* klass, const char* fieldName) {
        auto* field = GetFieldByName(klass, fieldName);
        if (!field) return -1;
        // Access offset through the il2cppFieldInfo structure
        return *reinterpret_cast<int32_t*>(reinterpret_cast<char*>(field) + 0x18);
    }

    void GetStaticFieldValue(il2cppFieldInfo* field, void* outValue) {
        if (!E() || !E()->m_fieldStaticGetValue || !field || !outValue) return;
        reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, void*)>(E()->m_fieldStaticGetValue)(field, outValue);
    }

    void SetStaticFieldValue(il2cppFieldInfo* field, void* value) {
        if (!E() || !E()->m_fieldStaticSetValue || !field || !value) return;
        reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, void*)>(E()->m_fieldStaticSetValue)(field, value);
    }

    void GetFieldValue(il2cppObject* obj, il2cppFieldInfo* field, void* outValue) {
        if (!E() || !E()->m_fieldGetValue || !obj || !field || !outValue) return;
        reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, void*, void*)>(E()->m_fieldGetValue)(obj, field, outValue);
    }

    void SetFieldValue(il2cppObject* obj, il2cppFieldInfo* field, void* value) {
        if (!E() || !E()->m_fieldSetValue || !obj || !field || !value) return;
        reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, void*, void*)>(E()->m_fieldSetValue)(obj, field, value);
    }

    // ========================================================================
    //  Method API
    // ========================================================================

    il2cppMethodInfo* GetMethods(il2cppClass* klass, void** iter) {
        if (!E() || !E()->m_classGetMethods || !klass) return nullptr;
        return reinterpret_cast<il2cppMethodInfo*(IL2CPP_CALLTYPE)(void*, void**)>(
            E()->m_classGetMethods)(klass, iter);
    }

    il2cppMethodInfo* GetMethodByName(il2cppClass* klass, const char* name, int argc) {
        if (!E() || !E()->m_classGetMethodFromName || !klass || !name) return nullptr;
        return reinterpret_cast<il2cppMethodInfo*(IL2CPP_CALLTYPE)(void*, const char*, int)>(
            E()->m_classGetMethodFromName)(klass, name, argc);
    }

    void* GetMethodPointer(il2cppClass* klass, const char* name, int argc) {
        auto* method = GetMethodByName(klass, name, argc);
        if (!method) return nullptr;
        // m_pMethodPointer is the first field of il2cppMethodInfo
        return *reinterpret_cast<void**>(method);
    }

    il2cppType* GetMethodParamType(il2cppMethodInfo* method, uint32_t index) {
        if (!E() || !E()->m_methodGetParam || !method) return nullptr;
        return reinterpret_cast<il2cppType*(IL2CPP_CALLTYPE)(void*, uint32_t)>(
            E()->m_methodGetParam)(method, index);
    }

    const char* GetMethodParamName(il2cppMethodInfo* method, uint32_t index) {
        if (!E() || !E()->m_methodGetParamName || !method) return nullptr;
        return reinterpret_cast<const char*(IL2CPP_CALLTYPE)(void*, uint32_t)>(
            E()->m_methodGetParamName)(method, index);
    }

    // ========================================================================
    //  Property API
    // ========================================================================

    il2cppPropertyInfo* GetProperties(il2cppClass* klass, void** iter) {
        if (!E() || !E()->m_classGetProperties || !klass) return nullptr;
        return reinterpret_cast<il2cppPropertyInfo*(IL2CPP_CALLTYPE)(void*, void**)>(
            E()->m_classGetProperties)(klass, iter);
    }

    il2cppPropertyInfo* GetPropertyByName(il2cppClass* klass, const char* name) {
        if (!E() || !E()->m_classGetPropertyFromName || !klass || !name) return nullptr;
        return reinterpret_cast<il2cppPropertyInfo*(IL2CPP_CALLTYPE)(void*, const char*)>(
            E()->m_classGetPropertyFromName)(klass, name);
    }

    // ========================================================================
    //  Object
    // ========================================================================

    il2cppObject* NewObject(il2cppClass* klass) {
        if (!E() || !E()->m_objectNew || !klass) return nullptr;
        return reinterpret_cast<il2cppObject*(IL2CPP_CALLTYPE)(void*)>(E()->m_objectNew)(klass);
    }

    il2cppObject* Box(il2cppClass* klass, void* data) {
        if (!E() || !E()->m_valueBox || !klass || !data) return nullptr;
        return reinterpret_cast<il2cppObject*(IL2CPP_CALLTYPE)(void*, void*)>(E()->m_valueBox)(klass, data);
    }

    il2cppObject* RuntimeInvoke(il2cppMethodInfo* method, void* obj, void** params, void** exc) {
        if (!E() || !E()->m_runtimeInvoke || !method) return nullptr;
        return reinterpret_cast<il2cppObject*(IL2CPP_CALLTYPE)(void*, void*, void**, void**)>(
            E()->m_runtimeInvoke)(method, obj, params, exc);
    }

    // ========================================================================
    //  String
    // ========================================================================

    void* StringNew(const char* str) {
        if (!E() || !E()->m_stringNew || !str) return nullptr;
        return reinterpret_cast<void*(IL2CPP_CALLTYPE)(const char*)>(E()->m_stringNew)(str);
    }

    // ========================================================================
    //  ResolveCall
    // ========================================================================

    void* ResolveCall(std::string_view fullPath, bool isExtern) {
        if (!E() || !E()->m_helperResolveCall) return nullptr;
        return reinterpret_cast<void*(IL2CPP_CALLTYPE)(const char*, bool)>(
            E()->m_helperResolveCall)(std::string(fullPath).c_str(), isExtern);
    }

    // ========================================================================
    //  Name Stabilization Queries
    // ========================================================================

    const char* GetStableName(const char* obfuscatedName) {
        if (!E() || !E()->m_helperGetStableName || !obfuscatedName) return obfuscatedName;
        return reinterpret_cast<const char*(IL2CPP_CALLTYPE)(const char*)>(
            E()->m_helperGetStableName)(obfuscatedName);
    }

    const char* GetOriginalName(const char* stableName) {
        if (!E() || !E()->m_helperGetOriginalName || !stableName) return stableName;
        return reinterpret_cast<const char*(IL2CPP_CALLTYPE)(const char*)>(
            E()->m_helperGetOriginalName)(stableName);
    }

    // ========================================================================
    //  Convenience: Fetch Helpers
    // ========================================================================

    size_t FetchFields(il2cppClass* klass, std::vector<il2cppFieldInfo*>& out) {
        out.clear();
        if (!klass) return 0;

        void* iter = nullptr;
        size_t count = 0;
        while (auto* field = GetFields(klass, &iter)) {
            out.emplace_back(field);
            ++count;
        }
        return count;
    }

    size_t FetchMethods(il2cppClass* klass, std::vector<il2cppMethodInfo*>& out) {
        out.clear();
        if (!klass) return 0;

        void* iter = nullptr;
        size_t count = 0;
        while (auto* method = GetMethods(klass, &iter)) {
            out.emplace_back(method);
            ++count;
        }
        return count;
    }

    size_t FetchClasses(std::vector<il2cppClass*>& out, std::string_view assemblyName) {
        out.clear();
        if (!E() || !E()->m_domainGetAssemblies || !E()->m_imageGetClassCount || !E()->m_imageGetClass)
            return 0;

        size_t assemblyCount = 0;
        auto** assemblies = GetAssemblies(&assemblyCount);
        if (!assemblies || assemblyCount == 0) return 0;

        // Find the assembly's image
        for (size_t a = 0; a < assemblyCount; ++a) {
            auto* assembly = assemblies[a];
            if (!assembly) continue;

            // Access image from assembly (first field)
            auto* image = *reinterpret_cast<il2cppImage**>(assembly);
            if (!image) continue;

            // Compare assembly name (second field of il2cppImage = m_pNameNoExt)
            const char* imageName = *reinterpret_cast<const char**>(
                reinterpret_cast<char*>(image) + sizeof(void*));
            if (!imageName || assemblyName != imageName) continue;

            size_t classCount = reinterpret_cast<size_t(IL2CPP_CALLTYPE)(void*)>(
                E()->m_imageGetClassCount)(image);

            for (size_t c = 0; c < classCount; ++c) {
                auto* klass = reinterpret_cast<il2cppClass*(IL2CPP_CALLTYPE)(void*, size_t)>(
                    E()->m_imageGetClass)(image, c);
                if (klass) out.emplace_back(klass);
            }
            break;
        }

        return out.size();
    }

    // ========================================================================
    //  Unity Functions Access
    // ========================================================================

    unity_functions const* GetUnityFunctions() noexcept {
        return g_conn.unity;
    }

    bool IsUnityConnected() noexcept {
        return g_conn.unity != nullptr;
    }

} // namespace IL2CPP::Module
