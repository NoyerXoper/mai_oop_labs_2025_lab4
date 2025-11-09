#pragma once

#include "polygon.hpp"

namespace geometry {
namespace {
constexpr std::size_t PENTAGON_VERTICES = 5;
}

template <concepts::Scalar T>
class Pentagon : public Polygon<T, PENTAGON_VERTICES> {
public:
    Pentagon() noexcept;
    Pentagon(const Point<T>& start, double turn, double side);

    Pentagon(const Pentagon& other);
    Pentagon(Pentagon&& other) noexcept;

    Pentagon& operator=(const Pentagon& other);
    Pentagon& operator=(Pentagon&& other) noexcept;

    virtual ~Pentagon() override = default;

    virtual operator double() const noexcept final;
    virtual void Read(std::istream& in) final;

    template <concepts::Scalar U>
    friend inline bool operator==(const Pentagon<U>& first,
                                  const Pentagon<U>& second) noexcept;

protected:
    using Polygon<T, PENTAGON_VERTICES>::points_;
};
}  // namespace geometry

#include "pentagon.ipp"
