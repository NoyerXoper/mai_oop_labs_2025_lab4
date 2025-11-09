#include "rhombus.hpp"

#include "compare.hpp"
#include "polygon_exception.hpp"

namespace geometry {

template <concepts::Scalar T>
Rhombus<T>::Rhombus() noexcept
    : Polygon<T, RHOMBUS_VERTICES>() {}

template <concepts::Scalar T>
Rhombus<T>::Rhombus(const Point<T>& start, double turn, double side,
                    double angle) {
    if (std::isnan(turn) || std::isinf(turn)) {
        throw exceptions::PolygonException("Turn must be a finite number");
    }

    if (std::isnan(side) || std::isinf(side)) {
        throw exceptions::PolygonException("Side must be a finite number");
    }

    if (std::isnan(angle) || std::isinf(angle)) {
        throw exceptions::PolygonException("Angle must be a finite number");
    }

    if (side <= 0) {
        throw exceptions::PolygonException("Sides must be greater than 0");
    }
    double mathAngle = angle * std::numbers::pi_v<double> / 180;
    double mathTurn = turn * std::numbers::pi_v<double> / 180;
    Point<double> firstSide =
        Point(side * std::cos(mathTurn), side * std::sin(mathTurn));
    Point<double> secondSide = Point(side * std::cos(mathTurn + mathAngle),
                                     side * std::sin(mathTurn + mathAngle));

    Point<double> point1 = static_cast<Point<double>>(start) + firstSide;
    Point<double> point2 = point1 + secondSide;
    Point<double> point3 = point2 - firstSide;

    this->points_[0] = start;
    this->points_[1] = static_cast<Point<T>>(point1);
    this->points_[2] = static_cast<Point<T>>(point2);
    this->points_[3] = static_cast<Point<T>>(point3);
}

template <concepts::Scalar T>
Rhombus<T>::Rhombus(const Rhombus<T>& other)
    : Polygon<T, RHOMBUS_VERTICES>(other) {}

template <concepts::Scalar T>
Rhombus<T>::Rhombus(Rhombus<T>&& other) noexcept
    : Polygon<T, RHOMBUS_VERTICES>(std::move(other)) {}

template <concepts::Scalar T>
Rhombus<T>& Rhombus<T>::operator=(const Rhombus<T>& other) {
    if (this == std::addressof(other)) {
        return *this;
    }
    Polygon<T, RHOMBUS_VERTICES>::operator=(other);
    return *this;
}

template <concepts::Scalar T>
Rhombus<T>& Rhombus<T>::operator=(Rhombus<T>&& other) noexcept {
    if (this == std::addressof(other)) {
        return *this;
    }
    Polygon<T, RHOMBUS_VERTICES>::operator=(std::move(other));
    return *this;
}

template <concepts::Scalar T>
Rhombus<T>::operator double() const noexcept {
    Point side1 = points_[1] - points_[0];
    Point side2 = points_[2] - points_[1];
    return std::abs(side1.x * side2.y - side2.x * side1.y);
}

template <concepts::Scalar T>
inline bool operator==(const Rhombus<T>& first,
                       const Rhombus<T>& second) noexcept {
    double side1_1 = Abs(first.points_[0] - first.points_[1]);

    double side2_1 = Abs(second.points_[0] - second.points_[1]);

    return compare::AreNumbersEqual(side1_1, side2_1) &&
           compare::AreNumbersEqual(static_cast<double>(first),
                                    static_cast<double>(second));
}

template <concepts::Scalar T>
inline bool operator!=(const Rhombus<T>& first,
                       const Rhombus<T>& second) noexcept {
    return !(first == second);
}

template <concepts::Scalar T>
void Rhombus<T>::Read(std::istream& in) {
    Point<T> start;
    double turn;
    double side;
    double angle;
    in >> start;
    in >> turn;
    in >> side;
    in >> angle;

    *this = Rhombus<T>(start, turn, side, angle);
}

}  // namespace geometry