#pragma once

#include "polygon.hpp"

namespace geometry {
namespace {
constexpr std::size_t TRAPEZOID_VERTICES = 4;
}

template <concepts::Scalar T>
class Trapezoid : public Polygon<T, TRAPEZOID_VERTICES> {
public:
    Trapezoid() noexcept = default;
    Trapezoid(const Point<T>& start, double turn, double base1, double base2,
              double side_length);

    Trapezoid(const Trapezoid& other);
    Trapezoid(Trapezoid&& other) noexcept;

    Trapezoid& operator=(const Trapezoid& other);
    Trapezoid& operator=(Trapezoid&& other) noexcept;

    virtual ~Trapezoid() override = default;

    virtual operator double() const noexcept final;
    virtual void Read(std::istream& in) final;

    template <concepts::Scalar U>
    friend bool operator==(const Trapezoid<U>& first,
                           const Trapezoid<U>& second) noexcept;

protected:
    using Polygon<T, TRAPEZOID_VERTICES>::points_;
};
}  // namespace geometry

#include "trapezoid.ipp"
