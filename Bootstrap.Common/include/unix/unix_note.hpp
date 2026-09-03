#pragma once
#include <cstdint>
#include <string>
#include "unix_module_abi.hpp"

namespace UNIx {

/// <summary>Owning host-side mirror of unix_bind_note. It outlives the bind call and is
/// shipped to the loader afterwards, so it holds allocated strings where the wire form
/// holds borrowed unix_str views; ToWire is the one conversion between them.</summary>
struct Note {
    unix_note_kind kind{};
    std::string    symbol;
    std::string    replacement;
    std::string    message;
    std::string    code;
    uint32_t       since     = 0;
    uint32_t       removal   = 0;          // removal, or the version it was removed in
    uint32_t       have      = 0;          // host_sdk
    uint32_t       want      = 0;          // the module's sdk_built
    uint32_t       req_index = 0xFFFFFFFFu; // 0xFFFFFFFF = module-level
};

} // namespace UNIx
