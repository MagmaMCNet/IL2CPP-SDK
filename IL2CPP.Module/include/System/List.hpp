#pragma once
#include "Array.hpp"

namespace IL2CPP::Module::System {

    template<typename T>
    class List : public ManagedObject {
        static constexpr int kItemsOffset   = 0x10;  // il2cppArray<T>*
        static constexpr int kSizeOffset    = 0x18;  // int m_iSize
        static constexpr int kVersionOffset = 0x1C;  // int m_iVersion

    public:
        using ManagedObject::ManagedObject;

        /// Get the internal array as an Array<T> handle.
        [[nodiscard]] Array<T> items() const {
            if (!valid()) return Array<T>{};
            return Array<T>{ read<void*>(kItemsOffset) };
        }

        /// Get the list count (logical size, not capacity).
        [[nodiscard]] int count() const {
            if (!valid()) return 0;
            return read<int>(kSizeOffset);
        }

        [[nodiscard]] bool empty() const { return count() == 0; }

        /// Access by index through the internal array.
        [[nodiscard]] T& operator[](uintptr_t i) { return items()[i]; }
        [[nodiscard]] const T& operator[](uintptr_t i) const { return items()[i]; }

        /// Safe access.
        [[nodiscard]] T* try_at(uintptr_t i) { return items().try_at(i); }

        /// Get as std::span (uses internal array size, not logical count).
        [[nodiscard]] std::span<T> as_span() { return items().as_span(); }
        [[nodiscard]] std::span<const T> as_span() const { return items().as_span(); }


        [[nodiscard]] T* begin() { return items().begin(); }
        [[nodiscard]] T* end() { return items().end(); }
        [[nodiscard]] const T* begin() const { return items().begin(); }
        [[nodiscard]] const T* end() const { return items().end(); }

        /// Convert to std::vector.
        [[nodiscard]] std::vector<T> to_vector() const { return items().to_vector(); }
    };

} // namespace IL2CPP::Module::System
