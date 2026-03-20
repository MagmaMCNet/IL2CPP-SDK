#pragma once
#include "../MethodHandler.hpp"
#include <IL2CPP.Common/il2cpp_types.hpp>
#include <IL2CPP.Common/il2cpp_shared.hpp>
#include <string>
#include <string_view>
#include <Windows.h>

namespace IL2CPP::Module {
    [[nodiscard]] IL2CPP::il2cpp_exports const* GetExports() noexcept;
}

namespace IL2CPP::Module::Unity {

    class LayerMaskUtils {
    public:
        LayerMaskUtils() = delete;

        /// Convert a layer index to its name.
        [[nodiscard]] static std::string layer_to_name(int layer) {
            static auto m = MethodHandler::resolve("UnityEngine.LayerMask", "LayerToName", 1);
            void* params[] = { &layer };
            void* str = MethodHandler::invoke<void*>(m, nullptr, params);
            if (!str) return "";
            int len = *reinterpret_cast<int*>(static_cast<char*>(str) + 0x10);
            if (len <= 0) return "";
            wchar_t* wstr = reinterpret_cast<wchar_t*>(static_cast<char*>(str) + 0x14);
            int bytes = WideCharToMultiByte(CP_UTF8, 0, wstr, len, nullptr, 0, nullptr, nullptr);
            if (bytes <= 0) return "";
            std::string out(static_cast<size_t>(bytes), '\0');
            WideCharToMultiByte(CP_UTF8, 0, wstr, len, out.data(), bytes, nullptr, nullptr);
            return out;
        }

        /// Convert a layer name to its index.
        [[nodiscard]] static int name_to_layer(std::string_view name) {
            static auto m = MethodHandler::resolve("UnityEngine.LayerMask", "NameToLayer", 1);
            auto* exports = GetExports();
            if (!exports || !exports->m_stringNew) return -1;
            void* il2cppStr = reinterpret_cast<void*(IL2CPP_CALLTYPE)(const char*)>(exports->m_stringNew)(
                std::string(name).c_str());
            void* params[] = { il2cppStr };
            return MethodHandler::invoke<int>(m, nullptr, params);
        }


        [[nodiscard]] static LayerMask from_layer(int layer) {
            return LayerMask(1 << layer);
        }
        [[nodiscard]] static LayerMask from_name(std::string_view name) {
            int layer = name_to_layer(name);
            if (layer < 0) return LayerMask(0);
            return LayerMask(1 << layer);
        }
        [[nodiscard]] static LayerMask combine(LayerMask a, LayerMask b) {
            return LayerMask(a.value() | b.value());
        }
        [[nodiscard]] static bool contains_layer(LayerMask mask, int layer) {
            return (mask.value() & (1 << layer)) != 0;
        }
        [[nodiscard]] static LayerMask invert(LayerMask mask) {
            return LayerMask(~mask.value());
        }
        [[nodiscard]] static LayerMask all() {
            return LayerMask(-1);
        }
        [[nodiscard]] static LayerMask none() {
            return LayerMask(0);
        }
        [[nodiscard]] static LayerMask default_layer() {
            return LayerMask(1);
        }
    };

} // namespace IL2CPP::Module::Unity
