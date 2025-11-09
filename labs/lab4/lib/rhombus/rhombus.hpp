#pragma once

#include "polygon.hpp"

namespace geometry {
namespace {
constexpr std::size_t RHOMBUS_VERTICES = 4;
}

template <concepts::Scalar T>
class Rhombus : public Polygon<T, RHOMBUS_VERTICES> {
public:
    Rhombus() noexcept;
    Rhombus(const Point<T>& start, double turn, double side, double angle);

    Rhombus(const Rhombus& other);
    Rhombus(Rhombus&& other) noexcept;

    Rhombus& operator=(const Rhombus& other);
    Rhombus& operator=(Rhombus&& other) noexcept;

    virtual ~Rhombus() override = default;

    virtual operator double() const noexcept final;
    virtual void Read(std::istream& in) final;

    template <concepts::Scalar U>
    friend inline bool operator==(const Rhombus<U>& first,
                                  const Rhombus<U>& second) noexcept;

protected:
    using Polygon<T, RHOMBUS_VERTICES>::points_;
};
}  // namespace geometry

#include "rhombus.ipp"
