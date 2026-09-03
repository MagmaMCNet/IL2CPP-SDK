#pragma once

#include <unix/module.hpp>

// One release only: the pre-7.0 spellings, so a consumer that names the old types keeps
// compiling. Deleted in 7.1 along with UNIx::Config's snake_case forwarders.
namespace Bootstrap::Module {

using ModuleConfig [[deprecated("use UNIx::Config")]] = ::UNIx::Config;

using Page         = ::UNIx::UIPage;
using SubPage      = ::UNIx::UISubPage;
using Button       = ::UNIx::UIButton;
using Toggle       = ::UNIx::UIToggle;
using Slider       = ::UNIx::UISlider;
using EnumSelector = ::UNIx::UIEnumSelector;
using Foldout      = ::UNIx::UIFoldout;
using Menu         = ::UNIx::Menu;

} // namespace Bootstrap::Module
