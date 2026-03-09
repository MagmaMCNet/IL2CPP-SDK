#pragma once

// ============================================================================
//  IL2CPP.Module  --  Master Include
//
//  This is the single header you include in your modules. It provides the full
//  high-level API for interacting with the IL2CPP runtime through shared memory.
//
//  Usage:
//      #include <il2cpp_module.hpp>
//
//      // Initialize connection to IL2CPP.Core:
//      if (!IL2CPP::Module::Connect()) return;
//
//      // --- Reflection API ---
//      auto klass = IL2CPP::Module::Class::find("UnityEngine.GameObject");
//      auto method = klass.get_method("Find", 1);
//      void* fnPtr = method.pointer();
//
//      // --- ManagedObject API ---
//      IL2CPP::Module::ManagedObject obj(somePtr);
//      float hp = obj.get_field<float>("health");
//      obj.set_field<float>("health", 100.f);
//
//      // --- Unity Wrappers ---
//      auto go = IL2CPP::Module::Unity::GameObject::find("Player");
//      auto tf = go.get_transform();
//      auto pos = tf.get_position();
//      float dt = IL2CPP::Module::Unity::Time::get_delta_time();
//
//      // --- .NET Wrappers ---
//      auto str = IL2CPP::Module::System::String::create("Hello");
//      std::string s = str.to_string();
//
//      // --- Deobfuscation ---
//      const char* stable = IL2CPP::Module::Deobfuscation::GetStableName(obfName);
//      IL2CPP::Module::Deobfuscation::AddMapping("obf", "clean");
//
//      // --- ClassResolver ---
//      auto klass2 = IL2CPP::Module::Class::find("SomeClass");
//      IL2CPP::Module::ClassResolver resolver(klass2);
//      int offset = 0;
//      resolver.field().byTypeName("Single").toOffset(offset).required();
//      if (resolver.resolve()) { /* offset is set */ }
//
//      // --- Raw access ---
//      void* rawClass = klass.raw();     // il2cppClass*
//      void* rawObj   = obj.raw();       // il2cppObject*
//
//      // Cleanup:
//      IL2CPP::Module::Disconnect();
// ============================================================================

// ---- Shared types (value types, enums, vtable definitions, struct layouts) ----
#include <IL2CPP.Common/il2cpp_shared.hpp>
#include <IL2CPP.Common/il2cpp_structs.hpp>
#include <IL2CPP.Common/il2cpp_unity_shared.hpp>
#include <IL2CPP.Common/il2cpp_types.hpp>

// ---- Core includes ----
#include <cstdint>
#include <string_view>
#include <vector>
#include <string>
#include <format>
#include <mutex>
#include <unordered_map>

// ============================================================================
//  Low-Level Module API (raw IL2CPP function wrappers)
//  These are retained for backward compatibility and advanced usage.
// ============================================================================

namespace IL2CPP::Module {

    // ---- Connection Lifecycle ----
    [[nodiscard]] bool Connect();
    void Disconnect();
    [[nodiscard]] bool IsConnected() noexcept;
    [[nodiscard]] IL2CPP::il2cpp_exports const* GetExports() noexcept;
    [[nodiscard]] unity_functions const* GetUnityFunctions() noexcept;
    [[nodiscard]] bool IsUnityConnected() noexcept;

    // ---- Domain / Assembly ----
    [[nodiscard]] void*             GetDomain();
    [[nodiscard]] il2cppAssembly**  GetAssemblies(size_t* count);

    // ---- Thread ----
    void* ThreadAttach(void* domain);
    void  ThreadDetach(void* thread);

    // ---- Class Lookup ----
    [[nodiscard]] il2cppClass* FindClass(std::string_view fullName);
    [[nodiscard]] il2cppClass* GetClassFromName(il2cppImage* image, const char* ns, const char* name);
    [[nodiscard]] il2cppType* GetType(il2cppClass* klass);
    [[nodiscard]] il2cppClass* ClassFromType(il2cppType* type);
    [[nodiscard]] il2cppClass* GetParent(il2cppClass* klass);
    [[nodiscard]] il2cppSystemType* GetSystemType(il2cppClass* klass);

    // ---- Field API ----
    [[nodiscard]] il2cppFieldInfo* GetFields(il2cppClass* klass, void** iter);
    [[nodiscard]] il2cppFieldInfo* GetFieldByName(il2cppClass* klass, const char* name);
    [[nodiscard]] int GetFieldOffset(il2cppClass* klass, const char* fieldName);
    void GetStaticFieldValue(il2cppFieldInfo* field, void* outValue);
    void SetStaticFieldValue(il2cppFieldInfo* field, void* value);
    void GetFieldValue(il2cppObject* obj, il2cppFieldInfo* field, void* outValue);
    void SetFieldValue(il2cppObject* obj, il2cppFieldInfo* field, void* value);

    // ---- Method API ----
    [[nodiscard]] il2cppMethodInfo* GetMethods(il2cppClass* klass, void** iter);
    [[nodiscard]] il2cppMethodInfo* GetMethodByName(il2cppClass* klass, const char* name, int argc = -1);
    [[nodiscard]] void* GetMethodPointer(il2cppClass* klass, const char* name, int argc = -1);
    [[nodiscard]] il2cppType* GetMethodParamType(il2cppMethodInfo* method, uint32_t index);
    [[nodiscard]] const char* GetMethodParamName(il2cppMethodInfo* method, uint32_t index);

    // ---- Property API ----
    [[nodiscard]] il2cppPropertyInfo* GetProperties(il2cppClass* klass, void** iter);
    [[nodiscard]] il2cppPropertyInfo* GetPropertyByName(il2cppClass* klass, const char* name);

    // ---- Object ----
    [[nodiscard]] il2cppObject* NewObject(il2cppClass* klass);
    [[nodiscard]] il2cppObject* Box(il2cppClass* klass, void* data);
    il2cppObject* RuntimeInvoke(il2cppMethodInfo* method, void* obj, void** params, void** exc);

    // ---- String ----
    [[nodiscard]] void* StringNew(const char* str);

    // ---- ResolveCall ----
    [[nodiscard]] void* ResolveCall(std::string_view fullPath, bool isExtern = false);

    // ---- Name Stabilization ----
    [[nodiscard]] const char* GetStableName(const char* obfuscatedName);
    [[nodiscard]] const char* GetOriginalName(const char* stableName);

    // ---- Convenience Fetch Helpers ----
    size_t FetchFields(il2cppClass* klass, std::vector<il2cppFieldInfo*>& out);
    size_t FetchMethods(il2cppClass* klass, std::vector<il2cppMethodInfo*>& out);
    size_t FetchClasses(std::vector<il2cppClass*>& out, std::string_view assemblyName);

} // namespace IL2CPP::Module

// ============================================================================
//  High-Level Module API
// ============================================================================

// Reflection: Class, Field, Method, Property, Type handles
#include "Reflection.hpp"

// ManagedObject: high-level il2cppObject wrapper
#include "ManagedObject.hpp"

// Deobfuscation: name stabilization lookups and registration
#include "Deobfuscation.hpp"

// ClassResolver: fluent class/field/method resolution system
#include "ClassResolver.hpp"

// ClassCache: high-level cache with deobfuscated Class handles
#include "ClassCache.hpp"

// MethodHandler: safe resolve + invoke through Core vtable
#include "MethodHandler.hpp"

// Unity wrappers — core hierarchy
#include "Unity/Object.hpp"
#include "Unity/Component.hpp"
#include "Unity/GameObject.hpp"
#include "Unity/Behaviour.hpp"
#include "Unity/MonoBehaviour.hpp"
#include "Unity/Transform.hpp"
#include "Unity/Camera.hpp"
#include "Unity/Rigidbody.hpp"
#include "Unity/Collider.hpp"
#include "Unity/Time.hpp"
#include "Unity/Input.hpp"
#include "Unity/RectTransform.hpp"
#include "Unity/Canvas.hpp"
#include "Unity/CanvasGroup.hpp"

// Unity wrappers — rendering
#include "Unity/Renderer.hpp"
#include "Unity/MeshRenderer.hpp"
#include "Unity/SkinnedMeshRenderer.hpp"
#include "Unity/LineRenderer.hpp"
#include "Unity/TrailRenderer.hpp"
#include "Unity/Light.hpp"
#include "Unity/ParticleSystem.hpp"
#include "Unity/Mesh.hpp"

// Unity wrappers — audio & animation
#include "Unity/AudioSource.hpp"
#include "Unity/AudioClip.hpp"
#include "Unity/Animator.hpp"
#include "Unity/AnimationClip.hpp"
#include "Unity/RuntimeAnimatorController.hpp"
#include "Unity/AnimatorOverrideController.hpp"

// Unity wrappers — physics subtypes
#include "Unity/BoxCollider.hpp"
#include "Unity/SphereCollider.hpp"
#include "Unity/MeshCollider.hpp"

// Unity wrappers — UI hierarchy
#include "Unity/UIBehaviour.hpp"
#include "Unity/Graphic.hpp"
#include "Unity/MaskableGraphic.hpp"
#include "Unity/Image.hpp"
#include "Unity/RawImage.hpp"
#include "Unity/TMP_Text.hpp"
#include "Unity/Selectable.hpp"
#include "Unity/Button.hpp"
#include "Unity/Toggle.hpp"
#include "Unity/Slider.hpp"
#include "Unity/InputField.hpp"
#include "Unity/TMP_InputField.hpp"

// Unity wrappers — UI layout
#include "Unity/CanvasScaler.hpp"
#include "Unity/ContentSizeFitter.hpp"
#include "Unity/LayoutGroup.hpp"
#include "Unity/HorizontalLayoutGroup.hpp"
#include "Unity/VerticalLayoutGroup.hpp"
#include "Unity/LayoutElement.hpp"
#include "Unity/ScrollRect.hpp"
#include "Unity/RectMask2D.hpp"

// Unity wrappers — assets
#include "Unity/Material.hpp"
#include "Unity/Texture2D.hpp"
#include "Unity/Sprite.hpp"
#include "Unity/Resources.hpp"
#include "Unity/AssetBundle.hpp"
#include "Unity/AssetBundleCreateRequest.hpp"

// Unity wrappers — networking & IO
#include "Unity/UnityWebRequest.hpp"
#include "Unity/PlayerPrefs.hpp"

// Unity wrappers — scene management
#include "Unity/SceneManager.hpp"

// .NET wrappers
#include "System/String.hpp"
#include "System/Array.hpp"
#include "System/List.hpp"
#include "System/Dictionary.hpp"
#include "System/HashSet.hpp"
#include "System/Queue.hpp"
#include "System/Stack.hpp"
#include "System/Delegate.hpp"
#include "System/IO.hpp"
#include "System/Encoding.hpp"
