#pragma once
#include <cstdint>

// Single source of truth for SDK version — change this one number
#define UNIX_SDK_MAJOR 5
#define UNIX_SDK_MINOR 0
#define UNIX_SDK_PATCH 0

// Stringify helper
#define _UNIX_STR(x) #x
#define _UNIX_XSTR(x) _UNIX_STR(x)
#define UNIX_SDK_VERSION_STR _UNIX_XSTR(UNIX_SDK_MAJOR)

namespace Bootstrap {

    constexpr uint32_t sdk_major = UNIX_SDK_MAJOR;
    constexpr uint32_t sdk_minor = UNIX_SDK_MINOR;
    constexpr uint32_t sdk_patch = UNIX_SDK_PATCH;
    constexpr uint32_t sdk_version = sdk_major;

} // namespace Bootstrap
