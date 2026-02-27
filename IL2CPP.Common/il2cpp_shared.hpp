#pragma once
#include <cstdint>

// ============================================================================
//  IL2CPP.Common - Shared types between IL2CPP.Core and IL2CPP.Module
//  Mirrors the pattern of Logging.Common/include/logger_shared.hpp
// ============================================================================

namespace IL2CPP {

    // ---- Forward declarations for IL2CPP types ----
    // These are opaque pointers representing IL2CPP internal types.
    struct Il2CppSystemType;  // System.Type reflection object

    // ---- Calling convention for IL2CPP exports ----
#ifndef IL2CPP_CALLTYPE
#   ifdef _WIN64
#       define IL2CPP_CALLTYPE __fastcall*
#   else
#       define IL2CPP_CALLTYPE __stdcall*
#   endif
#endif

    // ---- Unity Callback Events ----
    enum class UnityEvent : uint8_t {
        Update = 0,
        LateUpdate,
        FixedUpdate,
        PostLateUpdate,
        OnSceneLoaded,
        OnSceneUnloaded
    };

    // ---- .NET metadata constants ----

    // Field access modifiers (mask = 0x0007)
    constexpr uint16_t FIELD_ATTRIBUTE_ACCESS_MASK   = 0x0007;
    constexpr uint16_t FIELD_ATTRIBUTE_PRIVATE       = 0x0001;
    constexpr uint16_t FIELD_ATTRIBUTE_FAM_AND_ASSEM = 0x0002;  // private protected
    constexpr uint16_t FIELD_ATTRIBUTE_ASSEMBLY      = 0x0003;  // internal
    constexpr uint16_t FIELD_ATTRIBUTE_FAMILY        = 0x0004;  // protected
    constexpr uint16_t FIELD_ATTRIBUTE_FAM_OR_ASSEM  = 0x0005;  // protected internal
    constexpr uint16_t FIELD_ATTRIBUTE_PUBLIC        = 0x0006;
    constexpr uint16_t FIELD_ATTRIBUTE_STATIC        = 0x0010;
    constexpr uint16_t FIELD_ATTRIBUTE_INIT_ONLY     = 0x0020;
    constexpr uint16_t FIELD_ATTRIBUTE_LITERAL       = 0x0040;
    constexpr uint16_t FIELD_ATTRIBUTE_HAS_DEFAULT   = 0x8000;

    // Method access modifiers (mask = 0x0007)
    constexpr uint16_t METHOD_ATTRIBUTE_ACCESS_MASK  = 0x0007;
    constexpr uint16_t METHOD_ATTRIBUTE_PRIVATE      = 0x0001;
    constexpr uint16_t METHOD_ATTRIBUTE_FAM_AND_ASSEM= 0x0002;  // private protected
    constexpr uint16_t METHOD_ATTRIBUTE_ASSEMBLY     = 0x0003;  // internal
    constexpr uint16_t METHOD_ATTRIBUTE_FAMILY       = 0x0004;  // protected
    constexpr uint16_t METHOD_ATTRIBUTE_FAM_OR_ASSEM = 0x0005;  // protected internal
    constexpr uint16_t METHOD_ATTRIBUTE_PUBLIC       = 0x0006;
    constexpr uint16_t METHOD_ATTRIBUTE_STATIC       = 0x0010;
    constexpr uint16_t METHOD_ATTRIBUTE_FINAL        = 0x0020;  // sealed
    constexpr uint16_t METHOD_ATTRIBUTE_VIRTUAL      = 0x0040;
    constexpr uint16_t METHOD_ATTRIBUTE_ABSTRACT     = 0x0400;

    // ---- IL2CPP export vtable ----
    // Lives in shared memory. Core writes it, Module reads it.
    // All function pointer slots are void* - callers cast to the appropriate signature.

    struct il2cpp_exports {
        uint32_t    m_uVersion;
        void*       m_hModule;              // HMODULE of GameAssembly.dll

        // ===== Domain =====
        void*       m_domainGet;            // void*()
        void*       m_domainGetAssemblies;  // void**(void* domain, size_t* count)

        // ===== Thread =====
        void*       m_threadAttach;         // void*(void* domain)
        void*       m_threadDetach;         // void(void* thread)

        // ===== Init / Shutdown =====
        void*       m_init;                 // int(const char* domain_name)
        void*       m_shutdown;             // void()

        // ===== Class =====
        void*       m_classFromName;        // void*(void* image, const char* ns, const char* name)
        void*       m_classFromIl2cppType;  // void*(void* type)
        void*       m_classFromSystemType;  // void*(void* systemType)
        void*       m_classGetType;         // void*(void* klass)
        void*       m_classGetParent;       // void*(void* klass)
        void*       m_classGetDeclaringType;// void*(void* klass)
        void*       m_classGetElementClass; // void*(void* klass)
        void*       m_classGetFields;       // void*(void* klass, void** iter)
        void*       m_classGetFieldFromName;// void*(void* klass, const char* name)
        void*       m_classGetMethods;      // void*(void* klass, void** iter)
        void*       m_classGetMethodFromName;// void*(void* klass, const char* name, int argc)
        void*       m_classGetProperties;   // void*(void* klass, void** iter)
        void*       m_classGetPropertyFromName; // void*(void* klass, const char* name)
        void*       m_classGetEvents;       // void*(void* klass, void** iter)
        void*       m_classGetNestedTypes;  // void*(void* klass, void** iter)
        void*       m_classGetInterfaces;   // void*(void* klass, void** iter)
        void*       m_classEnumBasetype;    // void*(void* klass)
        void*       m_classIsGeneric;       // bool(void* klass)
        void*       m_classIsSubclassOf;    // bool(void* klass, void* parent)
        void*       m_classIsEnum;          // bool(void* klass)
        void*       m_classHasAttribute;    // bool(void* klass, void* attr)
        void*       m_classGetStaticFieldData; // void*(void* klass)
        void*       m_classGetBitmap;       // void(void* klass, size_t* bitmap, uint32_t maxLen)
        void*       m_classGetBitmapSize;   // uint32_t(void* klass)

        // ===== Image =====
        void*       m_imageGetClassCount;   // size_t(void* image)
        void*       m_imageGetClass;        // void*(void* image, size_t index)
        void*       m_assemblyGetImage;     // void*(void* assembly)

        // ===== Type =====
        void*       m_typeGetObject;        // void*(void* type)
        void*       m_typeGetType;          // int(void* type)
        void*       m_typeGetName;          // const char*(void* type)
        void*       m_typeIsByref;          // bool(void* type)
        void*       m_typeGetAssemblyQualifiedName; // const char*(void* type)
        void*       m_typeGetReflectionName;// char*(void* type)

        // ===== Field =====
        void*       m_fieldGetValue;        // void(void* obj, void* field, void* value)
        void*       m_fieldSetValue;        // void(void* obj, void* field, void* value)
        void*       m_fieldStaticGetValue;  // void(void* field, void* value)
        void*       m_fieldStaticSetValue;  // void(void* field, void* value)
        void*       m_fieldHasAttribute;    // bool(void* field, void* attr)

        // ===== Method =====
        void*       m_methodGetObject;      // void*(void* method, void* refclass)
        void*       m_methodGetParam;       // void*(void* method, uint32_t index)
        void*       m_methodGetParamName;   // const char*(void* method, uint32_t index)
        void*       m_methodGetFlags;       // uint32_t(void* method, uint32_t* implFlags)
        void*       m_methodHasAttribute;   // bool(void* method, void* attr)

        // ===== Object =====
        void*       m_objectNew;            // void*(void* klass)
        void*       m_valueBox;             // void*(void* klass, void* data)

        // ===== Runtime =====
        void*       m_runtimeInvoke;        // void*(void* method, void* obj, void** params, void** exc)
        void*       m_resolveFunction;      // void*(const char* name) -- il2cpp_resolve_icall

        // ===== String =====
        void*       m_stringNew;            // void*(const char* str)

        // ===== Array =====
        void*       m_arrayClassGet;        // void*(void* elementClass, uint32_t rank)
        void*       m_arrayNew;             // void*(void* elementTypeInfo, uintptr_t length)
        void*       m_arrayNewSpecific;     // void*(void* arrayTypeInfo, uintptr_t length)
        void*       m_arrayNewFull;         // void*(void* arrayTypeInfo, uintptr_t* lengths, uintptr_t* lowerBounds)

        // ===== Memory =====
        void*       m_alloc;                // void*(size_t size)
        void*       m_free;                 // void(void* ptr)

        // ===== GC =====
        void*       m_gcCollect;            // void(int maxGen)
        void*       m_gcCollectALittle;     // void()

        // ===== Core Helper Functions (implemented by IL2CPP.Core) =====
        // These allow modules to use Core's cached lookups and deobfuscation.
        void*       m_helperFindClass;      // void*(const char* fullName)
        void*       m_helperResolveCall;    // void*(const char* fullPath, bool isExtern)
        void*       m_helperGetStableName;  // const char*(const char* obfuscatedName)
        void*       m_helperGetOriginalName;// const char*(const char* stableName)
        void*       m_helperAddMapping;     // void(const char* obfuscated, const char* deobfuscated)
        void*       m_helperGetClassStableName; // const char*(void* klass) -- get/generate stable name for class
        void*       m_helperGetClassStableNamespace; // const char*(void* klass) -- get stable namespace for class
        void*       m_helperGetClassStableFullName;  // const char*(void* klass) -- get stable full name (ns.name) for class
        void*       m_helperGetTypeStableName;  // const char*(void* type)  -- get/generate stable name for type
        void*       m_helperGetTypeStableNamespace; // const char*(void* type) -- get stable namespace for type
        void*       m_helperGetTypeStableFullName;  // const char*(void* type) -- get stable full name for type

        // ===== Core Reflection Helpers (used by Module ClassResolver) =====
        void*       m_helperClassFromType;  // void*(void* type)  -- il2cppClass* from il2cppType*
        void*       m_helperGetMethodParamType; // void*(void* method, uint32_t index)
        void*       m_helperGetMethodReturnType;// void*(void* method)  -- il2cppType* from method

        // ===== ClassCache Helpers (for Module's wrapped ClassCache) =====
        void*       m_helperCacheLoad;          // void(const char* assembly)
        void*       m_helperCacheLoadMultiple;  // void(const char** assemblies, size_t count)
        void*       m_helperCacheRelease;       // void()
        void*       m_helperCacheReleaseOne;    // void(const char* assembly)
        void*       m_helperCacheGetClasses;    // void*(const char* assembly, size_t* outCount)  -- returns void** array
        void*       m_helperCacheFilter;        // void*(const char** sigs, size_t sigCount, const char* assembly)
        void*       m_helperCacheFilterAll;     // void*(const char** sigs, size_t sigCount)

        // ===== Unity Callback Helpers =====
        void*       m_helperCallbackRegister;       // void(void* callback, UnityEvent event)
        void*       m_helperCallbackInitialize;     // void()
        void*       m_helperCallbackUninitialize;   // void()
    };

    // ---- Version & shared memory ----
    constexpr uint32_t      exports_version     = 7;  // Added il2cpp_value_box
    constexpr wchar_t const* exports_shared_prefix = L"Local\\UNIx_PID_";
    constexpr wchar_t const* exports_shared_suffix = L"_IL2CPPCore";


} // namespace IL2CPP
