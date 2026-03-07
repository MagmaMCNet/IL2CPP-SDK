#pragma once
#include "MaskableGraphic.hpp"
#include "../MethodHandler.hpp"
#include <IL2CPP.Common/il2cpp_types.hpp>
#include <IL2CPP.Common/il2cpp_shared.hpp>
#include <string>
#include <string_view>
#include <Windows.h>

namespace IL2CPP::Module::Unity {

    class TMP_Text : public MaskableGraphic {
    public:
        using MaskableGraphic::MaskableGraphic;

        // ---- text (get) ----
        [[nodiscard]] std::string GetText() const {
            static auto m = MethodHandler::resolve("TMPro.TMP_Text", "get_text", 0);
            void* str = MethodHandler::invoke<void*>(m, raw());
            if (!str) return "";
            int len = *reinterpret_cast<int*>(static_cast<char*>(str) + 0x10);
            if (len <= 0) return "";
            const wchar_t* wstr = reinterpret_cast<const wchar_t*>(static_cast<char*>(str) + 0x14);
            int bytes = WideCharToMultiByte(CP_UTF8, 0, wstr, len, nullptr, 0, nullptr, nullptr);
            if (bytes <= 0) return "";
            std::string out(static_cast<size_t>(bytes), '\0');
            WideCharToMultiByte(CP_UTF8, 0, wstr, len, out.data(), bytes, nullptr, nullptr);
            return out;
        }

        // ---- text (set) ----
        void SetText(std::string_view value) {
            static auto m = MethodHandler::resolve("TMPro.TMP_Text", "set_text", 1);
            auto* e = GetExports();
            if (!e || !e->m_stringNew) return;
            void* il2cppStr = reinterpret_cast<void*(IL2CPP_CALLTYPE)(const char*)>(
                e->m_stringNew)(std::string(value).c_str());
            void* params[] = { il2cppStr };
            MethodHandler::invoke(m, raw(), params);
        }

        // ---- fontSize ----
        [[nodiscard]] float GetFontSize() const {
            static auto m = MethodHandler::resolve("TMPro.TMP_Text", "get_fontSize", 0);
            return MethodHandler::invoke<float>(m, raw());
        }
        void SetFontSize(float value) {
            static auto m = MethodHandler::resolve("TMPro.TMP_Text", "set_fontSize", 1);
            void* params[] = { &value };
            MethodHandler::invoke(m, raw(), params);
        }

        // ---- color ----
        [[nodiscard]] Color GetColor() const {
            static auto m = MethodHandler::resolve("TMPro.TMP_Text", "get_color", 0);
            return MethodHandler::invoke<Color>(m, raw());
        }
        void SetColor(const Color& value) {
            static auto m = MethodHandler::resolve("TMPro.TMP_Text", "set_color", 1);
            Color c = value;
            void* params[] = { &c };
            MethodHandler::invoke(m, raw(), params);
        }

        // ---- alignment ----
        [[nodiscard]] int GetAlignment() const {
            static auto m = MethodHandler::resolve("TMPro.TMP_Text", "get_alignment", 0);
            return MethodHandler::invoke<int>(m, raw());
        }
        void SetAlignment(int value) {
            static auto m = MethodHandler::resolve("TMPro.TMP_Text", "set_alignment", 1);
            void* params[] = { &value };
            MethodHandler::invoke(m, raw(), params);
        }

        // ---- enableWordWrapping ----
        [[nodiscard]] bool GetEnableWordWrapping() const {
            static auto m = MethodHandler::resolve("TMPro.TMP_Text", "get_enableWordWrapping", 0);
            return MethodHandler::invoke<bool>(m, raw());
        }
        void SetEnableWordWrapping(bool value) {
            static auto m = MethodHandler::resolve("TMPro.TMP_Text", "set_enableWordWrapping", 1);
            void* params[] = { &value };
            MethodHandler::invoke(m, raw(), params);
        }

        // ---- fontStyle ----
        [[nodiscard]] int GetFontStyle() const {
            static auto m = MethodHandler::resolve("TMPro.TMP_Text", "get_fontStyle", 0);
            return MethodHandler::invoke<int>(m, raw());
        }
        void SetFontStyle(int value) {
            static auto m = MethodHandler::resolve("TMPro.TMP_Text", "set_fontStyle", 1);
            void* params[] = { &value };
            MethodHandler::invoke(m, raw(), params);
        }

        // ---- richText ----
        [[nodiscard]] bool GetRichText() const {
            static auto m = MethodHandler::resolve("TMPro.TMP_Text", "get_richText", 0);
            return MethodHandler::invoke<bool>(m, raw());
        }
        void SetRichText(bool value) {
            static auto m = MethodHandler::resolve("TMPro.TMP_Text", "set_richText", 1);
            void* params[] = { &value };
            MethodHandler::invoke(m, raw(), params);
        }

        // ---- SetText (method, takes string param) ----
        void CallSetText(std::string_view text) {
            static auto m = MethodHandler::resolve("TMPro.TMP_Text", "SetText", 1);
            auto* e = GetExports();
            if (!e || !e->m_stringNew) return;
            void* il2cppStr = reinterpret_cast<void*(IL2CPP_CALLTYPE)(const char*)>(
                e->m_stringNew)(std::string(text).c_str());
            void* params[] = { il2cppStr };
            MethodHandler::invoke(m, raw(), params);
        }

        // ---- ForceMeshUpdate ----
        void ForceMeshUpdate() {
            static auto m = MethodHandler::resolve("TMPro.TMP_Text", "ForceMeshUpdate", 0);
            MethodHandler::invoke(m, raw());
        }
    };

} // namespace IL2CPP::Module::Unity
