#pragma once
#include <atomic>
#include <cstdint>
#include <string>
#include <string_view>

namespace IL2CPP::Module {

    /// <summary>Records bindings that failed to resolve, so a miss is diagnosable instead of a silent null.</summary>
    class BindMiss {
    public:
        static constexpr uint32_t kCapacity = 64;
        static constexpr uint32_t kNameMax  = 128;

        /// <summary>Records a failed binding. Allocation-free and safe to call from a magic-static initialiser.</summary>
        static void Record(std::string_view klass, std::string_view member, int argc) noexcept;

        /// <summary>Total misses recorded, including any beyond the retained capacity.</summary>
        [[nodiscard]] static uint32_t Count() noexcept;

        /// <summary>Distinct misses retained for reporting.</summary>
        [[nodiscard]] static uint32_t Retained() noexcept;

        /// <summary>Formats the retained misses as one line per binding. Allocates; never call from a resolve path.</summary>
        [[nodiscard]] static std::string Report();

        static void Reset() noexcept;
    };

    /// <summary>One-line summary of binding health for logging at init.</summary>
    [[nodiscard]] std::string SelfTest();

}
