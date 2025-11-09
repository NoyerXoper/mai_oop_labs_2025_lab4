#pragma once

#include <initializer_list>
#include <type_traits>

namespace array {
// Rewrote this to raw pointer because I didn't understand the problem with my
// previous solution: I had a custom deleter that deleted the memory for my and
// array called the destructors of constructed objects So, there was only one
// place for UB: Data(), but it's the same thing with the std::vector, so I'm
// not sure about what was the "UB" And by the way, shared_ptr has only one
// template parameter, Deleter it stores using type erasure, only unique_ptr
// gets it from template parameter
template <class T>
class Array {
public:
    Array();

    explicit Array(std::size_t i) requires std::is_default_constructible_v<T>;

    Array(std::size_t size,
          const T& obj) requires std::is_copy_constructible_v<T>;

    Array(const std::initializer_list<T>& il) requires
        std::is_copy_constructible_v<T>;

    Array(const Array& other);
    Array(Array&& other) noexcept;

    ~Array() noexcept;

    Array& operator=(const Array& other);
    Array& operator=(Array&& other) noexcept;

    template <typename... Args>
    void EmplaceBack(Args&&... args);

    void PushBack(const T& obj) requires std::is_copy_constructible_v<T>;
    void PushBack(T&& obj) requires std::is_move_constructible_v<T>;

    void Insert(std::size_t pos,
                const T& obj) requires std::is_copy_assignable_v<T> &&
        std::is_move_constructible_v<T> && std::is_move_assignable_v<T>;
    void Insert(std::size_t pos, T&& obj) requires
        std::is_move_constructible_v<T> && std::is_move_assignable_v<T>;

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

    const T* Data() const noexcept;
    T* Data() noexcept;

    std::size_t Size() const noexcept;
    std::size_t Capacity() const noexcept;
    bool Empty() const noexcept;

    void Reserve(std::size_t size) requires std::is_move_constructible_v<T>;
    template <class U>
    friend void swap(Array<U>& first, Array<U>& second);

private:
    inline void
    CheckCapacity(std::size_t size) requires std::is_move_constructible_v<T>;
    void Swap(Array& other) noexcept;
    std::size_t capacity_;
    std::size_t size_;
    T* data_;
};
}  // namespace array

#include "array.ipp"
