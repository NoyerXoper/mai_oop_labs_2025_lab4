#include "compare.hpp"

#include <limits>

namespace compare {
namespace {
constexpr double KOEFFITSIENT = 64;

template <concepts::FloatingPoint T>
constexpr T Eps_v = KOEFFITSIENT* std::numeric_limits<T>::epsilon();

}  // namespace
template <concepts::Scalar T>
constexpr bool AreNumbersEqual(T a, T b) {
    if constexpr (std::is_floating_point_v<T>) {
        if (std::isnan(a) || std::isnan(b)) {
            return false;
        }

        if (std::isinf(a) || std::isinf(b)) {
            return false;
        }

        if (a == b) {
            return true;
        }
        T diff = std::abs(a - b);

        if (diff < Eps_v<T>) {
            return true;
        }

        if (std::max(std::abs(a), std::abs(b)) <
            std::numeric_limits<T>::min() * 100) {
            return diff <= Eps_v<T>;
        }

        T magnitude = std::max(std::abs(a), std::abs(b));

        return diff <= magnitude * Eps_v<T>;
    } else {
        return a == b;
    }
}
}  // namespace compare