#pragma once

#include <Bootstrap.Common/include/bootstrap_shared.hpp>

namespace Bootstrap::Module {

    [[nodiscard]] bool is_connected() noexcept;
    [[nodiscard]] Bootstrap::BootstrapVtable const* get_vtable() noexcept;

} // namespace Bootstrap::Module
