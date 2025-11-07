#include <iostream>
#include <memory>

#include "array.hpp"
#include "pentagon.hpp"
#include "rhombus.hpp"
#include "trapezoid.hpp"

int main() {
    array::Array<geometry::Pentagon<double>> pentaArray(2);
    std::cout << "Enter 2 pentagons: x_0, y_0, turn_degrees, side\n";
    for (std::size_t i = 0; i < pentaArray.Capacity(); ++i) {
        std::cin >> pentaArray[i];
    }

    std::cout << "Your pentagons:\n";
    for (std::size_t i = 0; i < pentaArray.Capacity(); ++i) {
        std::cout << pentaArray[i] << '\n';
    }

    std::cout << "Centers:\n";
    for (std::size_t i = 0; i < pentaArray.Capacity(); ++i) {
        std::cout << pentaArray[i].Center() << '\n';
    }

    std::cout << "Areas:\n";
    double total = 0;
    double temp_area = 0;
    for (std::size_t i = 0; i < pentaArray.Capacity(); ++i) {
        temp_area = static_cast<double>(pentaArray[i]);
        total += temp_area;
        std::cout << temp_area << '\n';
    }

    std::cout << "Total: " << total;
    std::cout << "\nEnter Rhombus: x0, y0, turn, side, angle; and Trapezoid: "
                 "x0, y0, turn, base1, base2, side_length:\n";
    array::Array<geometry::Figure<double>*> pmrarray{
        new geometry::Rhombus<double>(), new geometry::Trapezoid<double>()};
    for (std::size_t i = 0; i < pmrarray.Size(); ++i) {
        std::cin >> *pmrarray[i];
    }

    std::cout << "Your figures:\n";
    for (std::size_t i = 0; i < pmrarray.Capacity(); ++i) {
        std::cout << *pmrarray[i] << '\n';
    }

    std::cout << "Centers:\n";
    for (std::size_t i = 0; i < pmrarray.Capacity(); ++i) {
        std::cout << pmrarray[i]->Center() << '\n';
    }

    std::cout << "Areas:\n";
    total = 0;
    temp_area = 0;
    for (std::size_t i = 0; i < pmrarray.Capacity(); ++i) {
        temp_area = static_cast<double>(*pmrarray[i]);
        total += temp_area;
        std::cout << temp_area << '\n';
    }

    std::cout << "Total: " << total;

    for (std::size_t i = 0; i < pmrarray.Size(); ++i) {
        delete pmrarray[i];
    }
}