#include <include/ManagedObject.hpp>
#include <include/il2cpp_module.hpp>
#include <include/System/String.hpp>

// ============================================================================
//  IL2CPP.Module - ManagedObject Implementation
// ============================================================================

namespace IL2CPP::Module {

    bool ManagedObject::valid() const noexcept {
        if (!m_native) return false;
        if (!IsValidPointer(m_native)) return false;
        return true;
        // Check that m_pClass (first field of il2cppObject) is non-null
        void* klass = *reinterpret_cast<void**>(m_native);
        return IsValidPointer(klass);
    }

    Class ManagedObject::get_class() const {
        if (!valid()) return Class{};
        // il2cppObject::m_pClass is the first field
        return Class{ *reinterpret_cast<void**>(m_native) };
    }

    void* ManagedObject::get_method_pointer(std::string_view name, int argc) const {
        if (!valid()) return nullptr;
        Class klass = get_class();
        if (!klass) return nullptr;
        return klass.get_method_pointer(name, argc);
    }

    Field ManagedObject::get_field_info(std::string_view name) const {
        if (!valid()) return Field{};
        Class klass = get_class();
        if (!klass) return Field{};
        return klass.get_field(name);
    }

    Method ManagedObject::get_method_info(std::string_view name, int argc) const {
        if (!valid()) return Method{};
        Class klass = get_class();
        if (!klass) return Method{};
        return klass.get_method(name, argc);
    }

    // ---- String convenience helpers ----

    std::string ManagedObject::get_string_field(std::string_view name) const {
        if (!valid()) return "";
        auto* strPtr = get_field<void*>(name);
        if (!strPtr) return "";
        return System::String(strPtr).to_string();
    }

    std::string ManagedObject::get_string_property(std::string_view name) const {
        if (!valid()) return "";
        auto* strPtr = get_property<void*>(name);
        if (!strPtr) return "";
        return System::String(strPtr).to_string();
    }

    std::string ManagedObject::call_string_method(std::string_view name, void** params, int argc) const {
        if (!valid()) return "";
        auto* strPtr = call_method<void*>(name, params, argc);
        if (!strPtr) return "";
        return System::String(strPtr).to_string();
    }

    void ManagedObject::set_string_field(std::string_view name, std::string_view value) {
        if (!valid()) return;
        auto str = System::String::create(value);
        set_field(name, str.raw());
    }

    void ManagedObject::set_string_property(std::string_view name, std::string_view value) {
        if (!valid()) return;
        auto str = System::String::create(value);
        set_property(name, str.raw());
    }

} // namespace IL2CPP::Module
