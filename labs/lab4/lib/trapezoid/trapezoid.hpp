#pragma once

#include "polygon.hpp"

namespace geometry {
namespace {
constexpr std::size_t VERTICES = 4;
}

template<concepts::Scalar T>
class Trapezoid: public Polygon<T, VERTICES> {
public:
    Trapezoid() noexcept;
    Trapezoid(const Point<T>& start, double turn, double base1, double base2, double side_length) noexcept;

    virtual operator double() const noexcept final;
    virtual void Read(std::istream& in) final;

    friend operator==(const Trapezoid& first, const Trapezoid& second) noexcept;
};
}

#include "trapezoid.ipp"