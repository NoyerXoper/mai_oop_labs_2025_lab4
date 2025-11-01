#pragma once

#include <istream>
#include <ostream>

#include "concepts.hpp"

namespace geometry {

template<concepts::Scalar T>
class Figure {
public:
    virtual Point<T> Center() const noexcept = 0;
    virtual operator double() const noexcept = 0;

    friend std::ostream& operator<<(std::ostream& out, const Figure& figure);
    friend std::istream& operator>>(std::istream& in, Figure& figure);
protected:
    virtual void Read(std::istream& in) = 0;
    virtual void Print(std::ostream& out) const = 0;
};

template<concepts::Scalar T>
std::ostream& operator<<(std::ostream& out, const Figure<T>& figure);

template<concepts::Scalar T>
std::istream& operator>>(std::istream& in, Figure<T>& figure);
}

#include "figure.ipp"