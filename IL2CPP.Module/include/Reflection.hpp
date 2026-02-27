#pragma once
#include <IL2CPP.Common/il2cpp_shared.hpp>
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

namespace IL2CPP::Module {

    // Forward declarations
    class Field;
    class Method;
    class Property;
    class Type;
    class ManagedObject;
    class Assembly;
    class Image;

    // ========================================================================
    //  Type
    // ========================================================================

    class Class;  // Forward decl for Type::get_class()

    class Type {
        void* m_native = nullptr;
    public:
        explicit Type(void* raw = nullptr) : m_native(raw) {}

        /// Get the raw il2cppType* pointer.
        [[nodiscard]] void* raw() const noexcept { return m_native; }

        /// Check if this handle is valid.
        [[nodiscard]] operator bool() const noexcept { return m_native != nullptr; }

        /// Get the deobfuscated type name (uses underlying class name if available).
        [[nodiscard]] const char* name() const;

        /// Get the raw (potentially obfuscated) type name.
        [[nodiscard]] const char* raw_name() const;

        /// Get the deobfuscated namespace for this type.
        [[nodiscard]] const char* ns() const;

        /// Get the raw (potentially obfuscated) namespace.
        [[nodiscard]] const char* raw_ns() const;

        /// Get the deobfuscated full name (namespace.name) for this type.
        [[nodiscard]] std::string full_name() const;

        /// Get the raw full name (namespace.name) - may be obfuscated.
        [[nodiscard]] std::string raw_full_name() const;

        /// Get the underlying class for this type (if it's a class type).
        [[nodiscard]] Class get_class() const;

        /// Get the type enum value (IL2CPP type ID).
        [[nodiscard]] int type_enum() const;

        /// Check if this type is a by-reference type.
        [[nodiscard]] bool is_byref() const;

        /// Get the assembly-qualified name.
        [[nodiscard]] const char* assembly_qualified_name() const;

        /// Get the System.Type reflection object for this type.
        [[nodiscard]] void* get_system_type_object() const;
    };

    // ========================================================================
    //  Field
    // ========================================================================

    class Field {
        void* m_native = nullptr;  // il2cppFieldInfo*
    public:
        explicit Field(void* raw = nullptr) : m_native(raw) {}

        /// Get the raw il2cppFieldInfo* pointer.
        [[nodiscard]] void* raw() const noexcept { return m_native; }

        /// Check if this handle is valid.
        [[nodiscard]] operator bool() const noexcept { return m_native != nullptr; }

        /// Get the deobfuscated field name.
        [[nodiscard]] const char* name() const;

        /// Get the raw (potentially obfuscated) field name.
        [[nodiscard]] const char* raw_name() const;

        /// Get the deobfuscated type name.
        [[nodiscard]] const char* type_name() const;

        /// Get the raw (potentially obfuscated) type name.
        [[nodiscard]] const char* raw_type_name() const;

        /// Get the field type.
        [[nodiscard]] Type type() const;

        /// Get the field offset from the object base.
        [[nodiscard]] int offset() const;

        /// Get the raw field attributes flags.
        [[nodiscard]] uint32_t attributes() const;

        // ----- Access modifier queries -----

        /// Check if this is a static field.
        [[nodiscard]] bool is_static() const;

        /// Check if this is a public field.
        [[nodiscard]] bool is_public() const;

        /// Check if this is a private field.
        [[nodiscard]] bool is_private() const;

        /// Check if this is a protected field.
        [[nodiscard]] bool is_protected() const;

        /// Check if this is an internal field.
        [[nodiscard]] bool is_internal() const;

        /// Check if this is a readonly (initonly) field.
        [[nodiscard]] bool is_readonly() const;

        /// Check if this is a const (literal) field.
        [[nodiscard]] bool is_const() const;

        /// Get a human-readable access modifier string ("public", "private", etc.)
        [[nodiscard]] const char* access_modifier() const;

        // ----- Value access -----

        /// Get an instance field value from an object.
        void get_value(void* obj, void* out_value) const;

        /// Set an instance field value on an object.
        void set_value(void* obj, void* value) const;

        /// Get a static field value.
        void get_static_value(void* out_value) const;

        /// Set a static field value.
        void set_static_value(void* value) const;

        /// Check if the field has a specific attribute.
        [[nodiscard]] bool has_attribute(void* attr_class) const;
    };

    // ========================================================================
    //  Method
    // ========================================================================

    class Method {
        void* m_native = nullptr;  // il2cppMethodInfo*
    public:
        explicit Method(void* raw = nullptr) : m_native(raw) {}

        /// Get the raw il2cppMethodInfo* pointer.
        [[nodiscard]] void* raw() const noexcept { return m_native; }

        /// Check if this handle is valid.
        [[nodiscard]] operator bool() const noexcept { return m_native != nullptr; }

        /// Get the deobfuscated method name.
        [[nodiscard]] const char* name() const;

        /// Get the raw (potentially obfuscated) method name.
        [[nodiscard]] const char* raw_name() const;

        /// Get the deobfuscated return type name.
        [[nodiscard]] const char* return_type_name() const;

        /// Get the raw (potentially obfuscated) return type name.
        [[nodiscard]] const char* raw_return_type_name() const;

        /// Get the direct function pointer (for hooking/calling).
        [[nodiscard]] void* pointer() const;

        /// Get the number of parameters.
        [[nodiscard]] uint8_t param_count() const;

        /// Get method flags.
        [[nodiscard]] uint32_t flags(uint32_t* impl_flags = nullptr) const;

        // ----- Access modifier queries -----

        /// Check if this is a static method.
        [[nodiscard]] bool is_static() const;

        /// Check if this is a public method.
        [[nodiscard]] bool is_public() const;

        /// Check if this is a private method.
        [[nodiscard]] bool is_private() const;

        /// Check if this is a protected method.
        [[nodiscard]] bool is_protected() const;

        /// Check if this is an internal method.
        [[nodiscard]] bool is_internal() const;

        /// Check if this is a virtual method.
        [[nodiscard]] bool is_virtual() const;

        /// Check if this is an abstract method.
        [[nodiscard]] bool is_abstract() const;

        /// Check if this is a sealed (final) method.
        [[nodiscard]] bool is_sealed() const;

        /// Get a human-readable access modifier string ("public", "private", etc.)
        [[nodiscard]] const char* access_modifier() const;

        // ----- Parameters & return -----

        /// Get parameter type by index.
        [[nodiscard]] Type get_param_type(uint32_t index) const;

        /// Get parameter name by index.
        [[nodiscard]] const char* get_param_name(uint32_t index) const;

        /// Get the return type.
        [[nodiscard]] Type return_type() const;

        /// Invoke this method on an object with the given parameters.
        /// Returns the result as a raw il2cppObject*.
        void* invoke(void* obj, void** params, void** exc = nullptr) const;

        /// Check if the method has a specific attribute.
        [[nodiscard]] bool has_attribute(void* attr_class) const;
    };

    // ========================================================================
    //  Property
    // ========================================================================

    class Property {
        void* m_native = nullptr;  // il2cppPropertyInfo*
    public:
        explicit Property(void* raw = nullptr) : m_native(raw) {}

        /// Get the raw il2cppPropertyInfo* pointer.
        [[nodiscard]] void* raw() const noexcept { return m_native; }

        /// Check if this handle is valid.
        [[nodiscard]] operator bool() const noexcept { return m_native != nullptr; }

        /// Get the deobfuscated property name.
        [[nodiscard]] const char* name() const;

        /// Get the raw (potentially obfuscated) property name.
        [[nodiscard]] const char* raw_name() const;

        /// Get the deobfuscated property type name (from getter return type).
        [[nodiscard]] const char* type_name() const;

        /// Get the raw (potentially obfuscated) property type name.
        [[nodiscard]] const char* raw_type_name() const;

        /// Get the getter method (may be null).
        [[nodiscard]] Method getter() const;

        /// Get the setter method (may be null).
        [[nodiscard]] Method setter() const;

        /// Get the parent class.
        [[nodiscard]] void* parent_class_raw() const;

        // ----- Access modifier queries (derived from getter/setter) -----

        /// Check if this property is public (getter or setter is public).
        [[nodiscard]] bool is_public() const;

        /// Check if this property is private.
        [[nodiscard]] bool is_private() const;

        /// Check if this property is read-only (has getter but no setter).
        [[nodiscard]] bool is_readonly() const;

        /// Check if this property is write-only (has setter but no getter).
        [[nodiscard]] bool is_writeonly() const;

        /// Get a human-readable access modifier string.
        [[nodiscard]] const char* access_modifier() const;
    };

    // ========================================================================
    //  Class
    // ========================================================================

    class Class {
        void* m_native = nullptr;  // il2cppClass*
    public:
        explicit Class(void* raw = nullptr) : m_native(raw) {}

        /// Get the raw il2cppClass* pointer.
        [[nodiscard]] void* raw() const noexcept { return m_native; }

        /// Check if this handle is valid.
        [[nodiscard]] operator bool() const noexcept { return m_native != nullptr; }

        /// Get the deobfuscated class name.
        [[nodiscard]] const char* name() const;

        /// Get the raw (potentially obfuscated) class name.
        [[nodiscard]] const char* raw_name() const;

        /// Get the deobfuscated namespace.
        [[nodiscard]] const char* ns() const;

        /// Get the raw (potentially obfuscated) namespace.
        [[nodiscard]] const char* raw_ns() const;

        /// Get deobfuscated full name (namespace.name).
        [[nodiscard]] std::string full_name() const;

        /// Get raw full name (namespace.name) - may be obfuscated.
        [[nodiscard]] std::string raw_full_name() const;

        /// Get the parent class.
        [[nodiscard]] Class parent() const;

        /// Get the type for this class.
        [[nodiscard]] Type get_type() const;

        /// Check if this class is a subclass of `parent`.
        [[nodiscard]] bool is_subclass_of(const Class& parent) const;

        /// Check if this is an enum type.
        [[nodiscard]] bool is_enum() const;

        /// Check if this is a generic type.
        [[nodiscard]] bool is_generic() const;

        /// Check if this class has a specific attribute.
        [[nodiscard]] bool has_attribute(void* attr_class) const;

        /// Get the instance size.
        [[nodiscard]] uint32_t instance_size() const;

        /// Get a static field data pointer.
        [[nodiscard]] void* static_field_data() const;

        // ---- Field access ----

        /// Get a field by name (searches by deobfuscated name first, then raw name).
        [[nodiscard]] Field get_field(std::string_view name) const;

        /// Get all fields.
        [[nodiscard]] std::vector<Field> get_fields() const;

        // ---- Method access ----

        /// Get a method by name and optional argument count (-1 = any).
        /// Searches by deobfuscated name first, then raw name.
        [[nodiscard]] Method get_method(std::string_view name, int argc = -1) const;

        /// Get the direct function pointer for a method.
        [[nodiscard]] void* get_method_pointer(std::string_view name, int argc = -1) const;

        /// Get all methods.
        [[nodiscard]] std::vector<Method> get_methods() const;

        // ---- Property access ----

        /// Get a property by name (searches by deobfuscated name first, then raw name).
        [[nodiscard]] Property get_property(std::string_view name) const;

        /// Get all properties.
        [[nodiscard]] std::vector<Property> get_properties() const;

        // ---- Static factory ----

        /// Find a class by full name (e.g. "UnityEngine.GameObject").
        /// Supports both deobfuscated and raw names.
        [[nodiscard]] static Class find(std::string_view full_name);

        /// Allocate a new managed object of this class.
        [[nodiscard]] ManagedObject new_object() const;
    };

    // ========================================================================
    //  Image (Assembly module)
    // ========================================================================

    class Image {
        void* m_native = nullptr;  // il2cppImage*
    public:
        explicit Image(void* raw = nullptr) : m_native(raw) {}

        /// Get the raw il2cppImage* pointer.
        [[nodiscard]] void* raw() const noexcept { return m_native; }

        /// Check if this handle is valid.
        [[nodiscard]] operator bool() const noexcept { return m_native != nullptr; }

        /// Get the image name (e.g., "Assembly-CSharp").
        [[nodiscard]] const char* name() const;

        /// Get the number of classes in this image.
        [[nodiscard]] uint32_t class_count() const;

        /// Get a class by index.
        [[nodiscard]] Class get_class(uint32_t index) const;

        /// Get all classes in this image (wrapped handles with deobfuscation).
        [[nodiscard]] std::vector<Class> get_classes() const;
    };

    // ========================================================================
    //  Assembly
    // ========================================================================

    class Assembly {
        void* m_native = nullptr;  // il2cppAssembly*
    public:
        explicit Assembly(void* raw = nullptr) : m_native(raw) {}

        /// Get the raw il2cppAssembly* pointer.
        [[nodiscard]] void* raw() const noexcept { return m_native; }

        /// Check if this handle is valid.
        [[nodiscard]] operator bool() const noexcept { return m_native != nullptr; }

        /// Get the image (module) for this assembly.
        [[nodiscard]] Image get_image() const;

        /// Get all loaded assemblies (wrapped handles).
        [[nodiscard]] static std::vector<Assembly> get_all();
    };

} // namespace IL2CPP::Module
