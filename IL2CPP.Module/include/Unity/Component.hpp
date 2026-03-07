#pragma once
#include "Object.hpp"
#include "../Reflection.hpp"
#include "../MethodHandler.hpp"
#include <vector>

// ============================================================================
//  IL2CPP.Module::Unity::Component
// ============================================================================

namespace IL2CPP::Module::Unity {

    class GameObject;

    class Component : public Object {
    public:
        using Object::Object;

        /// Get the Transform attached to this component.
        [[nodiscard]] Transform GetTransform() const;

        /// Get the GameObject this component is attached to.
        [[nodiscard]] GameObject GetGameObject() const;

        // ---- Single Component Accessors ----

        /// Get a component by System.Type.
        [[nodiscard]] Component GetComponent(Il2CppSystemType* systemType) const {
            static auto m = MethodHandler::resolve("UnityEngine.Component", "GetComponent", 1);
            if (!systemType) return Component{};
            void* params[] = { systemType };
            return Component{ MethodHandler::invoke<void*>(m, raw(), params) };
        }

        /// Get a component by Class.
        [[nodiscard]] Component GetComponent(Class klass) const {
            if (!klass) return Component{};
            Type t = klass.get_type();
            if (!t) return Component{};
            return GetComponent(reinterpret_cast<Il2CppSystemType*>(t.get_system_type_object()));
        }

        /// Get a component by name.
        [[nodiscard]] Component GetComponentByName(std::string_view name) const {
            Class klass = Class::find(name);
            if (!klass) return Component{};
            return GetComponent(klass);
        }

        /// Get a component in children by System.Type.
        [[nodiscard]] Component GetComponentInChildren(Il2CppSystemType* systemType, bool includeInactive = false) const {
            static auto m = MethodHandler::resolve("UnityEngine.Component", "GetComponentInChildren", 2);
            if (!systemType) return Component{};
            void* params[] = { systemType, &includeInactive };
            return Component{ MethodHandler::invoke<void*>(m, raw(), params) };
        }

        /// Get a component in children by Class.
        [[nodiscard]] Component GetComponentInChildren(Class klass, bool includeInactive = false) const {
            if (!klass) return Component{};
            Type t = klass.get_type();
            if (!t) return Component{};
            return GetComponentInChildren(reinterpret_cast<Il2CppSystemType*>(t.get_system_type_object()), includeInactive);
        }

        /// Get a component in parent by System.Type.
        [[nodiscard]] Component GetComponentInParent(Il2CppSystemType* systemType, bool includeInactive = false) const {
            static auto m = MethodHandler::resolve("UnityEngine.Component", "GetComponentInParent", 2);
            if (!systemType) return Component{};
            void* params[] = { systemType, &includeInactive };
            return Component{ MethodHandler::invoke<void*>(m, raw(), params) };
        }

        /// Get a component in parent by Class.
        [[nodiscard]] Component GetComponentInParent(Class klass, bool includeInactive = false) const {
            if (!klass) return Component{};
            Type t = klass.get_type();
            if (!t) return Component{};
            return GetComponentInParent(reinterpret_cast<Il2CppSystemType*>(t.get_system_type_object()), includeInactive);
        }

        // ---- Multiple Component Accessors ----

        /// Get all components of the specified type.
        /// @param systemType The System.Type object pointer (Il2CppSystemType*)
        /// @return A vector of Component containing all found components.
        [[nodiscard]] std::vector<Component> GetComponents(Il2CppSystemType* systemType) const {
            static auto m = MethodHandler::resolve("UnityEngine.Component", "GetComponents", 1);
            if (!systemType) return {};
            void* params[] = { systemType };
            void* array = MethodHandler::invoke<void*>(m, raw(), params);
            return Object::FromArray<Component>(array);
        }

        /// Get all components of the specified class.
        [[nodiscard]] std::vector<Component> GetComponents(Class klass) const {
            if (!klass) return {};
            Type t = klass.get_type();
            if (!t) return {};
            return GetComponents(reinterpret_cast<Il2CppSystemType*>(t.get_system_type_object()));
        }

        /// Get all components of the specified class by name.
        [[nodiscard]] std::vector<Component> GetComponents(std::string_view className) const {
            Class klass = Class::find(className);
            if (!klass) return {};
            return GetComponents(klass);
        }

        /// Get all components and return as std::vector<T>.
        template<typename T> requires std::is_base_of_v<ManagedObject, T>
        [[nodiscard]] std::vector<T> GetComponentsAs(Il2CppSystemType* systemType) const {
            static auto m = MethodHandler::resolve("UnityEngine.Component", "GetComponents", 1);
            if (!systemType) return {};
            void* params[] = { systemType };
            void* array = MethodHandler::invoke<void*>(m, raw(), params);
            return Object::FromArray<T>(array);
        }

        template<typename T> requires std::is_base_of_v<ManagedObject, T>
        [[nodiscard]] std::vector<T> GetComponentsAs(Class klass) const {
            if (!klass) return {};
            Type t = klass.get_type();
            if (!t) return {};
            return GetComponentsAs<T>(reinterpret_cast<Il2CppSystemType*>(t.get_system_type_object()));
        }

        /// Get all components of the specified type in children.
        [[nodiscard]] std::vector<Component> GetComponentsInChildren(Il2CppSystemType* systemType, bool includeInactive = false) const {
            static auto m = MethodHandler::resolve("UnityEngine.Component", "GetComponentsInChildren", 2);
            if (!systemType) return {};
            void* params[] = { systemType, &includeInactive };
            void* array = MethodHandler::invoke<void*>(m, raw(), params);
            return Object::FromArray<Component>(array);
        }

        /// Get all components of the specified class in children.
        [[nodiscard]] std::vector<Component> GetComponentsInChildren(Class klass, bool includeInactive = false) const {
            if (!klass) return {};
            Type t = klass.get_type();
            if (!t) return {};
            return GetComponentsInChildren(reinterpret_cast<Il2CppSystemType*>(t.get_system_type_object()), includeInactive);
        }

        /// Get all components in children and return as std::vector<T>.
        template<typename T> requires std::is_base_of_v<ManagedObject, T>
        [[nodiscard]] std::vector<T> GetComponentsInChildrenAs(Il2CppSystemType* systemType, bool includeInactive = false) const {
            static auto m = MethodHandler::resolve("UnityEngine.Component", "GetComponentsInChildren", 2);
            if (!systemType) return {};
            void* params[] = { systemType, &includeInactive };
            void* array = MethodHandler::invoke<void*>(m, raw(), params);
            return Object::FromArray<T>(array);
        }

        /// Get all components of the specified type in parent.
        [[nodiscard]] std::vector<Component> GetComponentsInParent(Il2CppSystemType* systemType, bool includeInactive = false) const {
            static auto m = MethodHandler::resolve("UnityEngine.Component", "GetComponentsInParent", 2);
            if (!systemType) return {};
            void* params[] = { systemType, &includeInactive };
            void* array = MethodHandler::invoke<void*>(m, raw(), params);
            return Object::FromArray<Component>(array);
        }

        /// Get all components of the specified class in parent.
        [[nodiscard]] std::vector<Component> GetComponentsInParent(Class klass, bool includeInactive = false) const {
            if (!klass) return {};
            Type t = klass.get_type();
            if (!t) return {};
            return GetComponentsInParent(reinterpret_cast<Il2CppSystemType*>(t.get_system_type_object()), includeInactive);
        }

        /// Get all components in parent and return as std::vector<T>.
        template<typename T> requires std::is_base_of_v<ManagedObject, T>
        [[nodiscard]] std::vector<T> GetComponentsInParentAs(Il2CppSystemType* systemType, bool includeInactive = false) const {
            static auto m = MethodHandler::resolve("UnityEngine.Component", "GetComponentsInParent", 2);
            if (!systemType) return {};
            void* params[] = { systemType, &includeInactive };
            void* array = MethodHandler::invoke<void*>(m, raw(), params);
            return Object::FromArray<T>(array);
        }

        // ---- TryGetComponent ----

        /// Try to get a component of the specified type.
        /// @param systemType The System.Type object pointer
        /// @param out Output parameter for the found component
        /// @return true if the component was found, false otherwise
        [[nodiscard]] bool TryGetComponent(Il2CppSystemType* systemType, Component& out) const {
            static auto m = MethodHandler::resolve("UnityEngine.Component", "TryGetComponent", 2);
            if (!systemType) return false;
            void* outComp = nullptr;
            void* params[] = { systemType, &outComp };
            bool success = MethodHandler::invoke<bool>(m, raw(), params);
            if (success && outComp) {
                out = Component{ outComp };
                return true;
            }
            return false;
        }

        /// Try to get a component of the specified class.
        [[nodiscard]] bool TryGetComponent(Class klass, Component& out) const {
            if (!klass) return false;
            Type t = klass.get_type();
            if (!t) return false;
            return TryGetComponent(reinterpret_cast<Il2CppSystemType*>(t.get_system_type_object()), out);
        }

        // ---- Legacy snake_case aliases (deprecated) ----
        [[deprecated("Use GetTransform()")]] [[nodiscard]] Transform get_transform() const;
        [[deprecated("Use GetGameObject()")]] [[nodiscard]] GameObject get_game_object() const;
        [[deprecated("Use GetComponent()")]] [[nodiscard]] Component get_component(Il2CppSystemType* t) const { return GetComponent(t); }
        [[deprecated("Use GetComponent()")]] [[nodiscard]] Component get_component(Class k) const { return GetComponent(k); }
        [[deprecated("Use GetComponentByName()")]] [[nodiscard]] Component get_component_by_name(std::string_view n) const { return GetComponentByName(n); }
        [[deprecated("Use GetComponentInChildren()")]] [[nodiscard]] Component get_component_in_children(Il2CppSystemType* t, bool i = false) const { return GetComponentInChildren(t, i); }
        [[deprecated("Use GetComponentInChildren()")]] [[nodiscard]] Component get_component_in_children(Class k, bool i = false) const { return GetComponentInChildren(k, i); }
        [[deprecated("Use GetComponentInParent()")]] [[nodiscard]] Component get_component_in_parent(Il2CppSystemType* t, bool i = false) const { return GetComponentInParent(t, i); }
        [[deprecated("Use GetComponentInParent()")]] [[nodiscard]] Component get_component_in_parent(Class k, bool i = false) const { return GetComponentInParent(k, i); }
        [[deprecated("Use TryGetComponent()")]] [[nodiscard]] bool try_get_component(Il2CppSystemType* t, Component& o) const { return TryGetComponent(t, o); }
        [[deprecated("Use TryGetComponent()")]] [[nodiscard]] bool try_get_component(Class k, Component& o) const { return TryGetComponent(k, o); }
    };

    // Type alias for backwards compatibility
    using ComponentArray = std::vector<Component>;

} // namespace IL2CPP::Module::Unity
