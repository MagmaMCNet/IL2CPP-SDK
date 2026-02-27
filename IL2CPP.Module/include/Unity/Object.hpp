#pragma once
#include "../ManagedObject.hpp"
#include "../Reflection.hpp"
#include "../System/Array.hpp"
#include <IL2CPP.Common/il2cpp_types.hpp>
#include <IL2CPP.Common/il2cpp_shared.hpp>
#include <IL2CPP.Common/il2cpp_unity_shared.hpp>
#include <string>
#include <string_view>
#include <vector>
#include <Windows.h>

// ============================================================================
//  IL2CPP.Module::Unity::Object
//
//  High-level wrapper for UnityEngine.Object. Base class for all Unity types.
//  Uses the shared Unity function table from IL2CPP.Core.
// ============================================================================

namespace IL2CPP::Module {
    // Forward declarations
    unity_functions const* GetUnityFunctions() noexcept;
    bool IsUnityConnected() noexcept;
}

namespace IL2CPP::Module::Unity {

    class Transform;

    class Object : public ManagedObject {
    public:
        using ManagedObject::ManagedObject;

        /// Check if the Unity native pointer is still valid.
        [[nodiscard]] bool IsValid() const noexcept {
            if (!valid()) return false;
            // UnityEngine.Object has m_CachedPtr at offset 0x10 (after il2cppObject header)
            void* cachedPtr = read<void*>(0x10);
            return IsValidPointer(cachedPtr);
        }

        /// Destroy this object.
        void Destroy(float delay = 0.f) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->object.m_Destroy || !raw()) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, float)>(fn->object.m_Destroy)(raw(), delay);
        }

        /// Destroy this object immediately (use with caution).
        void DestroyImmediate() {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->object.m_DestroyImmediate || !raw()) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*)>(fn->object.m_DestroyImmediate)(raw());
        }

        /// Get the object name.

        [[nodiscard]] std::string GetName() const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->object.m_GetName || !raw()) return "";

            void* str =
                reinterpret_cast<void* (IL2CPP_CALLTYPE)(void*)>(fn->object.m_GetName)(
                    raw()
                    );
            if (!str) return "";

            const int len = *reinterpret_cast<int*>(static_cast<char*>(str) + 0x10);
            if (len <= 0) return "";

            const wchar_t* wstr =
                reinterpret_cast<const wchar_t*>(static_cast<char*>(str) + 0x14);

            const int bytes = WideCharToMultiByte(
                CP_UTF8,
                0,
                wstr,
                len,
                nullptr,
                0,
                nullptr,
                nullptr
            );
            if (bytes <= 0) return "";

            std::string out;
            out.resize(static_cast<size_t>(bytes));

            const int written = WideCharToMultiByte(
                CP_UTF8,
                0,
                wstr,
                len,
                out.data(),
                bytes,
                nullptr,
                nullptr
            );
            if (written != bytes) return "";

            return out;
        }

        /// Set the object name.
        void SetName(std::string_view name) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->object.m_SetName || !raw()) return;
            auto* exports = GetExports();
            if (!exports || !exports->m_stringNew) return;
            void* il2cppStr = reinterpret_cast<void*(IL2CPP_CALLTYPE)(const char*)>(exports->m_stringNew)(
                std::string(name).c_str());
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, void*)>(fn->object.m_SetName)(raw(), il2cppStr);
        }

        /// Instantiate (clone) this object.
        [[nodiscard]] Object Instantiate() const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->object.m_Internal_CloneSingle || !raw()) return Object{};
            return Object{ reinterpret_cast<void*(IL2CPP_CALLTYPE)(void*)>(fn->object.m_Internal_CloneSingle)(raw()) };
        }

        /// Mark this object as DontDestroyOnLoad.
        void DontDestroyOnLoad() {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->object.m_DontDestroyOnLoad || !raw()) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*)>(fn->object.m_DontDestroyOnLoad)(raw());
        }

        /// Static: Destroy an object by handle.
        static void Destroy(Object obj, float delay = 0.f) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->object.m_Destroy || !obj.raw()) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, float)>(fn->object.m_Destroy)(obj.raw(), delay);
        }

        // ---- Static FindObjectOfType Methods ----

        /// Find an object of the specified type (first match).
        /// @param systemType The System.Type object pointer (Il2CppSystemType*)
        /// @return The found object, or invalid Object if none found.
        [[nodiscard]] static Object FindObjectOfType(Il2CppSystemType* systemType) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->object.m_FindObjectOfType || !systemType) return Object{};
            return Object{ reinterpret_cast<void*(IL2CPP_CALLTYPE)(void*, bool)>(fn->object.m_FindObjectOfType)(systemType, false) };
        }

        /// Find an object of the specified class type (first match).
        /// @param klass The Class handle to search for.
        /// @return The found object, or invalid Object if none found.
        [[nodiscard]] static Object FindObjectOfType(Class klass) {
            if (!klass) return Object{};
            Type t = klass.get_type();
            if (!t) return Object{};
            return FindObjectOfType(reinterpret_cast<Il2CppSystemType*>(t.get_system_type_object()));
        }

        /// Find an object of the specified class by name (first match).
        /// @param className Full class name (e.g., "UnityEngine.Camera")
        /// @return The found object, or invalid Object if none found.
        [[nodiscard]] static Object FindObjectOfType(std::string_view className) {
            Class klass = Class::find(className);
            if (!klass) return Object{};
            return FindObjectOfType(klass);
        }

        // ---- Static FindObjectsOfType Methods ----

        /// Helper: convert raw IL2CPP array to std::vector of wrapped objects.
        template<typename T>
        static std::vector<T> FromArray(void* rawArray) {
            if (!rawArray) return {};
            System::Array<void*> arr{ rawArray };
            
            uintptr_t count = arr.size();
            if (count == 0) return {};
            
            std::vector<T> result;
            result.reserve(count);
            
            for (uintptr_t i = 0; i < count; i++) {
                void* element = arr[i];
                if (element) result.push_back(T{ element });
            }
            return result;
        }

        /// Find all objects of the specified type.
        /// @param systemType The System.Type object pointer (Il2CppSystemType*)
        /// @return A vector of Object containing all found objects.
        [[nodiscard]] static std::vector<Object> FindObjectsOfType(Il2CppSystemType* systemType) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->object.m_FindObjectsOfType || !systemType) return {};
            void* raw = reinterpret_cast<void*(IL2CPP_CALLTYPE)(void*, bool)>(fn->object.m_FindObjectsOfType)(systemType, false);
            return FromArray<Object>(raw);
        }

        /// Find all objects of the specified class type.
        /// @param klass The Class handle to search for.
        /// @return A vector of Object containing all found objects.
        [[nodiscard]] static std::vector<Object> FindObjectsOfType(Class klass) {
            if (!klass) return {};
            Type t = klass.get_type();
            if (!t) return {};
            return FindObjectsOfType(reinterpret_cast<Il2CppSystemType*>(t.get_system_type_object()));
        }

        /// Find all objects of the specified class by name.
        /// @param className Full class name (e.g., "UnityEngine.Camera")
        /// @return A vector of Object containing all found objects.
        [[nodiscard]] static std::vector<Object> FindObjectsOfType(std::string_view className) {
            Class klass = Class::find(className);
            if (!klass) return {};
            return FindObjectsOfType(klass);
        }

        // ---- Typed FindObjectsOfType (template helper) ----

        /// Find all objects and return as std::vector<T>.
        /// @tparam T The wrapper type (must derive from ManagedObject)
        /// @param systemType The System.Type object pointer
        /// @return A vector of T containing all found objects.
        template<typename T> requires std::is_base_of_v<ManagedObject, T>
        [[nodiscard]] static std::vector<T> FindObjectsOfTypeAs(Il2CppSystemType* systemType) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->object.m_FindObjectsOfType || !systemType) return {};
            void* raw = reinterpret_cast<void*(IL2CPP_CALLTYPE)(void*, bool)>(fn->object.m_FindObjectsOfType)(systemType, false);
            return FromArray<T>(raw);
        }

        template<typename T> requires std::is_base_of_v<ManagedObject, T>
        [[nodiscard]] static std::vector<T> FindObjectsOfTypeAs(Class klass) {
            if (!klass) return {};
            Type t = klass.get_type();
            if (!t) return {};
            return FindObjectsOfTypeAs<T>(reinterpret_cast<Il2CppSystemType*>(t.get_system_type_object()));
        }

        template<typename T> requires std::is_base_of_v<ManagedObject, T>
        [[nodiscard]] static std::vector<T> FindObjectsOfTypeAs(std::string_view className) {
            Class klass = Class::find(className);
            if (!klass) return {};
            return FindObjectsOfTypeAs<T>(klass);
        }

        // ---- Instantiate with Parent ----

        /// Instantiate (clone) this object with a parent transform.
        /// @param parent The parent Transform for the cloned object.
        /// @return The cloned object.
        [[nodiscard]] Object InstantiateWithParent(Transform parent) const;

        // ---- Legacy snake_case aliases (deprecated) ----
        [[deprecated("Use IsValid()")]] [[nodiscard]] bool is_valid() const noexcept { return IsValid(); }
        [[deprecated("Use Destroy()")]] void destroy(float delay = 0.f) { Destroy(delay); }
        [[deprecated("Use DestroyImmediate()")]] void destroy_immediate() { DestroyImmediate(); }
        [[deprecated("Use GetName()")]] [[nodiscard]] std::string get_name() const { return GetName(); }
        [[deprecated("Use SetName()")]] void set_name(std::string_view name) { SetName(name); }
        [[deprecated("Use Instantiate()")]] [[nodiscard]] Object instantiate() const { return Instantiate(); }
        [[deprecated("Use DontDestroyOnLoad()")]] void dont_destroy_on_load() { DontDestroyOnLoad(); }
    };

    // Type alias for backwards compatibility
    using ObjectArray = std::vector<Object>;

} // namespace IL2CPP::Module::Unity
