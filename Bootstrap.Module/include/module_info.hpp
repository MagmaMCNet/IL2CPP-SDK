#pragma once
// ============================================================================
//  module_info.hpp - Declares a packed PE export for module metadata
//
//  Usage (one line in your mod's .cpp):
//      #include <Bootstrap.Module/include/module_info.hpp>
//      UNIX_MODULE_INFO("MyCoolMod", "1.2.0");
//
//  The macro creates an exported symbol "_CLUE_" containing:
//      "UNIx"  \x01  name  \x00  version  \x00  sdk_version
//       magic   fmt         sep            sep
//
//  The UNIxLoader reads this export by parsing the PE on disk (no loading)
//  to display the mod name, version, and SDK compatibility in the UI.
// ============================================================================

#include <Bootstrap.Common/include/sdk_version.hpp>

// Internal helper to concatenate the packed string at compile time
#define _UNIX_MODULE_INFO_CONCAT(name, version) \
    "UNIx\x01" name "\0" version "\0" UNIX_SDK_VERSION_STR

/// Declare module metadata visible to UNIxLoader.
/// Must appear exactly once per module DLL, at file scope.
///   UNIX_MODULE_INFO("MyMod", "1.0.0");
#define UNIX_MODULE_INFO(name, version) \
    extern "C" __declspec(dllexport) \
    const char _CLUE_[] = _UNIX_MODULE_INFO_CONCAT(name, version)
