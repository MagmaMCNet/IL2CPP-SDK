#pragma once
#include "Object.hpp"
#include "Component.hpp"
#include "../Reflection.hpp"
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
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->gameObject.m_Find) return GameObject{};
            auto* exports = GetExports();
            if (!exports || !exports->m_stringNew) return GameObject{};
            void* il2cppStr = reinterpret_cast<void*(IL2CPP_CALLTYPE)(const char*)>(exports->m_stringNew)(
                std::string(name).c_str());
            return GameObject{ reinterpret_cast<void*(IL2CPP_CALLTYPE)(void*)>(fn->gameObject.m_Find)(il2cppStr) };
        }

        /// Static: Find a GameObject by tag.
        [[nodiscard]] static GameObject FindWithTag(std::string_view tag) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->gameObject.m_FindGameObjectWithTag) return GameObject{};
            auto* exports = GetExports();
            if (!exports || !exports->m_stringNew) return GameObject{};
            void* il2cppStr = reinterpret_cast<void*(IL2CPP_CALLTYPE)(const char*)>(exports->m_stringNew)(
                std::string(tag).c_str());
            return GameObject{ reinterpret_cast<void*(IL2CPP_CALLTYPE)(void*)>(fn->gameObject.m_FindGameObjectWithTag)(il2cppStr) };
        }

        /// Static: Find all GameObjects with the specified tag.
        [[nodiscard]] static std::vector<GameObject> FindGameObjectsWithTag(std::string_view tag) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->gameObject.m_FindGameObjectsWithTag) return {};
            auto* exports = GetExports();
            if (!exports || !exports->m_stringNew) return {};
            void* il2cppStr = reinterpret_cast<void*(IL2CPP_CALLTYPE)(const char*)>(exports->m_stringNew)(
                std::string(tag).c_str());
            void* array = reinterpret_cast<void*(IL2CPP_CALLTYPE)(void*)>(fn->gameObject.m_FindGameObjectsWithTag)(il2cppStr);
            return Object::FromArray<GameObject>(array);
        }

        /// Static: Create a primitive GameObject (Sphere, Cube, etc.).
        [[nodiscard]] static GameObject CreatePrimitive(PrimitiveType type) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->gameObject.m_CreatePrimitive) return GameObject{};
            return GameObject{ reinterpret_cast<void*(IL2CPP_CALLTYPE)(int)>(fn->gameObject.m_CreatePrimitive)(static_cast<int>(type)) };
        }

        /// Get the Transform component.
        [[nodiscard]] Transform GetTransform() const;

        // ---- Component Accessors ----

        /// Get a component by System.Type.
        [[nodiscard]] Component GetComponent(Il2CppSystemType* systemType) const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->gameObject.m_GetComponent || !raw() || !systemType) return Component{};
            return Component{ reinterpret_cast<void*(IL2CPP_CALLTYPE)(void*, void*)>(fn->gameObject.m_GetComponent)(raw(), systemType) };
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
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->gameObject.m_GetComponentByName || !raw()) return Component{};
            auto* exports = GetExports();
            if (!exports || !exports->m_stringNew) return Component{};
            void* il2cppStr = reinterpret_cast<void*(IL2CPP_CALLTYPE)(const char*)>(exports->m_stringNew)(
                std::string(name).c_str());
            return Component{ reinterpret_cast<void*(IL2CPP_CALLTYPE)(void*, void*)>(fn->gameObject.m_GetComponentByName)(raw(), il2cppStr) };
        }

        /// Get a component in children.
        [[nodiscard]] Component GetComponentInChildren(Il2CppSystemType* systemType, bool includeInactive = false) const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->gameObject.m_GetComponentInChildren || !raw() || !systemType) return Component{};
            return Component{ reinterpret_cast<void*(IL2CPP_CALLTYPE)(void*, void*, bool)>(fn->gameObject.m_GetComponentInChildren)(raw(), systemType, includeInactive) };
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
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->gameObject.m_GetComponentInParent || !raw() || !systemType) return Component{};
            return Component{ reinterpret_cast<void*(IL2CPP_CALLTYPE)(void*, void*, bool)>(fn->gameObject.m_GetComponentInParent)(raw(), systemType, includeInactive) };
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
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->gameObject.m_AddComponent || !raw() || !systemType) return Component{};
            return Component{ reinterpret_cast<void*(IL2CPP_CALLTYPE)(void*, void*)>(fn->gameObject.m_AddComponent)(raw(), systemType) };
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
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->gameObject.m_GetComponents || !raw() || !systemType) return {};
            void* array = reinterpret_cast<void*(IL2CPP_CALLTYPE)(void*, void*)>(fn->gameObject.m_GetComponents)(raw(), systemType);
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
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->gameObject.m_GetComponents || !raw() || !systemType) return {};
            void* array = reinterpret_cast<void*(IL2CPP_CALLTYPE)(void*, void*)>(fn->gameObject.m_GetComponents)(raw(), systemType);
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
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->gameObject.m_GetComponentsInChildren || !raw() || !systemType) return {};
            void* array = reinterpret_cast<void*(IL2CPP_CALLTYPE)(void*, void*, bool)>(fn->gameObject.m_GetComponentsInChildren)(raw(), systemType, includeInactive);
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
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->gameObject.m_GetComponentsInChildren || !raw() || !systemType) return {};
            void* array = reinterpret_cast<void*(IL2CPP_CALLTYPE)(void*, void*, bool)>(fn->gameObject.m_GetComponentsInChildren)(raw(), systemType, includeInactive);
            return Object::FromArray<T>(array);
        }

        /// Get all components of the specified type in parent.
        [[nodiscard]] std::vector<Component> GetComponentsInParent(Il2CppSystemType* systemType, bool includeInactive = false) const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->gameObject.m_GetComponentsInParent || !raw() || !systemType) return {};
            void* array = reinterpret_cast<void*(IL2CPP_CALLTYPE)(void*, void*, bool)>(fn->gameObject.m_GetComponentsInParent)(raw(), systemType, includeInactive);
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
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->gameObject.m_GetComponentsInParent || !raw() || !systemType) return {};
            void* array = reinterpret_cast<void*(IL2CPP_CALLTYPE)(void*, void*, bool)>(fn->gameObject.m_GetComponentsInParent)(raw(), systemType, includeInactive);
            return Object::FromArray<T>(array);
        }

        /// Try to get a component of the specified type.
        [[nodiscard]] bool TryGetComponent(Il2CppSystemType* systemType, Component& out) const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->gameObject.m_TryGetComponent || !raw() || !systemType) return false;
            void* result = nullptr;
            bool success = reinterpret_cast<bool(IL2CPP_CALLTYPE)(void*, void*, void**)>(fn->gameObject.m_TryGetComponent)(raw(), systemType, &result);
            if (success && result) {
                out = Component{ result };
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
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->gameObject.m_GetActive || !raw()) return false;
            return reinterpret_cast<bool(IL2CPP_CALLTYPE)(void*)>(fn->gameObject.m_GetActive)(raw());
        }

        [[nodiscard]] bool GetActiveSelf() const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->gameObject.m_GetActiveSelf || !raw()) return false;
            return reinterpret_cast<bool(IL2CPP_CALLTYPE)(void*)>(fn->gameObject.m_GetActiveSelf)(raw());
        }

        [[nodiscard]] bool GetActiveInHierarchy() const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->gameObject.m_GetActiveInHierarchy || !raw()) return false;
            return reinterpret_cast<bool(IL2CPP_CALLTYPE)(void*)>(fn->gameObject.m_GetActiveInHierarchy)(raw());
        }

        void SetActive(bool active) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->gameObject.m_SetActive || !raw()) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, bool)>(fn->gameObject.m_SetActive)(raw(), active);
        }

        // ---- Layer ----

        [[nodiscard]] unsigned int GetLayer() const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->gameObject.m_GetLayer || !raw()) return 0;
            return reinterpret_cast<unsigned int(IL2CPP_CALLTYPE)(void*)>(fn->gameObject.m_GetLayer)(raw());
        }

        void SetLayer(unsigned int layer) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->gameObject.m_SetLayer || !raw()) return;
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, unsigned int)>(fn->gameObject.m_SetLayer)(raw(), layer);
        }

        // ---- Scene ----

        [[nodiscard]] Scene GetScene() const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->gameObject.m_GetScene || !raw()) return Scene{};
            Scene s = reinterpret_cast<Scene(IL2CPP_CALLTYPE)(void*)>(fn->gameObject.m_GetScene)(raw());
            return s;
        }

        // ---- Tag Methods ----

        [[nodiscard]] std::string GetTag() const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->gameObject.m_GetTag || !raw()) return "";
            
            void* str = reinterpret_cast<void*(IL2CPP_CALLTYPE)(void*)>(fn->gameObject.m_GetTag)(raw());
            if (!str) return "";
            
            int len = *reinterpret_cast<int*>(static_cast<char*>(str) + 0x10);
            if (len <= 0) return "";
            
            wchar_t* wstr = reinterpret_cast<wchar_t*>(static_cast<char*>(str) + 0x14);
            std::wstring ws(wstr, len);
            return std::string(ws.begin(), ws.end());
        }

        void SetTag(std::string_view tag) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->gameObject.m_SetTag || !raw()) return;
            auto* exports = GetExports();
            if (!exports || !exports->m_stringNew) return;
            void* il2cppStr = reinterpret_cast<void*(IL2CPP_CALLTYPE)(const char*)>(exports->m_stringNew)(
                std::string(tag).c_str());
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, void*)>(fn->gameObject.m_SetTag)(raw(), il2cppStr);
        }

        [[nodiscard]] bool CompareTag(std::string_view tag) const {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->gameObject.m_CompareTag || !raw()) return false;
            auto* exports = GetExports();
            if (!exports || !exports->m_stringNew) return false;
            void* il2cppStr = reinterpret_cast<void*(IL2CPP_CALLTYPE)(const char*)>(exports->m_stringNew)(
                std::string(tag).c_str());
            return reinterpret_cast<bool(IL2CPP_CALLTYPE)(void*, void*)>(fn->gameObject.m_CompareTag)(raw(), il2cppStr);
        }

        // ---- Message Methods ----

        void SendMessage(std::string_view methodName, SendMessageOptions options = SendMessageOptions::RequireReceiver) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->gameObject.m_SendMessage || !raw()) return;
            auto* exports = GetExports();
            if (!exports || !exports->m_stringNew) return;
            void* il2cppStr = reinterpret_cast<void*(IL2CPP_CALLTYPE)(const char*)>(exports->m_stringNew)(
                std::string(methodName).c_str());
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, void*, int)>(fn->gameObject.m_SendMessage)(raw(), il2cppStr, static_cast<int>(options));
        }

        void SendMessageUpwards(std::string_view methodName, SendMessageOptions options = SendMessageOptions::RequireReceiver) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->gameObject.m_SendMessageUpwards || !raw()) return;
            auto* exports = GetExports();
            if (!exports || !exports->m_stringNew) return;
            void* il2cppStr = reinterpret_cast<void*(IL2CPP_CALLTYPE)(const char*)>(exports->m_stringNew)(
                std::string(methodName).c_str());
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, void*, int)>(fn->gameObject.m_SendMessageUpwards)(raw(), il2cppStr, static_cast<int>(options));
        }

        void BroadcastMessage(std::string_view methodName, SendMessageOptions options = SendMessageOptions::RequireReceiver) {
            auto* fn = GetUnityFunctions();
            if (!fn || !fn->gameObject.m_BroadcastMessage || !raw()) return;
            auto* exports = GetExports();
            if (!exports || !exports->m_stringNew) return;
            void* il2cppStr = reinterpret_cast<void*(IL2CPP_CALLTYPE)(const char*)>(exports->m_stringNew)(
                std::string(methodName).c_str());
            reinterpret_cast<void(IL2CPP_CALLTYPE)(void*, void*, int)>(fn->gameObject.m_BroadcastMessage)(raw(), il2cppStr, static_cast<int>(options));
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
