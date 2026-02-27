#pragma once
#include <Hooking.Common/hook_shared.hpp>
#include <string_view>
#include <string>
#include <utility>
#include <tuple>
#include <type_traits>

namespace Hooking::Module {

    [[nodiscard]] bool Connect();
    void Disconnect();
    [[nodiscard]] bool is_connected() noexcept;

    class HookModule {
    public:
        HookModule() = default;
        explicit HookModule(std::string_view name);
        ~HookModule();

        HookModule(HookModule const&) = delete;
        HookModule& operator=(HookModule const&) = delete;
        HookModule(HookModule&& other) noexcept;
        HookModule& operator=(HookModule&& other) noexcept;

        [[nodiscard]] bool valid() const noexcept;
        [[nodiscard]] uint32_t id() const noexcept;
        [[nodiscard]] std::string_view name() const noexcept;

        /// Create a Detour hook
        ///
        /// Usage:
        ///   using fn_t = void(*)(int, float);
        ///   fn_t original = nullptr;
        ///   void my_detour(int a, float b) { original(a, b); }
        ///   auto hid = mod.create_detour<fn_t>("MyHook", target_ptr, my_detour, &original);
        template<typename FnPtr>
        uint32_t create_detour(std::string_view hook_name,
                               FnPtr target,
                               FnPtr detour,
                               FnPtr* out_original);

        /// Create a Prefix hook
        ///
        /// Callback signature: bool callback(OrigArgs..., ReturnType& __retval)
        ///   Return true  → continue to call the original function.
        ///   Return false → skip the original; use __retval as the return value.
        ///
        /// For void-returning functions, use a dummy void*& parameter.
        ///
        /// Usage:
        ///   bool my_prefix(int a, float b, int& __retval) {
        ///       if (a == 42) { __retval = -1; return false; }
        ///       return true;
        ///   }
        ///   auto hid = mod.create_prefix("MyPrefix", target_ptr, my_prefix);
        template<typename CallbackFn>
        uint32_t create_prefix(std::string_view hook_name,
                               void* target,
                               CallbackFn callback);

        /// Create a Suffix hook
        ///
        /// Callback signature: void callback(OrigArgs..., ReturnType& __retval)
        /// Receives all original args + the return value by reference.
        /// Can inspect or modify the return value after the original runs.
        ///
        /// Usage:
        ///   void my_suffix(int a, float b, int& __retval) {
        ///       __retval *= 2;
        ///   }
        ///   auto hid = mod.create_suffix("MySuffix", target_ptr, my_suffix);
        template<typename CallbackFn>
        uint32_t create_suffix(std::string_view hook_name,
                               void* target,
                               CallbackFn callback);

        bool remove_hook(uint32_t hook_id);
        bool enable_hook(uint32_t hook_id);
        bool disable_hook(uint32_t hook_id);

        void enable_all();
        void disable_all();

        [[nodiscard]] HookStatus get_hook_status(uint32_t hook_id) const;
        [[nodiscard]] uint32_t   get_hook_count() const;
        [[nodiscard]] bool       get_hook_info(uint32_t hook_id, HookInfo* out) const;

        /// Register a UI render callback.
        /// Called each frame inside the hooked Present, with the full D3D11 context.
        /// The module is responsible for its own ImGui/rendering setup.
        ///
        /// Usage:
        ///   void my_render(Hooking::UiRenderContext const* ctx) {
        ///       auto* swap  = static_cast<IDXGISwapChain*>(ctx->swap_chain);
        ///       auto* dev   = static_cast<ID3D11Device*>(ctx->device);
        ///       // ImGui::NewFrame(), draw, ImGui::Render(), etc.
        ///   }
        ///   auto rid = mod.register_render(my_render);
        uint32_t register_render(fn_ui_render_callback callback);
        void unregister_render(uint32_t callback_id);

        /// Register a resize callback.
        /// Called BEFORE the original ResizeBuffers — release your render targets here.
        ///
        /// Usage:
        ///   void my_resize(uint32_t new_w, uint32_t new_h) {
        ///       if (my_render_target) { my_render_target->Release(); my_render_target = nullptr; }
        ///   }
        ///   auto rid = mod.register_resize(my_resize);
        uint32_t register_resize(fn_ui_resize_callback callback);
        void unregister_resize(uint32_t callback_id);

        /// Register a WndProc callback.
        /// Return true from the callback to consume the message.
        ///
        /// Usage:
        ///   bool my_wndproc(void* hwnd, uint32_t msg, uintptr_t wp, intptr_t lp) {
        ///       if (my_ui_visible) return true;
        ///       return false;
        ///   }
        ///   auto wid = mod.register_wndproc(my_wndproc);
        uint32_t register_wndproc(fn_ui_wndproc_callback callback);
        void unregister_wndproc(uint32_t callback_id);

    private:
        uint32_t    m_id = invalid_id;
        std::string m_name;
    };

    [[nodiscard]] uint32_t get_module_count();
    [[nodiscard]] bool     get_module_info(uint32_t module_id, ModuleInfo* out);

    /// Check if the UI rendering pipeline has discovered the D3D11 device.
    [[nodiscard]] bool is_ui_ready();

    template<typename FnPtr>
    uint32_t HookModule::create_detour(std::string_view hook_name,
                                        FnPtr target,
                                        FnPtr detour,
                                        FnPtr* out_original) {
        if (!valid() || !is_connected()) return invalid_id;

        extern HookVtable const* get_connection_vtable() noexcept;
        auto* vt = get_connection_vtable();
        if (!vt) return invalid_id;

        void* trampoline = nullptr;
        uint32_t hid = vt->create_detour(
            m_id,
            hook_name.data(), static_cast<uint32_t>(hook_name.size()),
            reinterpret_cast<void*>(target),
            reinterpret_cast<void*>(detour),
            &trampoline);

        if (hid != invalid_id && out_original)
            *out_original = reinterpret_cast<FnPtr>(trampoline);

        return hid;
    }

    template<typename CallbackFn>
    uint32_t HookModule::create_prefix(std::string_view hook_name,
                                         void* target,
                                         CallbackFn callback) {
        if (!valid() || !is_connected()) return invalid_id;

        extern HookVtable const* get_connection_vtable() noexcept;
        auto* vt = get_connection_vtable();
        if (!vt) return invalid_id;

        return vt->create_prefix(
            m_id,
            hook_name.data(), static_cast<uint32_t>(hook_name.size()),
            target,
            reinterpret_cast<void*>(callback));
    }

    template<typename CallbackFn>
    uint32_t HookModule::create_suffix(std::string_view hook_name,
                                         void* target,
                                         CallbackFn callback) {
        if (!valid() || !is_connected()) return invalid_id;

        extern HookVtable const* get_connection_vtable() noexcept;
        auto* vt = get_connection_vtable();
        if (!vt) return invalid_id;

        return vt->create_suffix(
            m_id,
            hook_name.data(), static_cast<uint32_t>(hook_name.size()),
            target,
            reinterpret_cast<void*>(callback));
    }

}
