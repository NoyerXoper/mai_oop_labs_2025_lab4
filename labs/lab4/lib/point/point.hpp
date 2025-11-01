#pragma once

#include <ostream>
#include <istream>
#include <cmath>

#include "concepts.hpp"

namespace geometry {
template<concepts::Scalar T>
struct Point {
    Point() noexcept;
    Point(T x, T y) noexcept;

    constexpr inline Point& operator+=(const Point& other) noexcept;
    constexpr inline Point& operator-=(const Point& other) noexcept;
    constexpr inline Point& operator*=(T number) noexcept;
    constexpr inline Point& operator/=(T number) noexcept;

    template<concepts::Scalar U>
    constexpr inline operator Point<U>() const noexcept;

    T x;
    T y;
};

template<concepts::Scalar T>
constexpr inline Point<T> operator+(const Point<T>& first, const Point<T>& second) noexcept;

template<concepts::Scalar T>
constexpr inline Point<T> operator-(const Point<T>& first, const Point<T>& second) noexcept;

template<concepts::Scalar T>
constexpr inline Point<T> operator*(T number, const Point<T>& point) noexcept;

template<concepts::Scalar T>
constexpr inline Point<T> operator/(const Point<T>& point, T number) noexcept;

template<concepts::Scalar T>
double Abs(const Point<T>& point) noexcept {
    return std::sqrt(point.x * point.x + point.y * point.y);
}

template<concepts::Scalar T>
std::ostream& operator<<(std::ostream& out, const Point<T>& point);

template<concepts::Scalar T>
std::istream& operator>>(std::istream& in, Point<T>& point);
}

#include "point.ipp"
