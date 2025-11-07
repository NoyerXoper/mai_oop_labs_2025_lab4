#pragma once

#include <array>
#include <memory>
#include <type_traits>

#include "figure.hpp"
#include "point.hpp"
#include "concepts"

namespace geometry {
namespace {
constexpr std::size_t MAX_STACK_POLYGON_POINTS = 50;
}
template <concepts::Scalar T, std::size_t N>
class Polygon : public Figure<T> {
    constexpr static bool IS_BIG = N > MAX_STACK_POLYGON_POINTS;

public:
    Polygon() noexcept requires(!IS_BIG);
    Polygon() requires IS_BIG;

    Polygon(const Polygon& other) requires IS_BIG;
    Polygon(Polygon&& other) noexcept requires IS_BIG;

    Polygon& operator=(const Polygon& other) requires IS_BIG;
    Polygon& operator=(Polygon&& other) noexcept requires IS_BIG;

    Polygon(const Polygon& other) requires(!IS_BIG) = default;
    Polygon(Polygon&& other) noexcept requires(!IS_BIG) = default;

    Polygon& operator=(const Polygon& other) requires(!IS_BIG) = default;
    Polygon& operator=(Polygon&& other) noexcept requires(!IS_BIG) = default;

    virtual ~Polygon() noexcept override = default;

    virtual Point<T> Center() const noexcept final;
    // it's imposible to overload or specialize swap for template classes
    template <concepts::Scalar U, std::size_t K>
    friend void swap(Polygon<U, K>& first, Polygon<U, K>& second) noexcept;

protected:
    inline void Swap(Polygon& other) noexcept;
    virtual void Print(std::ostream& out) const final;
    // Using std::array for small polygons, for the rest will store in the heap.
    using StorageType = std::conditional_t<IS_BIG, std::unique_ptr<Point<T>[]>,
                                           std::array<Point<T>, N>>;
    StorageType points_;
};
}  // namespace geometry

#include "polygon.ipp"
