#pragma once
#include "Reflection.hpp"
#include <IL2CPP.Common/il2cpp_shared.hpp>
#include <IL2CPP.Common/il2cpp_structs.hpp>
#include <string_view>
#include <type_traits>

namespace IL2CPP::Module {

    class MethodHandler {
    public:
        MethodHandler() = delete;

        /// Resolve a method by class name, method name, and argument count.
        /// Core caches the result; subsequent calls with the same key are fast lookups.
        /// @param className  Full class name (e.g. "UnityEngine.Canvas")
        /// @param methodName Method name (e.g. "get_renderMode")
        /// @param argc       Expected parameter count (-1 = any)
        /// @return A Method handle wrapping the il2cppMethodInfo*, or invalid Method on failure.
        [[nodiscard]] static Method resolve(
            std::string_view className, std::string_view methodName, int argc = -1);

        /// Invoke a resolved method safely through Core's runtime_invoke.
        /// Core catches exceptions internally and returns nullptr on failure.
        /// @return Raw il2cppObject* result (boxed for value types), or nullptr.
        static void* invoke_raw(const Method& method, void* obj, void** params = nullptr);

        /// Typed invoke convenience wrapper.
        /// - void return: just calls invoke_raw
        /// - Pointer return: reinterpret_cast from result
        /// - Value return: unboxes the result
        /// Returns TReturn{} (default) on null result.
        template<typename TReturn = void>
        static TReturn invoke(const Method& method, void* obj, void** params = nullptr) {
            if constexpr (std::is_void_v<TReturn>) {
                invoke_raw(method, obj, params);
            } else {
                void* result = invoke_raw(method, obj, params);
                if (!result) return TReturn{};
                if constexpr (std::is_pointer_v<TReturn>)
                    return reinterpret_cast<TReturn>(result);
                else
                    return *reinterpret_cast<TReturn*>(IL2CPP::Unbox(result));
            }
        }
    };

} // namespace IL2CPP::Module
