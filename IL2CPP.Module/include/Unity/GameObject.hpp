#pragma once
#include "Object.hpp"
#include "Component.hpp"
#include "../Reflection.hpp"
#include "../MethodHandler.hpp"
#include <IL2CPP.Common/il2cpp_shared.hpp>
#include <IL2CPP.Common/il2cpp_types.hpp>
#include <vector>

// ============================================================================
//  IL2CPP.Module::Unity::GameObject
// ============================================================================

namespace IL2CPP::Module::Unity {

    class Transform;

    class GameObject : public Object {
    public:
        using Object::Object;

        /// Static: Find a GameObject by name.
        [[nodiscard]] static GameObject Find(std::string_view name) {
            static auto m = MethodHandler::resolve("UnityEngine.GameObject", "Find", 1);
            auto* exports = GetExports();
            if (!exports || !exports->m_stringNew) return GameObject{};
            void* il2cppStr = reinterpret_cast<void*(IL2CPP_CALLTYPE)(const char*)>(exports->m_stringNew)(
                std::string(name).c_str());
            void* params[] = { il2cppStr };
            return GameObject{ MethodHandler::invoke<void*>(m, nullptr, params) };
        }

        /// Static: Find a GameObject by tag.
        [[nodiscard]] static GameObject FindWithTag(std::string_view tag) {
            static auto m = MethodHandler::resolve("UnityEngine.GameObject", "FindWithTag", 1);
            auto* exports = GetExports();
            if (!exports || !exports->m_stringNew) return GameObject{};
            void* il2cppStr = reinterpret_cast<void*(IL2CPP_CALLTYPE)(const char*)>(exports->m_stringNew)(
                std::string(tag).c_str());
            void* params[] = { il2cppStr };
            return GameObject{ MethodHandler::invoke<void*>(m, nullptr, params) };
        }

        /// Static: Find all GameObjects with the specified tag.
        [[nodiscard]] static std::vector<GameObject> FindGameObjectsWithTag(std::string_view tag) {
            static auto m = MethodHandler::resolve("UnityEngine.GameObject", "FindGameObjectsWithTag", 1);
            auto* exports = GetExports();
            if (!exports || !exports->m_stringNew) return {};
            void* il2cppStr = reinterpret_cast<void*(IL2CPP_CALLTYPE)(const char*)>(exports->m_stringNew)(
                std::string(tag).c_str());
            void* params[] = { il2cppStr };
            void* array = MethodHandler::invoke<void*>(m, nullptr, params);
            return Object::FromArray<GameObject>(array);
        }

        /// Static: Create a primitive GameObject (Sphere, Cube, etc.).
        [[nodiscard]] static GameObject CreatePrimitive(PrimitiveType type) {
            static auto m = MethodHandler::resolve("UnityEngine.GameObject", "CreatePrimitive", 1);
            int val = static_cast<int>(type);
            void* params[] = { &val };
            return GameObject{ MethodHandler::invoke<void*>(m, nullptr, params) };
        }

        /// Get the Transform component.
        [[nodiscard]] Transform GetTransform() const;

        // ---- Component Accessors ----

        /// Get a component by System.Type.
        [[nodiscard]] Component GetComponent(Il2CppSystemType* systemType) const {
            static auto m = MethodHandler::resolve("UnityEngine.GameObject", "GetComponent", 1);
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

        /// Get a component in children.
        [[nodiscard]] Component GetComponentInChildren(Il2CppSystemType* systemType, bool includeInactive = false) const {
            static auto m = MethodHandler::resolve("UnityEngine.GameObject", "GetComponentInChildren", 2);
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

        /// Get a component in parent.
        [[nodiscard]] Component GetComponentInParent(Il2CppSystemType* systemType, bool includeInactive = false) const {
            static auto m = MethodHandler::resolve("UnityEngine.GameObject", "GetComponentInParent", 2);
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

        /// Add a component.
        [[nodiscard]] Component AddComponent(Il2CppSystemType* systemType) {
            static auto m = MethodHandler::resolve("UnityEngine.GameObject", "AddComponent", 1);
            if (!systemType) return Component{};
            void* params[] = { systemType };
            return Component{ MethodHandler::invoke<void*>(m, raw(), params) };
        }

        /// Add a component by Class.
        [[nodiscard]] Component AddComponent(Class klass) {
            if (!klass) return Component{};
            Type t = klass.get_type();
            if (!t) return Component{};
            return AddComponent(reinterpret_cast<Il2CppSystemType*>(t.get_system_type_object()));
        }

        // ---- GetComponents ----

        /// Get all components of the specified type.
        [[nodiscard]] std::vector<Component> GetComponents(Il2CppSystemType* systemType) const {
            static auto m = MethodHandler::resolve("UnityEngine.GameObject", "GetComponents", 1);
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
            static auto m = MethodHandler::resolve("UnityEngine.GameObject", "GetComponents", 1);
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
            static auto m = MethodHandler::resolve("UnityEngine.GameObject", "GetComponentsInChildren", 2);
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
            static auto m = MethodHandler::resolve("UnityEngine.GameObject", "GetComponentsInChildren", 2);
            if (!systemType) return {};
            void* params[] = { systemType, &includeInactive };
            void* array = MethodHandler::invoke<void*>(m, raw(), params);
            return Object::FromArray<T>(array);
        }

        /// Get all components of the specified type in parent.
        [[nodiscard]] std::vector<Component> GetComponentsInParent(Il2CppSystemType* systemType, bool includeInactive = false) const {
            static auto m = MethodHandler::resolve("UnityEngine.GameObject", "GetComponentsInParent", 2);
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
            static auto m = MethodHandler::resolve("UnityEngine.GameObject", "GetComponentsInParent", 2);
            if (!systemType) return {};
            void* params[] = { systemType, &includeInactive };
            void* array = MethodHandler::invoke<void*>(m, raw(), params);
            return Object::FromArray<T>(array);
        }

        /// Try to get a component of the specified type.
        [[nodiscard]] bool TryGetComponent(Il2CppSystemType* systemType, Component& out) const {
            static auto m = MethodHandler::resolve("UnityEngine.GameObject", "TryGetComponent", 2);
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

        // ---- Active State ----

        [[nodiscard]] bool GetActive() const {
            static auto m = MethodHandler::resolve("UnityEngine.GameObject", "get_active", 0);
            return MethodHandler::invoke<bool>(m, raw());
        }

        [[nodiscard]] bool GetActiveSelf() const {
            static auto m = MethodHandler::resolve("UnityEngine.GameObject", "get_activeSelf", 0);
            return MethodHandler::invoke<bool>(m, raw());
        }

        [[nodiscard]] bool GetActiveInHierarchy() const {
            static auto m = MethodHandler::resolve("UnityEngine.GameObject", "get_activeInHierarchy", 0);
            return MethodHandler::invoke<bool>(m, raw());
        }

        void SetActive(bool active) {
            static auto m = MethodHandler::resolve("UnityEngine.GameObject", "SetActive", 1);
            void* params[] = { &active };
            MethodHandler::invoke(m, raw(), params);
        }

        // ---- Layer ----

        [[nodiscard]] unsigned int GetLayer() const {
            static auto m = MethodHandler::resolve("UnityEngine.GameObject", "get_layer", 0);
            return static_cast<unsigned int>(MethodHandler::invoke<int>(m, raw()));
        }

        void SetLayer(unsigned int layer) {
            static auto m = MethodHandler::resolve("UnityEngine.GameObject", "set_layer", 1);
            int val = static_cast<int>(layer);
            void* params[] = { &val };
            MethodHandler::invoke(m, raw(), params);
        }

        // ---- Scene ----

        [[nodiscard]] Scene GetScene() const {
            static auto m = MethodHandler::resolve("UnityEngine.GameObject", "get_scene", 0);
            return MethodHandler::invoke<Scene>(m, raw());
        }

        // ---- Tag Methods ----

        [[nodiscard]] std::string GetTag() const {
            static auto m = MethodHandler::resolve("UnityEngine.GameObject", "get_tag", 0);
            void* str = MethodHandler::invoke<void*>(m, raw());
            if (!str) return "";

            int len = *reinterpret_cast<int*>(static_cast<char*>(str) + 0x10);
            if (len <= 0) return "";

            wchar_t* wstr = reinterpret_cast<wchar_t*>(static_cast<char*>(str) + 0x14);
            std::wstring ws(wstr, len);
            return std::string(ws.begin(), ws.end());
        }

        void SetTag(std::string_view tag) {
            static auto m = MethodHandler::resolve("UnityEngine.GameObject", "set_tag", 1);
            auto* exports = GetExports();
            if (!exports || !exports->m_stringNew) return;
            void* il2cppStr = reinterpret_cast<void*(IL2CPP_CALLTYPE)(const char*)>(exports->m_stringNew)(
                std::string(tag).c_str());
            void* params[] = { il2cppStr };
            MethodHandler::invoke(m, raw(), params);
        }

        [[nodiscard]] bool CompareTag(std::string_view tag) const {
            static auto m = MethodHandler::resolve("UnityEngine.GameObject", "CompareTag", 1);
            auto* exports = GetExports();
            if (!exports || !exports->m_stringNew) return false;
            void* il2cppStr = reinterpret_cast<void*(IL2CPP_CALLTYPE)(const char*)>(exports->m_stringNew)(
                std::string(tag).c_str());
            void* params[] = { il2cppStr };
            return MethodHandler::invoke<bool>(m, raw(), params);
        }

        // ---- Message Methods ----

        void SendMessage(std::string_view methodName, SendMessageOptions options = SendMessageOptions::RequireReceiver) {
            static auto m = MethodHandler::resolve("UnityEngine.GameObject", "SendMessage", 2);
            auto* exports = GetExports();
            if (!exports || !exports->m_stringNew) return;
            void* il2cppStr = reinterpret_cast<void*(IL2CPP_CALLTYPE)(const char*)>(exports->m_stringNew)(
                std::string(methodName).c_str());
            int opt = static_cast<int>(options);
            void* params[] = { il2cppStr, &opt };
            MethodHandler::invoke(m, raw(), params);
        }

        void SendMessageUpwards(std::string_view methodName, SendMessageOptions options = SendMessageOptions::RequireReceiver) {
            static auto m = MethodHandler::resolve("UnityEngine.GameObject", "SendMessageUpwards", 2);
            auto* exports = GetExports();
            if (!exports || !exports->m_stringNew) return;
            void* il2cppStr = reinterpret_cast<void*(IL2CPP_CALLTYPE)(const char*)>(exports->m_stringNew)(
                std::string(methodName).c_str());
            int opt = static_cast<int>(options);
            void* params[] = { il2cppStr, &opt };
            MethodHandler::invoke(m, raw(), params);
        }

        void BroadcastMessage(std::string_view methodName, SendMessageOptions options = SendMessageOptions::RequireReceiver) {
            static auto m = MethodHandler::resolve("UnityEngine.GameObject", "BroadcastMessage", 2);
            auto* exports = GetExports();
            if (!exports || !exports->m_stringNew) return;
            void* il2cppStr = reinterpret_cast<void*(IL2CPP_CALLTYPE)(const char*)>(exports->m_stringNew)(
                std::string(methodName).c_str());
            int opt = static_cast<int>(options);
            void* params[] = { il2cppStr, &opt };
            MethodHandler::invoke(m, raw(), params);
        }

        // ---- Legacy snake_case aliases (deprecated) ----
        [[deprecated("Use Find()")]] [[nodiscard]] static GameObject find(std::string_view n) { return Find(n); }
        [[deprecated("Use FindWithTag()")]] [[nodiscard]] static GameObject find_with_tag(std::string_view t) { return FindWithTag(t); }
        [[deprecated("Use FindGameObjectsWithTag()")]] [[nodiscard]] static std::vector<GameObject> find_game_objects_with_tag(std::string_view t) { return FindGameObjectsWithTag(t); }
        [[deprecated("Use CreatePrimitive()")]] [[nodiscard]] static GameObject create_primitive(PrimitiveType t) { return CreatePrimitive(t); }
        [[deprecated("Use GetTransform()")]] [[nodiscard]] Transform get_transform() const;
        [[deprecated("Use GetActive()")]] [[nodiscard]] bool get_active() const { return GetActive(); }
        [[deprecated("Use GetActiveSelf()")]] [[nodiscard]] bool get_active_self() const { return GetActiveSelf(); }
        [[deprecated("Use GetActiveInHierarchy()")]] [[nodiscard]] bool get_active_in_hierarchy() const { return GetActiveInHierarchy(); }
        [[deprecated("Use SetActive()")]] void set_active(bool a) { SetActive(a); }
        [[deprecated("Use GetLayer()")]] [[nodiscard]] unsigned int get_layer() const { return GetLayer(); }
        [[deprecated("Use SetLayer()")]] void set_layer(unsigned int l) { SetLayer(l); }
        [[deprecated("Use GetScene()")]] [[nodiscard]] Scene get_scene() const { return GetScene(); }
        [[deprecated("Use GetTag()")]] [[nodiscard]] std::string get_tag() const { return GetTag(); }
        [[deprecated("Use SetTag()")]] void set_tag(std::string_view t) { SetTag(t); }
        [[deprecated("Use CompareTag()")]] [[nodiscard]] bool compare_tag(std::string_view t) const { return CompareTag(t); }
    };

    // Type alias for backwards compatibility
    using GameObjectArray = std::vector<GameObject>;

} // namespace IL2CPP::Module::Unity
