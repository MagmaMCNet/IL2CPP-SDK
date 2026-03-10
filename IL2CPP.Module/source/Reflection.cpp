#ifndef UNITY_VERSION_2022_3_8_HIGHER
#define UNITY_VERSION_2022_3_8_HIGHER
#endif

#include <include/Reflection.hpp>
#include <include/ManagedObject.hpp>
#include <include/Deobfuscation.hpp>
#include <include/il2cpp_module.hpp>
#include <cstring>

namespace IL2CPP::Module {

    namespace {
        inline il2cpp_exports const* E() {
            return GetExports();
        }

        inline std::string build_member_key(const char* className, const char* memberName) {
            if (!className || !memberName) return memberName ? memberName : "";
            return std::string(className) + "::" + memberName;
        }

        inline bool isValidPointer(const void* ptr) noexcept {
            uintptr_t val = reinterpret_cast<uintptr_t>(ptr);
            return val > 0x10000 && val < 0x7FFFFFFFFFFF;
        }

        inline const char* extract_member_name(const char* result) {
            const char* colonPos = std::strstr(result, "::");
            return colonPos ? colonPos + 2 : result;
        }

        // Resolve a member name by trying deobfuscated class name first, then stabilized.
        // Chain: rawClassName -> stableClassName -> humanClassName
        // Lookup "humanClassName::rawMemberName" for deobfuscated name,
        // falling back to "stableClassName::rawMemberName" for stabilized name.
        inline const char* resolve_member_name(const char* rawClassName, const char* rawMemberName) {
            const char* stableClassName = Deobfuscation::GetStableName(rawClassName);

            // Chain-resolve: stable class -> human class name
            const char* humanClassName = Deobfuscation::GetStableName(stableClassName);
            if (humanClassName && humanClassName != stableClassName &&
                std::strcmp(humanClassName, stableClassName) != 0) {
                std::string humanKey = build_member_key(humanClassName, rawMemberName);
                const char* deobf = Deobfuscation::GetStableName(humanKey.c_str());
                if (deobf && deobf != humanKey.c_str() && std::strcmp(deobf, humanKey.c_str()) != 0)
                    return extract_member_name(deobf);
            }

            // Fall back to stabilized name
            std::string key = build_member_key(stableClassName, rawMemberName);
            const char* stable = Deobfuscation::GetStableName(key.c_str());
            if (stable && stable != key.c_str() && std::strcmp(stable, key.c_str()) != 0)
                return extract_member_name(stable);

            return nullptr;
        }
    }

    const char* Type::raw_name() const {
        if (!m_native || !E() || !E()->m_typeGetName) return "";
        const char* result = reinterpret_cast<const char*(IL2CPP_CALLTYPE)(void*)>(E()->m_typeGetName)(m_native);
        return result ? result : "";
    }

    const char* Type::raw_ns() const {
        Class klass = get_class();
        if (klass) return klass.raw_ns();
        return "";
    }

    const char* Type::ns() const {
        if (!m_native || !E()) return "";

        if (E()->m_helperGetTypeStableNamespace) {
            const char* result = reinterpret_cast<const char*(IL2CPP_CALLTYPE)(void*)>(
                E()->m_helperGetTypeStableNamespace)(m_native);
            return result ? result : "";
        }

        // Fallback: get from class
        Class klass = get_class();
        if (klass) return klass.ns();
        return "";
    }

    std::string Type::raw_full_name() const {
        Class klass = get_class();
        if (klass) return klass.raw_full_name();
        // Fallback to raw name only
        const char* n = raw_name();
        return n ? n : "";
    }

    std::string Type::full_name() const {
        if (!m_native || !E()) return "";
        
        // Use Core's cached helper for O(1) lookup after first call
        if (E()->m_helperGetTypeStableFullName) {
            const char* result = reinterpret_cast<const char*(IL2CPP_CALLTYPE)(void*)>(
                E()->m_helperGetTypeStableFullName)(m_native);
            if (result && *result) return result;
        }

        // Fallback: get from class
        Class klass = get_class();
        if (klass) return klass.full_name();
        
        // Fallback to name only
        const char* n = name();
        return n ? n : "";
    }

    Class Type::get_class() const {
        // Try to get the underlying class for this type
        if (!m_native || !E() || !E()->m_classFromIl2cppType) return Class(nullptr);
        void* klass = reinterpret_cast<void*(IL2CPP_CALLTYPE)(void*)>(E()->m_classFromIl2cppType)(m_native);
        return Class(klass);
    }

    const char* Type::name() const {
        if (!m_native || !E()) return "";
        
        // Use Core's helper which handles all type kinds and generates stable names on-demand
        // Don't try fallbacks - they can crash with invalid type pointers
        if (E()->m_helperGetTypeStableName) {
            const char* result = reinterpret_cast<const char*(IL2CPP_CALLTYPE)(void*)>(
                E()->m_helperGetTypeStableName)(m_native);
            return (result && *result) ? result : "";
        }

        return "";
    }

    int Type::type_enum() const {
        if (!m_native || !E() || !E()->m_typeGetType) return -1;
        return reinterpret_cast<int(IL2CPP_CALLTYPE)(void*)>(E()->m_typeGetType)(m_native);
    }

    bool Type::is_byref() const {
        if (!m_native || !E() || !E()->m_typeIsByref) return false;
        return reinterpret_cast<bool(IL2CPP_CALLTYPE)(void*)>(E()->m_typeIsByref)(m_native);
    }

    const char* Type::assembly_qualified_name() const {
        if (!m_native || !E() || !E()->m_typeGetAssemblyQualifiedName) return "";
        return reinterpret_cast<const char*(IL2CPP_CALLTYPE)(void*)>(E()->m_typeGetAssemblyQualifiedName)(m_native);
    }

    void* Type::get_system_type_object() const {
        if (!m_native || !E() || !E()->m_typeGetObject) return nullptr;
        return reinterpret_cast<void*(IL2CPP_CALLTYPE)(void*)>(E()->m_typeGetObject)(m_native);
    }

    // ========================================================================
    //  Field
    // ========================================================================

    const char* Field::raw_name() const {
        if (!m_native) return "";
        // il2cppFieldInfo::m_pName is the first field
        return *reinterpret_cast<const char**>(m_native);
    }

    const char* Field::name() const {
        const char* raw = raw_name();
        if (!raw || !*raw) return raw;

        // Try qualified lookup: deobfuscated name first, then stabilized
        void* parentClass = *reinterpret_cast<void**>(static_cast<char*>(m_native) + 2 * sizeof(void*));
        if (isValidPointer(parentClass)) {
            const char* rawClassName = *reinterpret_cast<const char**>(
                static_cast<char*>(parentClass) + 2 * sizeof(void*));
            if (isValidPointer(rawClassName)) {
                const char* resolved = resolve_member_name(rawClassName, raw);
                if (resolved) return resolved;
            }
        }

        return Deobfuscation::GetStableName(raw);
    }

    const char* Field::raw_type_name() const {
        Type t = type();
        return t ? t.raw_name() : "";
    }

    const char* Field::type_name() const {
        Type t = type();
        return t ? t.name() : "";
    }

    Type Field::type() const {
        if (!m_native) return Type{};
        // il2cppFieldInfo::m_pType is the second field (offset sizeof(void*))
        return Type{ *reinterpret_cast<void**>(static_cast<char*>(m_native) + sizeof(void*)) };
    }

    int Field::offset() const {
        if (!m_native) return -1;
        // il2cppFieldInfo::m_iOffset is at offset 3*sizeof(void*) (after name, type, parentClass)
        return *reinterpret_cast<int32_t*>(static_cast<char*>(m_native) + 3 * sizeof(void*));
    }

    uint32_t Field::attributes() const {
        if (!m_native) return 0;
        auto t = type();
        if (!t) return 0;
        void* typePtr = t.raw();
        if (!typePtr) return 0;
        // Attributes are at offset 0x8 in il2cppType
        return *reinterpret_cast<const uint16_t*>(static_cast<const char*>(typePtr) + 0x8);
    }

    bool Field::is_static() const {
        return (attributes() & FIELD_ATTRIBUTE_STATIC) != 0;
    }

    bool Field::is_public() const {
        return (attributes() & FIELD_ATTRIBUTE_ACCESS_MASK) == FIELD_ATTRIBUTE_PUBLIC;
    }

    bool Field::is_private() const {
        uint16_t access = attributes() & FIELD_ATTRIBUTE_ACCESS_MASK;
        return access == FIELD_ATTRIBUTE_PRIVATE || access == 0;  // PrivateScope == 0
    }

    bool Field::is_protected() const {
        uint16_t access = attributes() & FIELD_ATTRIBUTE_ACCESS_MASK;
        return access == FIELD_ATTRIBUTE_FAMILY || access == FIELD_ATTRIBUTE_FAM_OR_ASSEM;
    }

    bool Field::is_internal() const {
        uint16_t access = attributes() & FIELD_ATTRIBUTE_ACCESS_MASK;
        return access == FIELD_ATTRIBUTE_ASSEMBLY || access == FIELD_ATTRIBUTE_FAM_OR_ASSEM;
    }

    bool Field::is_readonly() const {
        return (attributes() & FIELD_ATTRIBUTE_INIT_ONLY) != 0;
    }

    bool Field::is_const() const {
        return (attributes() & FIELD_ATTRIBUTE_LITERAL) != 0;
    }

    const char* Field::access_modifier() const {
        uint16_t access = attributes() & FIELD_ATTRIBUTE_ACCESS_MASK;
        switch (access) {
            case FIELD_ATTRIBUTE_PUBLIC:        return "public";
            case FIELD_ATTRIBUTE_PRIVATE:       return "private";
            case FIELD_ATTRIBUTE_FAMILY:        return "protected";
            case FIELD_ATTRIBUTE_ASSEMBLY:      return "internal";
            case FIELD_ATTRIBUTE_FAM_OR_ASSEM:  return "protected internal";
            case FIELD_ATTRIBUTE_FAM_AND_ASSEM: return "private protected";
            default:                            return "private";  // PrivateScope
        }
    }

    void Field::get_value(void* obj, void* out_value) const {
        if (!m_native || !obj || !out_value || !E() || !E()->m_fieldGetValue) return;
        reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, void*, void*)>(E()->m_fieldGetValue)(obj, m_native, out_value);
    }

    void Field::set_value(void* obj, void* value) const {
        if (!m_native || !obj || !value || !E() || !E()->m_fieldSetValue) return;
        reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, void*, void*)>(E()->m_fieldSetValue)(obj, m_native, value);
    }

    void Field::get_static_value(void* out_value) const {
        if (!m_native || !out_value || !E() || !E()->m_fieldStaticGetValue) return;
        reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, void*)>(E()->m_fieldStaticGetValue)(m_native, out_value);
    }

    void Field::set_static_value(void* value) const {
        if (!m_native || !value || !E() || !E()->m_fieldStaticSetValue) return;
        reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, void*)>(E()->m_fieldStaticSetValue)(m_native, value);
    }

    bool Field::has_attribute(void* attr_class) const {
        if (!m_native || !attr_class || !E() || !E()->m_fieldHasAttribute) return false;
        return reinterpret_cast<bool(IL2CPP_CALLTYPE)(void*, void*)>(E()->m_fieldHasAttribute)(m_native, attr_class);
    }

    // ========================================================================
    //  Method
    // ========================================================================

    const char* Method::raw_name() const {
        if (!m_native) return "";
        // il2cppMethodInfo: m_pMethodPointer, [m_pVirtualMethodPointer], m_pInvokerMethod, m_pName
#ifdef UNITY_VERSION_2022_3_8_HIGHER
        return *reinterpret_cast<const char**>(static_cast<char*>(m_native) + 3 * sizeof(void*));
#else
        return *reinterpret_cast<const char**>(static_cast<char*>(m_native) + 2 * sizeof(void*));
#endif
    }

    const char* Method::name() const {
        const char* raw = raw_name();
        if (!raw || !*raw) return raw;

        // Get parent class pointer carefully
#ifdef UNITY_VERSION_2022_3_8_HIGHER
        void* parentClass = *reinterpret_cast<void**>(static_cast<char*>(m_native) + 4 * sizeof(void*));
#else
        void* parentClass = *reinterpret_cast<void**>(static_cast<char*>(m_native) + 3 * sizeof(void*));
#endif
        if (isValidPointer(parentClass)) {
            const char* rawClassName = *reinterpret_cast<const char**>(
                static_cast<char*>(parentClass) + 2 * sizeof(void*));

            if (isValidPointer(rawClassName)) {
                const char* resolved = resolve_member_name(rawClassName, raw);
                if (resolved) return resolved;
            }
        }

        return Deobfuscation::GetStableName(raw);
    }

    const char* Method::raw_return_type_name() const {
        Type t = return_type();
        return t ? t.raw_name() : "";
    }

    const char* Method::return_type_name() const {
        Type t = return_type();
        return t ? t.name() : "";
    }

    void* Method::pointer() const {
        if (!m_native) return nullptr;
        // m_pMethodPointer is the first field
        return *reinterpret_cast<void**>(m_native);
    }

    uint8_t Method::param_count() const {
        if (!m_native) return 0;
#ifdef UNITY_VERSION_2022_3_8_HIGHER
        constexpr size_t base = 9 * sizeof(void*);
#else
        constexpr size_t base = 8 * sizeof(void*);
#endif
        constexpr size_t offset = base + sizeof(uint32_t) + sizeof(uint16_t) + sizeof(uint16_t) + sizeof(uint16_t);
        return *reinterpret_cast<uint8_t*>(static_cast<char*>(m_native) + offset);
    }

    uint32_t Method::flags(uint32_t* impl_flags) const {
        if (!m_native || !E() || !E()->m_methodGetFlags) return 0;
        return reinterpret_cast<uint32_t(IL2CPP_CALLTYPE)(void*, uint32_t*)>(E()->m_methodGetFlags)(m_native, impl_flags);
    }

    bool Method::is_static() const {
        return (flags() & METHOD_ATTRIBUTE_STATIC) != 0;
    }

    bool Method::is_public() const {
        return (flags() & METHOD_ATTRIBUTE_ACCESS_MASK) == METHOD_ATTRIBUTE_PUBLIC;
    }

    bool Method::is_private() const {
        uint32_t access = flags() & METHOD_ATTRIBUTE_ACCESS_MASK;
        return access == METHOD_ATTRIBUTE_PRIVATE || access == 0;  // PrivateScope == 0
    }

    bool Method::is_protected() const {
        uint32_t access = flags() & METHOD_ATTRIBUTE_ACCESS_MASK;
        return access == METHOD_ATTRIBUTE_FAMILY || access == METHOD_ATTRIBUTE_FAM_OR_ASSEM;
    }

    bool Method::is_internal() const {
        uint32_t access = flags() & METHOD_ATTRIBUTE_ACCESS_MASK;
        return access == METHOD_ATTRIBUTE_ASSEMBLY || access == METHOD_ATTRIBUTE_FAM_OR_ASSEM;
    }

    bool Method::is_virtual() const {
        return (flags() & METHOD_ATTRIBUTE_VIRTUAL) != 0;
    }

    bool Method::is_abstract() const {
        return (flags() & METHOD_ATTRIBUTE_ABSTRACT) != 0;
    }

    bool Method::is_sealed() const {
        return (flags() & METHOD_ATTRIBUTE_FINAL) != 0;
    }

    const char* Method::access_modifier() const {
        uint32_t access = flags() & METHOD_ATTRIBUTE_ACCESS_MASK;
        switch (access) {
            case METHOD_ATTRIBUTE_PUBLIC:        return "public";
            case METHOD_ATTRIBUTE_PRIVATE:       return "private";
            case METHOD_ATTRIBUTE_FAMILY:        return "protected";
            case METHOD_ATTRIBUTE_ASSEMBLY:      return "internal";
            case METHOD_ATTRIBUTE_FAM_OR_ASSEM:  return "protected internal";
            case METHOD_ATTRIBUTE_FAM_AND_ASSEM: return "private protected";
            default:                             return "private";  // PrivateScope
        }
    }

    Type Method::get_param_type(uint32_t index) const {
        if (!m_native || !E() || !E()->m_methodGetParam) return Type{};
        return Type{ reinterpret_cast<void*(IL2CPP_CALLTYPE)(void*, uint32_t)>(E()->m_methodGetParam)(m_native, index) };
    }

    const char* Method::get_param_name(uint32_t index) const {
        if (!m_native || !E() || !E()->m_methodGetParamName) return "";
        return reinterpret_cast<const char*(IL2CPP_CALLTYPE)(void*, uint32_t)>(E()->m_methodGetParamName)(m_native, index);
    }

    Type Method::return_type() const {
        if (!m_native) return Type{};
        
        // Use Core's helper for safer access
        if (E() && E()->m_helperGetMethodReturnType) {
            void* retType = reinterpret_cast<void*(IL2CPP_CALLTYPE)(void*)>(
                E()->m_helperGetMethodReturnType)(m_native);
            // Validate the returned pointer
            if (isValidPointer(retType)) {
                return Type{ retType };
            }
            return Type{};  // Return empty type if pointer is invalid
        }

        // Fallback to direct access (with validation)
        void* retType = nullptr;
#ifdef UNITY_VERSION_2022_3_8_HIGHER
        retType = *reinterpret_cast<void**>(static_cast<char*>(m_native) + 5 * sizeof(void*));
#else
        retType = *reinterpret_cast<void**>(static_cast<char*>(m_native) + 4 * sizeof(void*));
#endif
        return isValidPointer(retType) ? Type{ retType } : Type{};
    }

    void* Method::invoke(void* obj, void** params, void** exc) const {
        if (!m_native || !E() || !E()->m_runtimeInvoke) return nullptr;
        return reinterpret_cast<void*(IL2CPP_CALLTYPE)(void*, void*, void**, void**)>(
            E()->m_runtimeInvoke)(m_native, obj, params, exc);
    }

    bool Method::has_attribute(void* attr_class) const {
        if (!m_native || !attr_class || !E() || !E()->m_methodHasAttribute) return false;
        return reinterpret_cast<bool(IL2CPP_CALLTYPE)(void*, void*)>(E()->m_methodHasAttribute)(m_native, attr_class);
    }

    // ========================================================================
    //  Property
    // ========================================================================

    const char* Property::raw_name() const {
        if (!m_native) return "";
        // il2cppPropertyInfo: m_pParentClass, m_pName, m_pGet, m_pSet, ...
        return *reinterpret_cast<const char**>(static_cast<char*>(m_native) + sizeof(void*));
    }

    const char* Property::name() const {
        const char* raw = raw_name();
        if (!raw || !*raw) return raw;

        // Get parent class for qualified lookup (with pointer validation)
        void* parentClass = *reinterpret_cast<void**>(m_native);
        if (isValidPointer(parentClass)) {
            const char* rawClassName = *reinterpret_cast<const char**>(
                static_cast<char*>(parentClass) + 2 * sizeof(void*));
            if (isValidPointer(rawClassName)) {
                const char* resolved = resolve_member_name(rawClassName, raw);
                if (resolved) return resolved;
            }
        }

        return Deobfuscation::GetStableName(raw);
    }

    const char* Property::raw_type_name() const {
        Method g = getter();
        if (g) {
            return g.raw_return_type_name();
        }
        // Fallback to setter's first param type
        Method s = setter();
        if (s && s.param_count() > 0) {
            Type paramType = s.get_param_type(0);
            return paramType ? paramType.raw_name() : "";
        }
        return "";
    }

    const char* Property::type_name() const {
        Method g = getter();
        if (g) {
            return g.return_type_name();
        }
        // Fallback to setter's first param type
        Method s = setter();
        if (s && s.param_count() > 0) {
            Type paramType = s.get_param_type(0);
            return paramType ? paramType.name() : "";
        }
        return "";
    }

    Method Property::getter() const {
        if (!m_native) return Method{};
        return Method{ *reinterpret_cast<void**>(static_cast<char*>(m_native) + 2 * sizeof(void*)) };
    }

    Method Property::setter() const {
        if (!m_native) return Method{};
        return Method{ *reinterpret_cast<void**>(static_cast<char*>(m_native) + 3 * sizeof(void*)) };
    }

    void* Property::parent_class_raw() const {
        if (!m_native) return nullptr;
        return *reinterpret_cast<void**>(m_native);
    }

    bool Property::is_public() const {
        Method g = getter();
        Method s = setter();
        return (g && g.is_public()) || (s && s.is_public());
    }

    bool Property::is_private() const {
        Method g = getter();
        Method s = setter();
        // Private if both accessors are private (or don't exist)
        bool getterPrivate = !g || g.is_private();
        bool setterPrivate = !s || s.is_private();
        return getterPrivate && setterPrivate && (g || s);  // Must have at least one accessor
    }

    bool Property::is_readonly() const {
        return getter() && !setter();
    }

    bool Property::is_writeonly() const {
        return setter() && !getter();
    }

    const char* Property::access_modifier() const {
        Method g = getter();
        Method s = setter();
        // Use the most accessible modifier from getter/setter
        if ((g && g.is_public()) || (s && s.is_public())) return "public";
        if ((g && g.is_protected()) || (s && s.is_protected())) return "protected";
        if ((g && g.is_internal()) || (s && s.is_internal())) return "internal";
        return "private";
    }

    // ========================================================================
    //  Class
    // ========================================================================

    const char* Class::raw_name() const {
        if (!m_native) return "";
        // il2cppClass::m_pName is the third field (after m_pImage, m_pGC)
        return *reinterpret_cast<const char**>(static_cast<char*>(m_native) + 2 * sizeof(void*));
    }

    const char* Class::name() const {
        if (!m_native) return "";
        
        // Use Core's helper which can generate stable names on-demand
        if (E() && E()->m_helperGetClassStableName) {
            const char* result = reinterpret_cast<const char*(IL2CPP_CALLTYPE)(void*)>(
                E()->m_helperGetClassStableName)(m_native);
            if (result && *result) return result;
        }

        // Fallback: return raw name
        return raw_name();
    }

    const char* Class::raw_ns() const {
        if (!m_native) return "";
        // il2cppClass::m_pNamespace is the fourth field
        return *reinterpret_cast<const char**>(static_cast<char*>(m_native) + 3 * sizeof(void*));
    }

    const char* Class::ns() const {
        if (!m_native) return "";
        
        // Use Core's helper for stable namespace
        if (E() && E()->m_helperGetClassStableNamespace) {
            const char* result = reinterpret_cast<const char*(IL2CPP_CALLTYPE)(void*)>(
                E()->m_helperGetClassStableNamespace)(m_native);
            if (result) return result;
        }

        // Fallback: try deobfuscating raw namespace
        const char* raw = raw_ns();
        if (!raw || !*raw) return raw;
        return Deobfuscation::GetStableName(raw);
    }

    std::string Class::full_name() const {
        if (!m_native) return "";
        
        // Use Core's helper for stable full name (returns persistent pointer)
        if (E() && E()->m_helperGetClassStableFullName) {
            const char* result = reinterpret_cast<const char*(IL2CPP_CALLTYPE)(void*)>(
                E()->m_helperGetClassStableFullName)(m_native);
            if (result && *result) return result;
        }

        // Fallback: concatenate ns + name
        const char* n = ns();
        const char* c = name();
        if (n && n[0]) return std::string(n) + "." + c;
        return c ? c : "";
    }

    std::string Class::raw_full_name() const {
        if (!m_native) return "";
        const char* n = raw_ns();
        const char* c = raw_name();
        if (n && n[0]) return std::string(n) + "." + c;
        return c ? c : "";
    }

    Class Class::parent() const {
        if (!m_native || !E() || !E()->m_classGetParent) return Class{};
        return Class{ reinterpret_cast<void*(IL2CPP_CALLTYPE)(void*)>(E()->m_classGetParent)(m_native) };
    }

    Type Class::get_type() const {
        if (!m_native || !E() || !E()->m_classGetType) return Type{};
        return Type{ reinterpret_cast<void*(IL2CPP_CALLTYPE)(void*)>(E()->m_classGetType)(m_native) };
    }

    bool Class::is_subclass_of(const Class& other) const {
        if (!m_native || !other.m_native || !E() || !E()->m_classIsSubclassOf) return false;
        return reinterpret_cast<bool(IL2CPP_CALLTYPE)(void*, void*)>(E()->m_classIsSubclassOf)(m_native, other.m_native);
    }

    bool Class::is_enum() const {
        if (!m_native || !E() || !E()->m_classIsEnum) return false;
        return reinterpret_cast<bool(IL2CPP_CALLTYPE)(void*)>(E()->m_classIsEnum)(m_native);
    }

    bool Class::is_generic() const {
        if (!m_native || !E() || !E()->m_classIsGeneric) return false;
        return reinterpret_cast<bool(IL2CPP_CALLTYPE)(void*)>(E()->m_classIsGeneric)(m_native);
    }

    bool Class::has_attribute(void* attr_class) const {
        if (!m_native || !attr_class || !E() || !E()->m_classHasAttribute) return false;
        return reinterpret_cast<bool(IL2CPP_CALLTYPE)(void*, void*)>(E()->m_classHasAttribute)(m_native, attr_class);
    }

    uint32_t Class::instance_size() const {
        if (!m_native) return 0;
        constexpr size_t offset = 22 * sizeof(void*);
        return *reinterpret_cast<uint32_t*>(static_cast<char*>(m_native) + offset);
    }

    void* Class::static_field_data() const {
        if (!m_native || !E() || !E()->m_classGetStaticFieldData) return nullptr;
        return reinterpret_cast<void*(IL2CPP_CALLTYPE)(void*)>(E()->m_classGetStaticFieldData)(m_native);
    }

    Field Class::get_field(std::string_view fname) const {
        if (!m_native || !E() || !E()->m_classGetFieldFromName) return Field{};

        std::string nameStr(fname);
        void* result = reinterpret_cast<void*(IL2CPP_CALLTYPE)(void*, const char*)>(
            E()->m_classGetFieldFromName)(m_native, nameStr.c_str());
        if (result) return Field{ result };

        // Try unqualified reverse lookup
        const char* original = Deobfuscation::GetOriginalName(nameStr.c_str());
        if (original && original != nameStr.c_str() && std::strcmp(original, nameStr.c_str()) != 0) {
            result = reinterpret_cast<void*(IL2CPP_CALLTYPE)(void*, const char*)>(
                E()->m_classGetFieldFromName)(m_native, original);
            if (result) return Field{ result };
        }

        // Try qualified reverse lookup using stable class name (member mappings key off stable, not human names)
        std::string rawFull = raw_full_name();
        const char* stableName = Deobfuscation::GetStableName(rawFull.c_str());
        std::string qualifiedKey = build_member_key(stableName, nameStr.c_str());
        original = Deobfuscation::GetOriginalName(qualifiedKey.c_str());
        if (original && original != qualifiedKey.c_str() && std::strcmp(original, qualifiedKey.c_str()) != 0) {
            result = reinterpret_cast<void*(IL2CPP_CALLTYPE)(void*, const char*)>(
                E()->m_classGetFieldFromName)(m_native, extract_member_name(original));
        }

        return Field{ result };
    }

    std::vector<Field> Class::get_fields() const {
        std::vector<Field> result;
        if (!m_native || !E() || !E()->m_classGetFields) return result;
        void* iter = nullptr;
        while (auto* f = reinterpret_cast<void*(IL2CPP_CALLTYPE)(void*, void**)>(
            E()->m_classGetFields)(m_native, &iter)) {
            result.emplace_back(f);
        }
        return result;
    }

    Method Class::get_method(std::string_view mname, int argc) const {
        if (!m_native || !E() || !E()->m_classGetMethodFromName) return Method{};

        std::string nameStr(mname);
        void* result = reinterpret_cast<void*(IL2CPP_CALLTYPE)(void*, const char*, int)>(
            E()->m_classGetMethodFromName)(m_native, nameStr.c_str(), argc);
        if (result) return Method{ result };

        // Try unqualified reverse lookup
        const char* original = Deobfuscation::GetOriginalName(nameStr.c_str());
        if (original && original != nameStr.c_str() && std::strcmp(original, nameStr.c_str()) != 0) {
            result = reinterpret_cast<void*(IL2CPP_CALLTYPE)(void*, const char*, int)>(
                E()->m_classGetMethodFromName)(m_native, original, argc);
            if (result) return Method{ result };
        }

        // Try qualified reverse lookup using stable class name (member mappings key off stable, not human names)
        std::string rawFull = raw_full_name();
        const char* stableName = Deobfuscation::GetStableName(rawFull.c_str());
        std::string qualifiedKey = build_member_key(stableName, nameStr.c_str());
        original = Deobfuscation::GetOriginalName(qualifiedKey.c_str());
        if (original && original != qualifiedKey.c_str() && std::strcmp(original, qualifiedKey.c_str()) != 0) {
            result = reinterpret_cast<void*(IL2CPP_CALLTYPE)(void*, const char*, int)>(
                E()->m_classGetMethodFromName)(m_native, extract_member_name(original), argc);
        }

        return Method{ result };
    }

    void* Class::get_method_pointer(std::string_view mname, int argc) const {
        auto m = get_method(mname, argc);
        return m ? m.pointer() : nullptr;
    }

    std::vector<Method> Class::get_methods() const {
        std::vector<Method> result;
        if (!m_native || !E() || !E()->m_classGetMethods) return result;
        void* iter = nullptr;
        while (auto* m = reinterpret_cast<void*(IL2CPP_CALLTYPE)(void*, void**)>(
            E()->m_classGetMethods)(m_native, &iter)) {
            result.emplace_back(m);
        }
        return result;
    }

    Property Class::get_property(std::string_view pname) const {
        if (!m_native || !E() || !E()->m_classGetPropertyFromName) return Property{};

        std::string nameStr(pname);
        void* result = reinterpret_cast<void*(IL2CPP_CALLTYPE)(void*, const char*)>(
            E()->m_classGetPropertyFromName)(m_native, nameStr.c_str());
        if (result) return Property{ result };

        // Try unqualified reverse lookup
        const char* original = Deobfuscation::GetOriginalName(nameStr.c_str());
        if (original && original != nameStr.c_str() && std::strcmp(original, nameStr.c_str()) != 0) {
            result = reinterpret_cast<void*(IL2CPP_CALLTYPE)(void*, const char*)>(
                E()->m_classGetPropertyFromName)(m_native, original);
            if (result) return Property{ result };
        }

        // Try qualified reverse lookup using stable class name (member mappings key off stable, not human names)
        std::string rawFull = raw_full_name();
        const char* stableName = Deobfuscation::GetStableName(rawFull.c_str());
        std::string qualifiedKey = build_member_key(stableName, nameStr.c_str());
        original = Deobfuscation::GetOriginalName(qualifiedKey.c_str());
        if (original && original != qualifiedKey.c_str() && std::strcmp(original, qualifiedKey.c_str()) != 0) {
            result = reinterpret_cast<void*(IL2CPP_CALLTYPE)(void*, const char*)>(
                E()->m_classGetPropertyFromName)(m_native, extract_member_name(original));
        }

        return Property{ result };
    }

    std::vector<Property> Class::get_properties() const {
        std::vector<Property> result;
        if (!m_native || !E() || !E()->m_classGetProperties) return result;
        void* iter = nullptr;
        while (auto* p = reinterpret_cast<void*(IL2CPP_CALLTYPE)(void*, void**)>(
            E()->m_classGetProperties)(m_native, &iter)) {
            result.emplace_back(p);
        }
        return result;
    }

    Class Class::find(std::string_view full_name) {
        if (!E() || !E()->m_helperFindClass) return Class{};

        std::string nameStr(full_name);
        void* result = reinterpret_cast<void*(IL2CPP_CALLTYPE)(const char*)>(
            E()->m_helperFindClass)(nameStr.c_str());
        if (result) return Class{ result };

        // Try original obfuscated name
        const char* original = Deobfuscation::GetOriginalName(nameStr.c_str());
        if (original && original != nameStr.c_str() && std::strcmp(original, nameStr.c_str()) != 0) {
            result = reinterpret_cast<void*(IL2CPP_CALLTYPE)(const char*)>(
                E()->m_helperFindClass)(original);
        }

        return Class{ result };
    }

    ManagedObject Class::new_object() const {
        if (!m_native || !E() || !E()->m_objectNew) return ManagedObject{};
        return ManagedObject{ reinterpret_cast<void*(IL2CPP_CALLTYPE)(void*)>(E()->m_objectNew)(m_native) };
    }

    // ========================================================================
    //  Image
    // ========================================================================

    const char* Image::name() const {
        if (!m_native) return "";
        // il2cppImage::m_pName is the first field
        return *reinterpret_cast<const char**>(m_native);
    }

    uint32_t Image::class_count() const {
        if (!m_native || !E() || !E()->m_imageGetClassCount) return 0;
        return reinterpret_cast<uint32_t(IL2CPP_CALLTYPE)(void*)>(E()->m_imageGetClassCount)(m_native);
    }

    Class Image::get_class(uint32_t index) const {
        if (!m_native || !E() || !E()->m_imageGetClass) return Class{};
        return Class{ reinterpret_cast<void*(IL2CPP_CALLTYPE)(void*, uint32_t)>(
            E()->m_imageGetClass)(m_native, index) };
    }

    std::vector<Class> Image::get_classes() const {
        std::vector<Class> result;
        uint32_t count = class_count();
        result.reserve(count);
        for (uint32_t i = 0; i < count; ++i) {
            auto klass = get_class(i);
            if (klass) result.push_back(klass);
        }
        return result;
    }

    // ========================================================================
    //  Assembly
    // ========================================================================

    Image Assembly::get_image() const {
        if (!m_native) return Image{};
        // il2cppAssembly::m_pImage is typically at offset 0
        // But let's use the API if available
        if (E() && E()->m_assemblyGetImage) {
            return Image{ reinterpret_cast<void*(IL2CPP_CALLTYPE)(void*)>(
                E()->m_assemblyGetImage)(m_native) };
        }
        // Fallback: direct struct access
        return Image{ *reinterpret_cast<void**>(m_native) };
    }

    std::vector<Assembly> Assembly::get_all() {
        std::vector<Assembly> result;
        if (!E() || !E()->m_domainGetAssemblies) return result;

        // Get current domain first
        void* domain = nullptr;
        if (E()->m_domainGet) {
            domain = reinterpret_cast<void*(IL2CPP_CALLTYPE)()>(E()->m_domainGet)();
        }
        if (!domain) return result;

        // Get assembly count and array
        size_t count = 0;
        void** assemblies = reinterpret_cast<void**(IL2CPP_CALLTYPE)(void*, size_t*)>(
            E()->m_domainGetAssemblies)(domain, &count);

        if (!assemblies || count == 0) return result;

        result.reserve(count);
        for (size_t i = 0; i < count; ++i) {
            if (assemblies[i]) {
                result.emplace_back(assemblies[i]);
            }
        }

        return result;
    }

} // namespace IL2CPP::Module
