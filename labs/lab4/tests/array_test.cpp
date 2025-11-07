#include <stdexcept>
#include <vector>

#include <gtest/gtest.h>

#include "array.hpp"
#include "out_of_range_exception.hpp"

struct NonTrivialCopy {
    int data;
    NonTrivialCopy()
        : data(0) {}
    NonTrivialCopy(int d)
        : data(d) {}
    NonTrivialCopy(const NonTrivialCopy& other)
        : data(other.data) {}
    NonTrivialCopy& operator=(const NonTrivialCopy& other) {
        if (this != &other)
            data = other.data;
        return *this;
    }
    bool operator==(const NonTrivialCopy& other) const {
        return data == other.data;
    }
    bool operator!=(const NonTrivialCopy& other) const {
        return !(*this == other);
    }
};

class MovableOnly {
public:
    int value;
    explicit MovableOnly(int v = 0)
        : value(v) {}
    MovableOnly(const MovableOnly&) = delete;
    MovableOnly& operator=(const MovableOnly&) = delete;
    MovableOnly(MovableOnly&&) noexcept = default;
    MovableOnly& operator=(MovableOnly&&) noexcept = default;
    bool operator==(const MovableOnly& other) const {
        return value == other.value;
    }
    bool operator!=(const MovableOnly& other) const {
        return !(*this == other);
    }
};

class NonDefaultConstructible {
public:
    int value;
    explicit NonDefaultConstructible(int v)
        : value(v) {}
    NonDefaultConstructible(const NonDefaultConstructible&) = default;
    NonDefaultConstructible&
    operator=(const NonDefaultConstructible&) = default;
    bool operator==(const NonDefaultConstructible& other) const {
        return value == other.value;
    }
    bool operator!=(const NonDefaultConstructible& other) const {
        return !(*this == other);
    }

private:
    NonDefaultConstructible() = delete;
};

template <typename T, typename Container>
bool ValidateArrayContents(const array::Array<T>& arr,
                           const Container& expected) {
    if (arr.Empty() || arr.Size() != expected.size()) {
        return false;
    }

    for (size_t i = 0; i < expected.size(); ++i) {
        if (!(arr[i] == expected[i])) {
            return false;
        }
    }
    return true;
}

TEST(ArrayTest, Int_DefaultConstructor) {
    array::Array<int> arr;
    EXPECT_EQ(arr.Size(), 0);
    EXPECT_EQ(arr.Capacity(), 0);
    EXPECT_TRUE(arr.Empty());
}

TEST(ArrayTest, Int_ConstructorWithSize) {
    array::Array<int> arr(5);
    EXPECT_EQ(arr.Size(), 5);
    EXPECT_GE(arr.Capacity(), 5);
    EXPECT_FALSE(arr.Empty());
    for (size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(arr[i], 0);
    }

    std::vector<int> expected(5, 0);
    EXPECT_TRUE(ValidateArrayContents(arr, expected));
}

TEST(ArrayTest, Int_ConstructorWithSizeAndValue) {
    array::Array<int> arr(3, 42);
    EXPECT_EQ(arr.Size(), 3);
    EXPECT_GE(arr.Capacity(), 3);
    for (size_t i = 0; i < 3; ++i) {
        EXPECT_EQ(arr[i], 42);
    }

    std::vector<int> expected = {42, 42, 42};
    EXPECT_TRUE(ValidateArrayContents(arr, expected));
}

TEST(ArrayTest, Int_InitializerListConstructor) {
    array::Array<int> arr = {1, 2, 3};
    EXPECT_EQ(arr.Size(), 3);
    EXPECT_GE(arr.Capacity(), 3);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);

    std::vector<int> expected = {1, 2, 3};
    EXPECT_TRUE(ValidateArrayContents(arr, expected));
}

TEST(ArrayTest, Int_CopyConstructor) {
    array::Array<int> arr1 = {1, 2, 3};
    array::Array<int> arr2(arr1);
    EXPECT_EQ(arr2.Size(), 3);
    EXPECT_EQ(arr2[0], 1);
    EXPECT_EQ(arr2[1], 2);
    EXPECT_EQ(arr2[2], 3);

    std::vector<int> expected = {1, 2, 3};
    EXPECT_TRUE(ValidateArrayContents(arr2, expected));
}

TEST(ArrayTest, Int_MoveConstructor) {
    array::Array<int> arr1 = {1, 2, 3};
    array::Array<int> arr2(std::move(arr1));
    EXPECT_EQ(arr2.Size(), 3);
    EXPECT_EQ(arr1.Size(), 0);
    EXPECT_TRUE(arr1.Empty());

    std::cout << arr2[0] << std::endl;

    std::vector<int> expected = {1, 2, 3};
    EXPECT_TRUE(ValidateArrayContents(arr2, expected));
}

TEST(ArrayTest, Int_PushBack) {
    array::Array<int> arr;
    arr.PushBack(10);
    arr.PushBack(20);
    EXPECT_EQ(arr.Size(), 2);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);

    std::vector<int> expected = {10, 20};
    EXPECT_TRUE(ValidateArrayContents(arr, expected));
}

TEST(ArrayTest, Int_EmplaceBack) {
    array::Array<int> arr;
    arr.EmplaceBack(30);
    EXPECT_EQ(arr.Size(), 1);
    EXPECT_EQ(arr[0], 30);

    std::vector<int> expected = {30};
    EXPECT_TRUE(ValidateArrayContents(arr, expected));
}

TEST(ArrayTest, Int_AtThrows) {
    array::Array<int> arr(5);
    EXPECT_NO_THROW(arr.At(4));
    EXPECT_THROW(arr.At(5), exceptions::OutOfRangeArrayException);
    EXPECT_THROW(arr.At(10), exceptions::OutOfRangeArrayException);
}

TEST(ArrayTest, Int_ElementTypeAccess) {
    array::Array<int> arr = {10, 20, 30};
    EXPECT_EQ(arr.Front(), 10);
    EXPECT_EQ(arr.Back(), 30);
    const auto& c_arr = arr;
    EXPECT_EQ(c_arr.Front(), 10);
    EXPECT_EQ(c_arr.Back(), 30);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(c_arr[1], 20);
}

TEST(ArrayTest, Int_Reserve) {
    array::Array<int> arr;
    arr.Reserve(10);
    EXPECT_GE(arr.Capacity(), 10);
    EXPECT_EQ(arr.Size(), 0);
}

TEST(ArrayTest, Int_Clear) {
    array::Array<int> arr(5);
    arr.Clear();
    EXPECT_EQ(arr.Size(), 0);
    EXPECT_GE(arr.Capacity(), 5);
}

TEST(ArrayTest, Int_PopBack) {
    array::Array<int> arr = {1, 2, 3};
    arr.PopBack();
    EXPECT_EQ(arr.Size(), 2);
    EXPECT_EQ(arr.Back(), 2);
}

TEST(ArrayTest, Int_Swap) {
    array::Array<int> arr1 = {1, 2};
    array::Array<int> arr2 = {3, 4, 5};
    swap(arr1, arr2);
    EXPECT_EQ(arr1.Size(), 3);
    EXPECT_EQ(arr2.Size(), 2);
    EXPECT_EQ(arr1[0], 3);
    EXPECT_EQ(arr2[0], 1);

    std::vector<int> expected1 = {3, 4, 5};
    std::vector<int> expected2 = {1, 2};
    EXPECT_TRUE(ValidateArrayContents(arr1, expected1));
    EXPECT_TRUE(ValidateArrayContents(arr2, expected2));
}

TEST(ArrayTest, NonTrivialCopy_ConstructorWithSizeAndValue) {
    NonTrivialCopy obj(42);
    array::Array<NonTrivialCopy> arr(3, obj);
    EXPECT_EQ(arr.Size(), 3);
    for (size_t i = 0; i < 3; ++i) {
        EXPECT_EQ(arr[i].data, 42);
    }

    std::vector<NonTrivialCopy> expected = {
        NonTrivialCopy(42), NonTrivialCopy(42), NonTrivialCopy(42)};
    EXPECT_TRUE(ValidateArrayContents(arr, expected));
}

TEST(ArrayTest, NonTrivialCopy_InitializerListConstructor) {
    array::Array<NonTrivialCopy> arr = {NonTrivialCopy(1), NonTrivialCopy(2)};
    EXPECT_EQ(arr.Size(), 2);
    EXPECT_EQ(arr[0].data, 1);
    EXPECT_EQ(arr[1].data, 2);

    std::vector<NonTrivialCopy> expected = {NonTrivialCopy(1),
                                            NonTrivialCopy(2)};
    EXPECT_TRUE(ValidateArrayContents(arr, expected));
}

TEST(ArrayTest, MovableOnly_DefaultConstructor) {
    array::Array<MovableOnly> arr;
    EXPECT_EQ(arr.Size(), 0);
    EXPECT_TRUE(arr.Empty());
}

TEST(ArrayTest, MovableOnly_EmplaceBack) {
    array::Array<MovableOnly> arr;
    arr.EmplaceBack(10);
    arr.EmplaceBack(20);
    EXPECT_EQ(arr.Size(), 2);
    EXPECT_EQ(arr[0].value, 10);
    EXPECT_EQ(arr[1].value, 20);

    std::vector<MovableOnly> expected;
    expected.emplace_back(10);
    expected.emplace_back(20);
    EXPECT_TRUE(ValidateArrayContents(arr, expected));
}

TEST(ArrayTest, MovableOnly_MoveConstructor) {
    array::Array<MovableOnly> arr1;
    arr1.EmplaceBack(10);
    array::Array<MovableOnly> arr2(std::move(arr1));
    EXPECT_EQ(arr2.Size(), 1);
    EXPECT_EQ(arr2[0].value, 10);
    EXPECT_TRUE(arr1.Empty());

    std::vector<MovableOnly> expected;
    expected.emplace_back(10);
    EXPECT_TRUE(ValidateArrayContents(arr2, expected));
}

TEST(ArrayTest, MovableOnly_Reserve) {
    array::Array<MovableOnly> arr;
    arr.Reserve(5);
    EXPECT_GE(arr.Capacity(), 5);
    arr.EmplaceBack(1);
    arr.EmplaceBack(2);
    EXPECT_EQ(arr.Size(), 2);
    EXPECT_GE(arr.Capacity(), 5);

    std::vector<MovableOnly> expected;
    expected.emplace_back(1);
    expected.emplace_back(2);
    EXPECT_TRUE(ValidateArrayContents(arr, expected));
}

TEST(ArrayTest, NonDefaultConstructible_InitializerListConstructor) {
    array::Array<NonDefaultConstructible> arr = {NonDefaultConstructible(1),
                                                 NonDefaultConstructible(2)};
    EXPECT_EQ(arr.Size(), 2);
    EXPECT_EQ(arr[0].value, 1);
    EXPECT_EQ(arr[1].value, 2);

    std::vector<NonDefaultConstructible> expected;
    expected.emplace_back(1);
    expected.emplace_back(2);
    EXPECT_TRUE(ValidateArrayContents(arr, expected));
}

TEST(ArrayTest, NonDefaultConstructible_EmplaceBack) {
    array::Array<NonDefaultConstructible> arr;
    arr.EmplaceBack(10);
    arr.EmplaceBack(20);
    EXPECT_EQ(arr.Size(), 2);
    EXPECT_EQ(arr[0].value, 10);
    EXPECT_EQ(arr[1].value, 20);

    std::vector<NonDefaultConstructible> expected;
    expected.emplace_back(10);
    expected.emplace_back(20);
    EXPECT_TRUE(ValidateArrayContents(arr, expected));
}

TEST(ArrayDeathTest, FrontBackEmpty) {
    array::Array<int> arr;
    ASSERT_DEATH(arr.Front(), "");
    ASSERT_DEATH(arr.Back(), "");
}

TEST(ArrayDeathTest, OperatorBracketEmpty) {
    array::Array<int> arr;
    ASSERT_DEATH(arr[0], "");
}

TEST(ArrayTest, NonDefaultConstructible_NoDefaultConstructor) {
    array::Array<NonDefaultConstructible> arr;
    arr.EmplaceBack(42);
    EXPECT_EQ(arr.Size(), 1);
    EXPECT_EQ(arr[0].value, 42);
}

TEST(ArrayTest, MovableOnly_Insert) {
    array::Array<MovableOnly> arr;
    arr.EmplaceBack(10);
    arr.EmplaceBack(30);

    arr.Insert(1, MovableOnly(20));

    EXPECT_EQ(arr.Size(), 3);
    EXPECT_EQ(arr[0].value, 10);
    EXPECT_EQ(arr[1].value, 20);
    EXPECT_EQ(arr[2].value, 30);

    std::vector<MovableOnly> expected;
    expected.emplace_back(10);
    expected.emplace_back(20);
    expected.emplace_back(30);
    EXPECT_TRUE(ValidateArrayContents(arr, expected));
}
