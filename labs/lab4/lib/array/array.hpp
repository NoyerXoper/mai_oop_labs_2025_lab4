#pragma once

#include <memory>
#include <initializer_list>
#include <type_traits>

namespace array {

namespace {
template<class T, class U>
struct ConstMatcher {
    using type = std::remove_cv_t<T>;
};

template<class T, class U>
struct ConstMatcher<T, const U> {
    using type = const T;
};

template<class T, class U>
using ConstMatcher_t = ConstMatcher<T, U>::type;
}

template <class T>
struct RawMemoryDeleter {
    void operator()(T* ptr) const;
};

template <class T>
class Array {
public:
    Array();

    explicit Array(std::size_t i) requires std::is_default_constructible_v<T>;

    Array(std::size_t size, const T& obj) requires std::is_copy_constructible_v<T>;

    Array(const std::initializer_list<T>& il) requires std::is_copy_constructible_v<T>;

    Array(const Array& other);
    Array(Array&& other) noexcept;

    ~Array() noexcept;

    Array& operator=(const Array& other);
    Array& operator=(Array&& other) noexcept;

    template<typename... Args>
    void EmplaceBack(Args&&... args);

    void PushBack(const T& obj) requires std::is_copy_constructible_v<T>;
    void PushBack(T&& obj) requires std::is_move_constructible_v<T>;

    void Insert(std::size_t pos, const T& obj) requires std::is_copy_assignable_v<T> && std::is_move_constructible_v<T> && std::is_move_assignable_v<T>;
    void Insert(std::size_t pos, T&& obj) requires std::is_move_constructible_v<T> && std::is_move_assignable_v<T>;

    T& Front();
    const T& Front() const;

    T& Back();
    const T& Back() const;

    T& operator[](std::size_t i);
    const T& operator[](std::size_t i) const;

    T& At(std::size_t i);
    const T& At(std::size_t i) const;

    void PopBack();
    void Pop(std::size_t i);

    void Clear() noexcept;
    
    std::weak_ptr<T[]> Data() const noexcept;

    std::size_t Size() const noexcept;
    std::size_t Capacity() const noexcept;
    bool Empty() const noexcept;

    void Reserve(std::size_t size) requires std::is_move_constructible_v<T>;
    friend void swap(Array& first, Array& second) noexcept;

private:
    void CheckCapacity(std::size_t size) requires std::is_move_constructible_v<T>;
    void Swap(Array& other) noexcept;
    std::size_t capacity_;
    std::size_t size_; 
    std::shared_ptr<T[]> data_;
};
}

#include "array.ipp"
