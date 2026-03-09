#include <include/VRChat/LocalizableString.hpp>
#include <IL2CPP.Module/include/System/String.hpp>

namespace IL2CPP::VRChat {

    // ---- Properties ----

    std::string LocalizableString::GetKey() {
        return call_string_method("get_Key");
    }

    std::string LocalizableString::GetFallbackText() {
        return call_string_method("get_FallbackText");
    }

    bool LocalizableString::HasKey() {
        if (!valid()) return false;
        return call_method<bool>("get_HasKey");
    }

    bool LocalizableString::IsLocalized() {
        if (!valid()) return false;
        return call_method<bool>("get_IsLocalized");
    }

    bool LocalizableString::IsEmpty() {
        if (!valid()) return true;
        return call_method<bool>("get_IsEmpty");
    }

    // ---- Methods ----

    std::string LocalizableString::ToString() {
        return call_string_method("ToString");
    }

    std::string LocalizableString::GetTranslation(bool& success) {
        if (!valid()) { success = false; return {}; }
        auto klass = get_class();
        if (!klass) { success = false; return {}; }
        auto m = klass.get_method("GetTranslation", 1);
        if (!m) { success = false; return {}; }
        bool outSuccess = false;
        void* params[1] = { &outSuccess };
        void* result = m.invoke(raw(), params);
        success = outSuccess;
        if (!result) return {};
        return IL2CPP::Module::System::String(result).to_string();
    }

    // ---- Static ----

    LocalizableString LocalizableString::Empty() {
        static auto klass = IL2CPP::Module::Class::find("VRC.Localization.LocalizableString");
        if (!klass) return LocalizableString{};
        auto m = klass.get_method("get_Empty", 0);
        if (!m) return LocalizableString{};
        void* result = m.invoke(nullptr, nullptr);
        return LocalizableString{ result };
    }

    // ---- Construction helpers (LocalizableStringExtensions) ----

    namespace {
        IL2CPP::Module::Class extensions_class() {
            static auto c = IL2CPP::Module::Class::find("VRC.Localization.LocalizableStringExtensions");
            return c;
        }
    }

    LocalizableString LocalizableString::Localize(std::string_view text) {
        auto k = extensions_class();
        if (!k) return LocalizableString{};
        auto m = k.get_method("Localize", 1);
        if (!m) return LocalizableString{};
        auto str = IL2CPP::Module::System::String::create(text);
        void* params[1] = { str.raw() };
        void* result = m.invoke(nullptr, params);
        return LocalizableString{ result };
    }

    LocalizableString LocalizableString::LocalizeWithFallback(std::string_view key, std::string_view fallback) {
        auto k = extensions_class();
        if (!k) return LocalizableString{};
        auto m = k.get_method("Localize", 2);
        if (!m) return LocalizableString{};
        auto keyStr = IL2CPP::Module::System::String::create(key);
        auto fallbackStr = IL2CPP::Module::System::String::create(fallback);
        void* params[2] = { keyStr.raw(), fallbackStr.raw() };
        void* result = m.invoke(nullptr, params);
        return LocalizableString{ result };
    }

    LocalizableString LocalizableString::NoTranslation(std::string_view text) {
        auto k = extensions_class();
        if (!k) return LocalizableString{};
        auto m = k.get_method("NoTranslation", 1);
        if (!m) return LocalizableString{};
        auto str = IL2CPP::Module::System::String::create(text);
        void* params[1] = { str.raw() };
        void* result = m.invoke(nullptr, params);
        return LocalizableString{ result };
    }

} // namespace IL2CPP::VRChat
