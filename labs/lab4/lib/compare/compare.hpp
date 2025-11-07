#pragma once

#include <type_traits>

#include "concepts.hpp"

namespace compare {
template <concepts::Scalar T>
constexpr bool AreNumbersEqual(T a, T b);
}

#include "compare.ipp"
