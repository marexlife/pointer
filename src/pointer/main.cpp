#include "pointer/intrusive/pointed_object.h"
#include "pointer/intrusive/pointer_list.h"
#include <cstdint>
#include <print>

int main() {
    pointer::intrusive::PointerList<std::int32_t> pointed_list;
    pointer::intrusive::PointedObject<std::int32_t> pointed_object;

    std::println("Hi");
}
