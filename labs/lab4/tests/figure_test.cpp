#include <cmath>
#include <memory>
#include <sstream>

#include <gtest/gtest.h>

#include "array.hpp"
#include "pentagon.hpp"
#include "rhombus.hpp"
#include "trapezoid.hpp"

TEST(RhombusTest, DefaultConstructor) {
    geometry::Rhombus<double> rhombus;
    EXPECT_NO_THROW(rhombus.Center());
}

TEST(RhombusTest, ParameterizedConstructor) {
    geometry::Point<double> start(0, 0);
    geometry::Rhombus<double> rhombus(start, 0.0, 5.0, 60);
    EXPECT_NEAR(static_cast<double>(rhombus), 5.0 * 5.0 * sin(M_PI / 3), 1e-6);
}

TEST(RhombusTest, AreaCalculation) {
    geometry::Point<double> start(0, 0);
    double side = 4.0;
    double angle = 60;
    geometry::Rhombus<double> rhombus(start, 0.0, side, angle);
    double expected_area = side * side * sin(angle * M_PI / 180.0);
    EXPECT_NEAR(static_cast<double>(rhombus), expected_area, 1e-6);
}

TEST(RhombusTest, EqualityOperator) {
    geometry::Point<double> start1(0, 0);
    geometry::Point<double> start2(1, 1);
    geometry::Rhombus<double> rhombus1(start1, 0.0, 5.0, M_PI / 4);
    geometry::Rhombus<double> rhombus2(start1, 0.0, 5.0, M_PI / 4);
    geometry::Rhombus<double> rhombus3(start2, 0.0, 5.0, M_PI / 4);

    EXPECT_TRUE(rhombus1 == rhombus2);
    EXPECT_TRUE(rhombus1 == rhombus3);
}

TEST(RhombusTest, StreamInputOperator) {
    geometry::Rhombus<double> rhombus;
    std::stringstream ss("0 0 0 5 1.047");

    EXPECT_NO_THROW(ss >> rhombus);
    EXPECT_NO_THROW(static_cast<double>(rhombus));
}

TEST(TrapezoidTest, DefaultConstructor) {
    geometry::Trapezoid<double> trapezoid;
    EXPECT_NO_THROW(trapezoid.Center());
}

TEST(TrapezoidTest, ParameterizedConstructor) {
    geometry::Point<double> start(0, 0);
    geometry::Trapezoid<double> trapezoid(start, 0.0, 8.0, 4.0, 3.0);
    EXPECT_GT(static_cast<double>(trapezoid), 0.0);
}

TEST(TrapezoidTest, AreaCalculation) {
    geometry::Point<double> start(0, 0);
    double base1 = 8.0, base2 = 4.0, side = 3.0;
    geometry::Trapezoid<double> trapezoid(start, 0.0, base1, base2, side);

    double height =
        sqrt(side * side - ((base1 - base2) / 2) * ((base1 - base2) / 2));
    double expected_area = (base1 + base2) * height / 2.0;

    EXPECT_NEAR(static_cast<double>(trapezoid), expected_area, 1e-6);
}

TEST(TrapezoidTest, EqualityOperator) {
    geometry::Point<double> start(0, 0);
    geometry::Trapezoid<double> trap1(start, 0.0, 8.0, 4.0, 3.0);
    geometry::Trapezoid<double> trap2(start, 0.0, 8.0, 4.0, 3.0);
    geometry::Trapezoid<double> trap3(start, 0.0, 6.0, 4.0, 3.0);

    EXPECT_TRUE(trap1 == trap2);
    EXPECT_FALSE(trap1 == trap3);
}

TEST(TrapezoidTest, CenterCalculation) {
    geometry::Point<double> start(0, 0);
    geometry::Trapezoid<double> trapezoid(start, 0.0, 8.0, 4.0, 3.0);
    geometry::Point<double> center = trapezoid.Center();

    EXPECT_NO_THROW(center.x);
    EXPECT_NO_THROW(center.y);
}

TEST(PentagonTest, DefaultConstructor) {
    geometry::Pentagon<double> pentagon;
    EXPECT_NO_THROW(pentagon.Center());
}

TEST(PentagonTest, ParameterizedConstructor) {
    geometry::Point<double> start(0, 0);
    geometry::Pentagon<double> pentagon(start, 0.0, 5.0);
    EXPECT_GT(static_cast<double>(pentagon), 0.0);
}

TEST(PentagonTest, AreaCalculation) {
    geometry::Point<double> start(0, 0);
    double side = 5.0;
    geometry::Pentagon<double> pentagon(start, 0.0, side);

    double expected_area =
        0.25 * sqrt(5.0 * (5.0 + 2.0 * sqrt(5.0))) * side * side;

    EXPECT_NEAR(static_cast<double>(pentagon), expected_area, 1e-6);
}

TEST(PentagonTest, EqualityOperator) {
    geometry::Point<double> start(0, 0);
    geometry::Pentagon<double> pent1(start, 0.0, 5.0);
    geometry::Pentagon<double> pent2(start, 0.0, 5.0);
    geometry::Pentagon<double> pent3(start, 45, 5.0);

    EXPECT_TRUE(pent1 == pent2);
    EXPECT_TRUE(pent1 == pent3);
}

TEST(PentagonTest, StreamOperators) {
    geometry::Pentagon<double> pentagon;
    std::stringstream ss("0 0 0 5");

    EXPECT_NO_THROW(ss >> pentagon);

    std::stringstream output;
    EXPECT_NO_THROW(output << pentagon);
    EXPECT_FALSE(output.str().empty());
}

TEST(ArrayWithFiguresTest, StoreDifferentFigures) {
    array::Array<std::shared_ptr<geometry::Figure<double>>> figures;

    figures.PushBack(std::make_shared<geometry::Rhombus<double>>(
        geometry::Point<double>(0, 0), 0.0, 4.0, M_PI / 3));
    figures.PushBack(std::make_shared<geometry::Trapezoid<double>>(
        geometry::Point<double>(1, 1), 0.0, 6.0, 4.0, 3.0));
    figures.PushBack(std::make_shared<geometry::Pentagon<double>>(
        geometry::Point<double>(2, 2), 0.0, 5.0));

    EXPECT_EQ(figures.Size(), 3);
}

TEST(ArrayWithFiguresTest, PolymorphicBehavior) {
    array::Array<std::shared_ptr<geometry::Figure<double>>> figures;

    figures.PushBack(std::make_shared<geometry::Rhombus<double>>(
        geometry::Point<double>(0, 0), 0.0, 4.0, M_PI / 3));
    figures.PushBack(std::make_shared<geometry::Pentagon<double>>(
        geometry::Point<double>(0, 0), 0.0, 3.0));

    double total_area = 0.0;
    for (size_t i = 0; i < figures.Size(); ++i) {
        total_area += static_cast<double>(*figures[i]);
    }

    EXPECT_GT(total_area, 0.0);
}

TEST(ArrayWithFiguresTest, CenterCalculations) {
    array::Array<std::shared_ptr<geometry::Figure<double>>> figures;

    figures.PushBack(std::make_shared<geometry::Rhombus<double>>(
        geometry::Point<double>(0, 0), 0.0, 4.0, M_PI / 3));
    figures.PushBack(std::make_shared<geometry::Pentagon<double>>(
        geometry::Point<double>(1, 1), 0.0, 2.0));

    for (size_t i = 0; i < figures.Size(); ++i) {
        geometry::Point<double> center = figures[i]->Center();
        EXPECT_NO_THROW(center.x);
        EXPECT_NO_THROW(center.y);
    }
}

TEST(ArrayWithFiguresTest, StreamOperationsWithArray) {
    array::Array<std::shared_ptr<geometry::Figure<double>>> figures;

    auto rhombus = std::make_shared<geometry::Rhombus<double>>();
    std::stringstream rhombus_ss("0 0 0 4 1.047");
    rhombus_ss >> *rhombus;
    figures.PushBack(rhombus);

    auto pentagon = std::make_shared<geometry::Pentagon<double>>();
    std::stringstream pentagon_ss("1 1 0 3");
    pentagon_ss >> *pentagon;
    figures.PushBack(pentagon);

    std::stringstream output;
    for (size_t i = 0; i < figures.Size(); ++i) {
        EXPECT_NO_THROW(output << *figures[i]);
    }
    EXPECT_FALSE(output.str().empty());
}

TEST(ArrayWithFiguresTest, EmplaceBackFigures) {
    array::Array<std::shared_ptr<geometry::Figure<double>>> figures;

    figures.EmplaceBack(std::make_shared<geometry::Rhombus<double>>());
    figures.EmplaceBack(std::make_shared<geometry::Trapezoid<double>>());

    EXPECT_EQ(figures.Size(), 2);
}

TEST(ArrayWithFiguresTest, FrontAndBackOperations) {
    array::Array<std::shared_ptr<geometry::Figure<double>>> figures;

    auto rhombus = std::make_shared<geometry::Rhombus<double>>(
        geometry::Point<double>(0, 0), 0.0, 4.0, M_PI / 3);
    auto pentagon = std::make_shared<geometry::Pentagon<double>>(
        geometry::Point<double>(0, 0), 0.0, 3.0);

    figures.PushBack(rhombus);
    figures.PushBack(pentagon);

    EXPECT_EQ(figures.Front(), rhombus);
    EXPECT_EQ(figures.Back(), pentagon);
}

TEST(ArrayWithFiguresTest, AtMethodWithFigures) {
    array::Array<std::shared_ptr<geometry::Figure<double>>> figures;

    figures.PushBack(std::make_shared<geometry::Rhombus<double>>(
        geometry::Point<double>(0, 0), 0.0, 4.0, M_PI / 3));

    EXPECT_NO_THROW(figures.At(0));
    EXPECT_THROW(figures.At(1), exceptions::OutOfRangeArrayException);
}

TEST(ArrayWithFiguresTest, PopOperations) {
    array::Array<std::shared_ptr<geometry::Figure<double>>> figures;

    figures.PushBack(std::make_shared<geometry::Rhombus<double>>());
    figures.PushBack(std::make_shared<geometry::Trapezoid<double>>());
    figures.PushBack(std::make_shared<geometry::Pentagon<double>>());

    figures.PopBack();
    EXPECT_EQ(figures.Size(), 2);
    std::cout << "Popback" << std::endl;

    figures.Pop(0);
    std::cout << "Pop" << std::endl;
    EXPECT_EQ(figures.Size(), 1);
    std::cout << "Test passed" << std::endl;
}

TEST(ArrayWithFiguresTest, ClearAndEmpty) {
    array::Array<std::shared_ptr<geometry::Figure<double>>> figures;

    figures.PushBack(std::make_shared<geometry::Rhombus<double>>());
    figures.PushBack(std::make_shared<geometry::Pentagon<double>>());

    EXPECT_FALSE(figures.Empty());
    figures.Clear();
    EXPECT_TRUE(figures.Empty());
}

TEST(ArrayWithFiguresTest, MoveSemantics) {
    array::Array<std::shared_ptr<geometry::Figure<double>>> figures1;
    figures1.PushBack(std::make_shared<geometry::Rhombus<double>>());

    array::Array<std::shared_ptr<geometry::Figure<double>>> figures2 =
        std::move(figures1);
    EXPECT_EQ(figures2.Size(), 1);
    EXPECT_EQ(figures1.Size(), 0);
}

TEST(MixedTypesTest, DifferentNumericTypes) {
    geometry::Rhombus<double> rhombus_d;
    geometry::Rhombus<float> rhombus_f;
    geometry::Rhombus<int> rhombus_i;

    EXPECT_NO_THROW(rhombus_d.Center());
    EXPECT_NO_THROW(rhombus_f.Center());
    EXPECT_NO_THROW(rhombus_i.Center());
}

TEST(StreamTest, MultipleFiguresStreamOperations) {
    geometry::Rhombus<double> rhombus;
    geometry::Pentagon<double> pentagon;

    std::stringstream ss;
    ss << "0 0 0 5 45 ";
    ss << "1 1 0 4";

    EXPECT_NO_THROW(ss >> rhombus >> pentagon);
    EXPECT_GT(static_cast<double>(rhombus), 0.0);
    EXPECT_GT(static_cast<double>(pentagon), 0.0);
}
