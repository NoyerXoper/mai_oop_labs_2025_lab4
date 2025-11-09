#include "pentagon.hpp"

#include "compare.hpp"
#include "polygon_exception.hpp"

namespace geometry {
template <concepts::Scalar T>
Pentagon<T>::Pentagon() noexcept = default;

template <concepts::Scalar T>
Pentagon<T>::operator double() const noexcept {
    static const double TG_72 = std::tan(3 * std::numbers::pi_v<double> / 10);

    double sideLength = Abs(points_[1] - points_[0]);

    return 5 * sideLength * sideLength / 4 * TG_72;
}

template <concepts::Scalar T>
Pentagon<T>::Pentagon(const Point<T>& start, double turn, double side) {
    if (std::isnan(turn) || std::isinf(turn)) {
        throw exceptions::PolygonException("Turn must be a finite number");
    }

    if (std::isnan(side) || std::isinf(side)) {
        throw exceptions::PolygonException("Side must be a finite number");
    }

    if (side <= 0) {
        throw exceptions::PolygonException("Side must be greater than 0");
    }

    static constexpr double angle_step =
        72.0 * std::numbers::pi_v<double> / 180.0;

    points_[0] = start;
    Point<double> current_point = static_cast<Point<double>>(start);
    double current_angle = turn;

    for (int i = 1; i < 5; ++i) {
        double angle_rad = current_angle;
        Point<double> sideVector(side * std::cos(angle_rad),
                                 side * std::sin(angle_rad));
        Point<double> next_point = current_point + sideVector;

        points_[i] = static_cast<Point<T>>(next_point);
        current_point = next_point;
        current_angle += angle_step;
    }
}

template <concepts::Scalar T>
Pentagon<T>::Pentagon(const Pentagon<T>& other)
    : Polygon<T, PENTAGON_VERTICES>(other) {}

template <concepts::Scalar T>
Pentagon<T>::Pentagon(Pentagon<T>&& other) noexcept
    : Polygon<T, PENTAGON_VERTICES>(std::move(other)) {}

template <concepts::Scalar T>
Pentagon<T>& Pentagon<T>::operator=(const Pentagon<T>& other) {
    if (this == std::addressof(other)) {
        return *this;
    }
    Polygon<T, PENTAGON_VERTICES>::operator=(other);
    return *this;
}

template <concepts::Scalar T>
Pentagon<T>& Pentagon<T>::operator=(Pentagon<T>&& other) noexcept {
    if (this == std::addressof(other)) {
        return *this;
    }
    Polygon<T, PENTAGON_VERTICES>::operator=(std::move(other));
    return *this;
}

template <concepts::Scalar T>
void Pentagon<T>::Read(std::istream& in) {
    Point<T> start;
    double turn;
    double side;
    in >> start >> turn >> side;
    *this = Pentagon<T>(start, turn, side);
}

template <concepts::Scalar T>
inline bool operator==(const Pentagon<T>& first,
                       const Pentagon<T>& second) noexcept {
    return compare::AreNumbersEqual(Abs(first.points_[1] - first.points_[0]),
                                    Abs(second.points_[1] - second.points_[0]));
}

template <concepts::Scalar T>
inline bool operator!=(const Pentagon<T>& first,
                       const Pentagon<T>& second) noexcept {
    return !(first == second);
}
}  // namespace geometry
