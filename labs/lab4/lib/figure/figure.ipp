#include "figure.hpp"

namespace geometry {
template<concepts::Scalar T>
std::ostream& operator<<(std::ostream& out, const Figure<T>& figure) {
    figure.Print(out);
    return out;
}

template<concepts::Scalar T>
std::istream& operator>>(std::istream& in, Figure<T>& figure) {
    figure.Read(in);
    return in;
}
}