#pragma once
#include "Array.hpp"
#include <functional>
#include <vector>

// ============================================================================
//  IL2CPP.Module::System::HashSet<T>
//
//  Wraps il2cppHashSet<T>. Provides element iteration and lookup.
//
//  Layout (after il2cppObject 0x10):
//    int* buckets           (+0x10)
//    Slot* slots            (+0x18)  // Slot = { int hashCode, int next, T value }
//    int count              (+0x20)
//    int lastIndex          (+0x24)
//    int freeList           (+0x28)
//    void* comparer         (+0x30)
// ============================================================================

namespace IL2CPP::Module::System {

    template<typename T>
    class HashSet : public ManagedObject {
    public:
        struct Slot {
            int     hashCode;
            int     next;
            T       value;
        };

    private:
        static constexpr int kBucketsOffset   = 0x10;
        static constexpr int kSlotsOffset     = 0x18;
        static constexpr int kCountOffset     = 0x20;
        static constexpr int kLastIndexOffset = 0x24;
        static constexpr int kFreeListOffset  = 0x28;

        [[nodiscard]] Array<Slot> slots() const {
            if (!valid()) return Array<Slot>{};
            return Array<Slot>{ read<void*>(kSlotsOffset) };
        }

    public:
        using ManagedObject::ManagedObject;

        /// Get the number of active elements.
        [[nodiscard]] int count() const {
            if (!valid()) return 0;
            return read<int>(kCountOffset);
        }

        [[nodiscard]] int last_index() const {
            if (!valid()) return 0;
            return read<int>(kLastIndexOffset);
        }

        [[nodiscard]] bool empty() const { return count() == 0; }

        /// Check if the set contains a value (linear scan).
        [[nodiscard]] bool contains(const T& value) const {
            auto s = slots();
            if (!s) return false;
            int limit = last_index();
            int cap = static_cast<int>(s.size());
            if (limit > cap) limit = cap;
            const Slot* data = s.data();
            if (!data) return false;
            for (int i = 0; i < limit; ++i) {
                if (data[i].hashCode >= 0 && data[i].value == value)
                    return true;
            }
            return false;
        }

        /// Iterate all active elements.
        template<typename Func>
        void for_each(Func f) {
            auto s = slots();
            if (!s) return;
            int limit = last_index();
            int cap = static_cast<int>(s.size());
            if (limit > cap) limit = cap;
            Slot* data = s.data();
            if (!data) return;
            for (int i = 0; i < limit; ++i) {
                if (data[i].hashCode >= 0)
                    f(data[i].value);
            }
        }

        /// Iterate all active elements (const).
        template<typename Func>
        void for_each(Func f) const {
            auto s = slots();
            if (!s) return;
            int limit = last_index();
            int cap = static_cast<int>(s.size());
            if (limit > cap) limit = cap;
            const Slot* data = s.data();
            if (!data) return;
            for (int i = 0; i < limit; ++i) {
                if (data[i].hashCode >= 0)
                    f(data[i].value);
            }
        }

        /// Convert to std::vector.
        [[nodiscard]] std::vector<T> to_vector() const {
            std::vector<T> result;
            result.reserve(count());
            for_each([&](const T& v) { result.push_back(v); });
            return result;
        }
    };

} // namespace IL2CPP::Module::System
