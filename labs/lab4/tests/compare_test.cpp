#include <cmath>
#include <limits>

#include <gtest/gtest.h>

#include "compare.hpp"

template <typename T>
class FloatCompareTest : public ::testing::Test {
protected:
    static constexpr T eps = std::numeric_limits<T>::epsilon();
    static constexpr T koef = 64;
    static constexpr T tolerance_base = koef * eps;
};

using FloatTypes = ::testing::Types<float, double, long double>;
TYPED_TEST_SUITE(FloatCompareTest, FloatTypes);

TEST(IntegralCompareTest, ExactEquality) {
    EXPECT_TRUE(compare::AreNumbersEqual(42, 42));
    EXPECT_TRUE(compare::AreNumbersEqual(-10, -10));
    EXPECT_TRUE(compare::AreNumbersEqual(0, 0));
    EXPECT_TRUE(compare::AreNumbersEqual(1234567890, 1234567890));
}

TEST(IntegralCompareTest, Inequality) {
    EXPECT_FALSE(compare::AreNumbersEqual(42, 43));
    EXPECT_FALSE(compare::AreNumbersEqual(-10, 10));
    EXPECT_FALSE(compare::AreNumbersEqual(0, 1));
    EXPECT_FALSE(compare::AreNumbersEqual(1234567890, 1234567891));
}

TYPED_TEST(FloatCompareTest, ExactEquality) {
    using T = TypeParam;
    EXPECT_TRUE(compare::AreNumbersEqual(T(1.0), T(1.0)));
    EXPECT_TRUE(compare::AreNumbersEqual(T(-2.5), T(-2.5)));
    EXPECT_TRUE(compare::AreNumbersEqual(T(0.0), T(0.0)));
    EXPECT_TRUE(compare::AreNumbersEqual(T(12345.6789), T(12345.6789)));
}

TYPED_TEST(FloatCompareTest, NearZero) {
    using T = TypeParam;
    const T eps = std::numeric_limits<T>::epsilon();

    EXPECT_TRUE(compare::AreNumbersEqual(T(0.0), T(eps * 0.5)));
    EXPECT_TRUE(compare::AreNumbersEqual(T(0.0), T(-eps * 0.5)));

    EXPECT_TRUE(compare::AreNumbersEqual(T(0.0), T(eps)));
    EXPECT_TRUE(compare::AreNumbersEqual(T(0.0), T(-eps)));

    EXPECT_FALSE(
        compare::AreNumbersEqual(T(0.0), T(this->tolerance_base * 1.1)));
    EXPECT_FALSE(
        compare::AreNumbersEqual(T(0.0), T(this->tolerance_base * 1.1)));
}

TYPED_TEST(FloatCompareTest, LargeValues) {
    using T = TypeParam;
    const T large_val = std::numeric_limits<T>::max() / T(10);

    T diff = large_val * this->tolerance_base * T(0.5);
    EXPECT_TRUE(compare::AreNumbersEqual(large_val, large_val + diff));
    EXPECT_TRUE(compare::AreNumbersEqual(large_val, large_val - diff));

    diff = large_val * this->tolerance_base * T(1.1);
    EXPECT_FALSE(compare::AreNumbersEqual(large_val, large_val + diff));
    EXPECT_FALSE(compare::AreNumbersEqual(large_val, large_val - diff));
}

TYPED_TEST(FloatCompareTest, NearMax) {
    using T = TypeParam;
    const T max_val = std::numeric_limits<T>::max();
    const T prev_val = std::nextafter(max_val, T(0));

    EXPECT_TRUE(compare::AreNumbersEqual(max_val, prev_val));

    T diff = max_val * this->tolerance_base * T(2.0);
    T separated_val = max_val - diff;
    EXPECT_FALSE(compare::AreNumbersEqual(max_val, separated_val));
}

TEST(SpecialValuesTest, NaN) {
    EXPECT_FALSE(compare::AreNumbersEqual(NAN, NAN));
    EXPECT_FALSE(compare::AreNumbersEqual(1.0f, NAN));
}

TEST(SpecialValuesTest, ZeroSign) {
    EXPECT_TRUE(compare::AreNumbersEqual(0.0, -0.0));
    EXPECT_TRUE(compare::AreNumbersEqual(0.0f, -0.0f));
}

TEST(CompileTimeChecks, MixedTypes) {
    static_assert(
        std::is_same_v<decltype(compare::AreNumbersEqual(1, 2)), bool>);
    static_assert(
        std::is_same_v<decltype(compare::AreNumbersEqual(1.0f, 2.0f)), bool>);
    static_assert(
        std::is_same_v<decltype(compare::AreNumbersEqual(1.0, 2.0)), bool>);
}
