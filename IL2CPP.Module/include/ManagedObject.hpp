#pragma once
#include "Reflection.hpp"
#include <IL2CPP.Common/il2cpp_structs.hpp>
#include <IL2CPP.Common/il2cpp_shared.hpp>
#include <cstdint>
#include <string>
#include <string_view>

// ============================================================================
//  IL2CPP.Module - ManagedObject
//
//  High-level wrapper around il2cppObject*. Provides type-safe, template-based
//  field/method/property access. All Unity and .NET wrapper classes derive
//  from this. Use raw() to get the underlying pointer for low-level usage.
// ============================================================================

namespace IL2CPP::Module {

    class ManagedObject {
    protected:
        void* m_native = nullptr;  // il2cppObject*

    public:
        ManagedObject() = default;
        explicit ManagedObject(void* raw) : m_native(raw) {}

        // ---- Raw access ----

        /// Get the raw il2cppObject* pointer.
        [[nodiscard]] void* raw() const noexcept { return m_native; }

        /// Implicit bool conversion - check if the object is valid.
        [[nodiscard]] operator bool() const noexcept { return valid(); }

        /// Check if the underlying pointer is a valid managed object.
        [[nodiscard]] bool valid() const noexcept;

        /// Get the class handle for this object.
        [[nodiscard]] Class get_class() const;

        // ---- Reflection-based field access ----

        template<typename T>
        [[nodiscard]] T get_field(int fieldOffset) const {
            if (!valid()) return T{};
            return *reinterpret_cast<T*>(static_cast<char*>(m_native) + fieldOffset);
        }

        /// Get a field value by name. Returns default T{} if not found.
        template<typename T>
        [[nodiscard]] T get_field(std::string_view name) const {
            if (!valid()) return T{};
            Class klass = get_class();
            if (!klass) return T{};
            Field f = klass.get_field(name);
            if (!f) return T{};
            int off = f.offset();
            if (off >= 0) {
                return *reinterpret_cast<T*>(static_cast<char*>(m_native) + off);
            }
            return T{};
        }

        /// Set a field value by name.
        template<typename T>
        void set_field(std::string_view name, T value) {
            if (!valid()) return;
            Class klass = get_class();
            if (!klass) return;
            Field f = klass.get_field(name);
            if (!f) return;
            int off = f.offset();
            if (off >= 0) {
                *reinterpret_cast<T*>(static_cast<char*>(m_native) + off) = value;
            }
        }

        /// Get a property value by name (calls the getter).
        template<typename T>
        [[nodiscard]] T get_property(std::string_view name) const {
            if (!valid()) return T{};
            Class klass = get_class();
            if (!klass) return T{};
            Property prop = klass.get_property(name);
            if (!prop) return T{};
            Method getter = prop.getter();
            if (!getter) return T{};
            void* result = getter.invoke(m_native, nullptr);
            if (!result) return T{};
            if constexpr (std::is_pointer_v<T>) {
                return reinterpret_cast<T>(result);
            } else {
                return *reinterpret_cast<T*>(IL2CPP::Unbox(result));
            }
        }

        /// Set a property value by name (calls the setter).
        template<typename T>
        void set_property(std::string_view name, T value) {
            if (!valid()) return;
            Class klass = get_class();
            if (!klass) return;
            Property prop = klass.get_property(name);
            if (!prop) return;
            Method setter = prop.setter();
            if (!setter) return;
            void* params[1];
            if constexpr (std::is_pointer_v<T>) {
                params[0] = reinterpret_cast<void*>(value);
            } else {
                params[0] = &value;
            }
            setter.invoke(m_native, params);
        }

        // ---- Direct offset access (low-level escape hatch) ----

        /// Read a value at a raw offset from the object base.
        template<typename T>
        [[nodiscard]] T read(int offset) const {
            if (!m_native || offset < 0) return T{};
            return *reinterpret_cast<T*>(static_cast<char*>(m_native) + offset);
        }

        /// Write a value at a raw offset from the object base.
        template<typename T>
        void write(int offset, T value) {
            if (!m_native || offset < 0) return;
            *reinterpret_cast<T*>(static_cast<char*>(m_native) + offset) = value;
        }

        /// Get a typed pointer at a raw offset from the object base.
        template<typename T = void*>
        [[nodiscard]] T* ptr_at(int offset) const {
            if (!m_native || offset < 0) return nullptr;
            return reinterpret_cast<T*>(static_cast<char*>(m_native) + offset);
        }

        // ---- Method invocation ----

        /// Call a method by name with typed return. Uses runtime invoke.
        template<typename TReturn>
        TReturn call_method(std::string_view name, void** params = nullptr, int argc = -1) const {
            if constexpr (std::is_void_v<TReturn>) {
                if (!valid()) return;
                Class klass = get_class();
                if (!klass) return;
                Method m = klass.get_method(name, argc);
                if (!m) return;
                m.invoke(m_native, params);
            }
            else {
                if (!valid()) return TReturn{};
                Class klass = get_class();
                if (!klass) return TReturn{};
                Method m = klass.get_method(name, argc);
                if (!m) return TReturn{};
                void* result = m.invoke(m_native, params);
                if (!result) return TReturn{};
                if constexpr (std::is_pointer_v<TReturn>) {
                    return reinterpret_cast<TReturn>(result);
                }
                else {
                    return *reinterpret_cast<TReturn*>(IL2CPP::Unbox(result));
                }
            }
        }

        /// Get a direct function pointer for a method, for fast calling.
        [[nodiscard]] void* get_method_pointer(std::string_view name, int argc = -1) const;

        /// Get a field handle by name.
        [[nodiscard]] Field get_field_info(std::string_view name) const;

        /// Get a method handle by name.
        [[nodiscard]] Method get_method_info(std::string_view name, int argc = -1) const;

        // ---- String convenience helpers ----

        [[nodiscard]] std::string get_string_field(std::string_view name) const;
        [[nodiscard]] std::string get_string_property(std::string_view name) const;
        [[nodiscard]] std::string call_string_method(std::string_view name, void** params = nullptr, int argc = -1) const;
        void set_string_field(std::string_view name, std::string_view value);
        void set_string_property(std::string_view name, std::string_view value);

        // ---- Equality ----

        [[nodiscard]] bool operator==(const ManagedObject& other) const noexcept { return m_native == other.m_native; }
        [[nodiscard]] bool operator!=(const ManagedObject& other) const noexcept { return m_native != other.m_native; }
    };

    /// Check if a raw pointer looks like a valid IL2CPP object.
    [[nodiscard]] inline bool IsValidPointer(void* ptr) noexcept {
        if (!ptr) return false;
        constexpr uintptr_t minAddr = 0x10000;
        constexpr uintptr_t maxAddr = 0x7FFFFFFF0000;
        uintptr_t addr = reinterpret_cast<uintptr_t>(ptr);
        return addr >= minAddr && addr <= maxAddr;
    }

} // namespace IL2CPP::Module

template<typename T>
    requires std::is_base_of_v<IL2CPP::Module::ManagedObject, T>
struct std::hash<T> {
    size_t operator()(const T& obj) const noexcept {
        return std::hash<void*>{}(obj.raw());
    }
};
