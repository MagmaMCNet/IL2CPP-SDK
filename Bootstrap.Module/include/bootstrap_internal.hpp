#pragma once

// ============================================================================
//  bootstrap_internal.hpp - Internal accessors for Bootstrap.Module
//
//  Used by VRChat class implementations to access the shared vtable.
//  Not part of the public API - do not include from consumer code.
// ============================================================================

#include <Bootstrap.Common/include/bootstrap_shared.hpp>

namespace Bootstrap::Module {

    [[nodiscard]] bool is_connected() noexcept;
    [[nodiscard]] Bootstrap::BootstrapVtable const* get_vtable() noexcept;

} // namespace Bootstrap::Module
