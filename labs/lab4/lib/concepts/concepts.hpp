#pragma once

#include <type_traits>

namespace concepts {

template<class T>
concept Scalar = std::is_arithmetic_v<T>;

}
