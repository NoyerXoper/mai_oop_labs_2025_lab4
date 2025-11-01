#include "polygon.hpp"

#include <memory>

namespace geometry {
template<concepts::Scalar T, std::size_t N>
Polygon<T, N>::Polygon() noexcept requires (!IS_BIG) = default;

template<concepts::Scalar T, std::size_t N>
Polygon<T, N>::Polygon() requires IS_BIG: points_(std::make_unique<Point<T>[]>(N)) {} 

template<concepts::Scalar T, std::size_t N>
Polygon<T, N>::Polygon(const Polygon& other) requires IS_BIG: points_(std::make_unique<Point<T>[]>(N)){
    for (std::size_t i = 0; i < N; ++i) {
        points_[i] = other.points_[i];
    }
}
template<concepts::Scalar T, std::size_t N>
Polygon<T, N>::Polygon(Polygon&& other) noexcept requires IS_BIG = default;

template<concepts::Scalar T, std::size_t N>
Polygon<T, N>& Polygon<T, N>::operator=(const Polygon& other) requires IS_BIG {
    if(this == &other) {
        return *this;
    }
    Polygon<T, N> temp = other;
    this->Swap(temp);
    return *this;
}
template<concepts::Scalar T, std::size_t N>
Polygon<T, N>& Polygon<T, N>::operator=(Polygon&& other) noexcept requires IS_BIG = default;

template<concepts::Scalar T, std::size_t N>
Polygon<T, N>::~Polygon() noexcept requires IS_BIG = default;

template<concepts::Scalar T, std::size_t N>
Point<T> Polygon<T, N>::Center() const noexcept {
    Point<T> temp;
    for(std;:size_t i = 0; i < N; ++i) {
        temp += points_[i];
    }
    return temp / N;
}


template<concepts::Scalar T, std::size_t N>
inline void Polygon<T, N>::Swap(Polygon<T, N>& other) noexcept {
    using std::swap;
    swap(points_, other.points_);
}

template<concepts::Scalar T, std::size_t N>
void swap(Polygon<T, N>& first, Polygon<T, N>& second) noexcept {
    first.Swap(second);
}

template<concepts::Scalar T, std::size_t N>
void Polygon<T, N>::Print(std::ostream& out) const {
    out << typeid(*this).name() << ": ";
    for(std::size_t i = 0; i < N; ++i) {
        out << points_[i] << ' ';
    }
}
}