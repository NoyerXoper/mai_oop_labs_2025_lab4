#include "compare.hpp"

#include <limits>

namespace compare {
namespace {
constexpr double KOEFFITSIENT = 128;

template<concepts::FloatingPoint T>
struct Eps {
    constexpr static T EPS = KOEFFITSIENT * std::numeric_limits<T>::epsilon();
};

template<concepts::FloatingPoint T>
using Eps_v = Eps<T>::EPS;

}
template<concepts::Scalar T>
constexpr inline bool AreNumbersEqual(T a, T b) {
    if constexpr (std::is_floating_point_v<T>) {
        if (a == b) return true;

        T diff = std::abs(a - b);
        T norm = std::min(std::abs(a + b), std::numeric_limits<T>::max());

        return diff < std::max(norm * Eps_v<T>, std::numeric_limits<T>::epsilon());
    } else {
        return a == b;
    }
}
}