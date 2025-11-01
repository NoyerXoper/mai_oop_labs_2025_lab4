#include "point.hpp"

namespace geometry {
template<concepts::Scalar T>
Point<T>::Point() noexcept: Point(0, 0);

template<concepts::Scalar T>
Point<T>::Point(T x, T y) noexcept: x(x), y(y);

template<concepts::Scalar T>
constexpr inline Point<T>& Point<T>::operator+=(const Point<T>& other) noexcept {
    x += other.x;
    y += other.y;
    return *this;
}

template<concepts::Scalar T>
constexpr inline Point<T>& Point<T>::operator-=(const Point<T>& other) noexcept {
    x -= other.x;
    y -= other.y;
    return *this;
}

template<concepts::Scalar T>
constexpr inline Point<T>& Point<T>::operator*=(T number) noexcept {
    x *= number;
    y *= number;
    return *this;
}
template<concepts::Scalar T>
constexpr inline Point<T>& Point<T>::operator/=(T number) noexcept {
    x /= number;
    y /= number;
    return *this;
}

template<concepts::Scalar T>
template<concepts::Scalar U>
constexpr inline Point<T>::operator Point<U>() const noexcept {
    return Point<U>(static_cast<U>(x), static_cast<U>(y));    
}

template<concepts::Scalar T>
constexpr inline Point<T> operator+(const Point<T>& first, const Point<T>& second) noexcept {
    Point<T> temp = first;
    return first += second;
}

template<concepts::Scalar T>
constexpr inline Point<T> operator-(const Point<T>& first, const Point<T>& second) noexcept {
    Point<T> temp = first;
    return first -= second;
}

template<concepts::Scalar T>
constexpr inline Point<T> operator*(T number, const Point<T>& point) noexcept {
    Point<T> temp = point;
    return temp *= number;
}

template<concepts::Scalar T>
constexpr inline Point<T> operator/(const Point<T>& point, T number) noexcept {
    Point<T> temp = point;
    return temp / number;
}

template<concepts::Scalar T>
std::ostream& operator<<(std::ostream& out, const Point<T>& point) {
    out << '(' << point.x << "; " << point.y << ')';
    return out;
}

template<concepts::Scalar T>
std::istream& operator>>(std::istream& in, Point<T>& point) {
    in >> point.x >> point.y;
    return in;
}

}