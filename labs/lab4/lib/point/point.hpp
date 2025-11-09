#pragma once

#include <cmath>
#include <istream>
#include <ostream>

#include "concepts.hpp"

namespace geometry {
template <concepts::Scalar T>
struct Point {
    Point() noexcept;
    Point(T x, T y) noexcept;

    template <concepts::Scalar U>
    constexpr inline Point& operator+=(const Point<U>& other) noexcept;
    template <concepts::Scalar U>
    constexpr inline Point& operator-=(const Point<U>& other) noexcept;
    template <concepts::Scalar U>
    constexpr inline Point& operator*=(U number) noexcept;
    template <concepts::Scalar U>
    constexpr inline Point& operator/=(U number) noexcept;

    template <concepts::Scalar U>
    constexpr inline operator Point<U>() const noexcept;

    T x;
    T y;
};

template <concepts::Scalar T>
constexpr inline Point<T> operator+(const Point<T>& first,
                                    const Point<T>& second) noexcept;

template <concepts::Scalar T>
constexpr inline Point<T> operator-(const Point<T>& first,
                                    const Point<T>& second) noexcept;

template <concepts::Scalar T, concepts::Scalar U>
constexpr inline Point<T> operator*(U number, const Point<T>& point) noexcept;

template <concepts::Scalar T, concepts::Scalar U>
constexpr inline Point<T> operator/(const Point<T>& point, U number) noexcept;

template <concepts::Scalar T>
constexpr inline bool operator==(const Point<T>& first,
                                 const Point<T>& second) noexcept;

template <concepts::Scalar T>
constexpr inline bool operator!=(const Point<T>& first,
                                 const Point<T>& second) noexcept;

template <concepts::Scalar T>
inline Point<T> rotate(const Point<T>& point, double angle) noexcept;

template <concepts::Scalar T>
double Abs(const Point<T>& point) noexcept {
    return std::sqrt(point.x * point.x + point.y * point.y);
}

template <concepts::Scalar T>
std::ostream& operator<<(std::ostream& out, const Point<T>& point);

template <concepts::Scalar T>
std::istream& operator>>(std::istream& in, Point<T>& point);
}  // namespace geometry

#include "point.ipp"
