#pragma once

#include <type_traits>

namespace concepts {

template <class T>
concept Scalar = std::is_arithmetic_v<T>;

template <class T>
concept FloatingPoint = std::is_floating_point_v<T>;

}  // namespace concepts
