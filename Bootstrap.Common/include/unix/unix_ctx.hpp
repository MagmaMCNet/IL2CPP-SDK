#pragma once
#include "unix_module_abi.hpp"

// One per image: a module DLL, a .ux image and Bootstrap itself each hold their own.
namespace UNIx::detail {

inline const unix_context* g_ctx{};

/// <summary>Publish the context this image reaches the host through. A module's
/// bind sets it; the host seeds its own so the statically linked shims can connect
/// before any module has loaded.</summary>
inline void SetContext(const unix_context* ctx) noexcept { g_ctx = ctx; }

/// <summary>The context this image was given, or null before it is published.</summary>
[[nodiscard]] inline const unix_context* Context() noexcept { return g_ctx; }

} // namespace UNIx::detail
