#pragma once

#include "concepts.hpp"

namespace geometry {
template<concepts::Scalar T>
struct Point {
    Point() noexcept;
    Point(T x, T y) noexcept;

    Point& operator+=(const Point& other) noexcept;
    Point& operator-=(const Point& other) noexcept;
    Point& operator*=(T number) noexcept;
    Point& operator/=(T number) noexcept;

    T x;
    T y;
};

template<concepts::Scalar T>
Point<T> operator+(const Point<T>& first, const Point<T>& second) noexcept;

template<concepts::Scalar T>
Point<T> operator-(const Point<T>& first, const Point<T>& second) noexcept;

template<concepts::Scalar T>
Point<T> operator*(T number, const Point<T>& point) noexcept;

template<concepts::Scalar T>
Point<T> operator/(const Point<T>& point, T number) noexcept;
}

#include "point.ipp"
