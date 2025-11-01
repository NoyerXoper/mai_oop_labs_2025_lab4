#include "trapezoid.hpp"

#include "polygon_exception.hpp"
#include "compare.hpp"

namespace geometry {
template<concepts::Scalar T>
Trapezoid<T>::Trapezoid() noexcept = default;

template<concepts::Scalar T>
Trapezoid<T>::Trapezoid(const Point<T>& start, double turn, double base1, double base2, double side_length) noexcept {
    if (base1 <= 0 || base2 <= 0 || side_length <= 0) {
        throw exceptions::FigureException("Sides must be greater than 0");
    }
    if (compare::AreDoublesEqual(base1, base2)) {
        throw exceptions::FigureException("Bases can't be equal");
    }
    if (side_length <= std::abs(base1 - base2) / 2) {
        throw exceptions::FigureException("This trapezoid can't exist because of the length of the side length");
    }

    double mathAngle = turn * std::numbers::pi_v<double> / 180;
    double lowerAngle = std::acos(((base1 - base2) / 2) / side);
    double upperAngle = std::numbers::pi - lowerAngle;

    Point firstBase = Point(base1 * std::cos(mathAngle), base1 * std::sin(mathAngle));
    Point secondBase = Point(base2 * std::cos(mathAngle), base2 * std::sin(mathAngle));
    Point sideSide = Point(side_length * std::cos(mathAngle + upperAngle), side_length * std::sin(mathAngle + upperAngle));

    Point<double> point1 = static_cast<Point<double>>(start) + firstBase;
    Point<double> points2 = points_[1] + sideSide;
    Point<double> points3 = points_[2] - secondBase;

    points_[0] = start;
    points_[1] = static_cast<Point<T>>(point1);
    points_[2] = static_cast<Point<T>>(point2);
    points_[3] = static_cast<Point<T>>(point3);
}

template<concepts::Scalar T>
Trapezoid<T>::operator double() const noexcept {
    double base1 = Abs(points_[1] - points_[0]);
    double base2 = Abs(points_[3] - points_[2]);
    double side = Abs(points_[2] - points_[1]);
    double height = std::sqrt(side * side - std::pow((base1 - base2) / 2, 2));
    return (base1 + base2) / 2 * height;    
}

template<concepts::Scalar T>
void Trapezoid<T>::Read(std::istream& in) {
    Point<T> start;
    double turn;
    double base1;
    double base2;
    double side_length;

    in >> start >> base1 >> base2 >> side_length;

    *this = Trapezoid<T>(start, turn, base1, base2, side_length);
}

template<concepts::Scalar T>
bool operator==(const Trapezoid<T>& first, const Trapezoid<T>& second) noexcept {
    double base1_1 = Abs(first.points_[0] - first.points_[1]);
    double base2_1 = Abs(first.points_[3] - first.points_[2]);
    double side_1 = Abs(first.points_[2] - first.points_[1]);

    double base1_2 = Abs(second.points_[0] - second.points_[1]);
    double base2_2 = Abs(second.points_[3] - second.points_[2]);
    double side_2 = Abs(second.points_[2] - second.points_[1]);

    if (compare::AreNumbersEqual(base1_1, base1_2)) {
        return compare::AreNumbersEqual(base2_1, base2_2) && compare::AreNumbersEqual(side_1, side_2); 
    }
    return compare::AreNumbersEqual(base1_1, base2_2) && compare::AreNumbersEqual(base2_1, base2_1) && compare::AreNumbersEqual(side_1, side_2);
}
}
