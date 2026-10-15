#ifndef POINTER_CONTAINER_VECTOR_H
#define POINTER_CONTAINER_VECTOR_H
#include <cstddef>
#include <cstring>
#include <memory>
#include <type_traits>

namespace pointer::containter {
template <typename T, std::size_t MaxStackLen = 100,
          std::size_t GrothAmount = 10, typename Alloc = std::allocator<T>>
class Vector final {
  public:
    Vector() = default;

    template <typename PushedType>
        requires std::is_rvalue_reference_v<PushedType> &&
                 std::is_move_constructible_v<PushedType>
    void emplace_back(PushedType value) {
        auto target_len = len_ + 1;
        if (target_len > MaxStackLen) {
            allocate_to_heap();
        }

        if (!is_heap_) {
            stack_data_[target_len] = std::move(value);
            len_ = target_len;
            return;
        }

        if (target_len >= heap_data_.cap) [[unlikely]] {
            grow();
        }

        heap_data_.elements[target_len] = std::move(value);
        len_ = target_len;
    }

    Vector(Vector &&) = delete;
    Vector &operator=(Vector &&) = delete;
    Vector(const Vector &) = delete;
    Vector &operator=(const Vector &) = delete;

    ~Vector() {
        if (is_heap_) {
            return;
        }

        allocator_.deallocate(heap_data_.elements, heap_data_.cap);
    }

  private:
    void grow() {
        heap_data_.cap *= GrothAmount;
        void *new_elements = allocator_.allocate(sizeof(T) * heap_data_.cap);
        std::memcpy(new_elements, heap_data_.elements, heap_data_.cap);
        allocator_.deallocate(heap_data_.elements, heap_data_.cap);
        heap_data_.elements = new_elements;
    }

    void allocate_to_heap() noexcept {
        is_heap_ = true;

        heap_data_.cap *= GrothAmount;
        heap_data_.elements = allocator_.allocate(heap_data_.cap);
        std::memcpy(heap_data_.elements, stack_data_, len_);
    }

    struct HeapData {
        T *elements = nullptr;
        std::size_t cap = 0;
    };

    Alloc allocator_{};
    T stack_data_[MaxStackLen] = {};
    HeapData heap_data_{};
    std::size_t len_ = 0;
    bool is_heap_ = false;
};
} // namespace pointer::containter
#endif // POINTER_CONTAINER_VECTOR_H
