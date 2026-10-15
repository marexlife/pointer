#ifndef POINTER_INTRUSIVE_POINTERLIST_H
#define POINTER_INTRUSIVE_POINTERLIST_H
#include "pointed_object.h"
#include <cstddef>
#include <type_traits>

namespace pointer::intrusive {
template <typename T>
    requires(!std::is_reference_v<T>)
struct PointerList {
    PointedObject<T> pointed_object{};
    std::size_t len{};
};
} // namespace pointer::intrusive
#endif // POINTER_INTRUSIVE_POINTERLIST_H
