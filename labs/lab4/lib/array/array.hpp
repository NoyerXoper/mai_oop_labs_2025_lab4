#pragma once

#include <initializer_list>
#include <memory>
#include <type_traits>

namespace array {

namespace {
template <class T>
struct RawMemoryDeleter {
    void operator()(T* ptr) const;
};
}  // namespace

// This is bad. Really bad.
// It's all because of ban of raw ptr.
// Array (vector) must be on eiter unique_ptr<T[], Deleter> or raw ptr.
// Shared ptr is bad for vector because: it uses more memory and some other
// things that we would talk in few next lines. About Data(): it is either UB or
// it makes vector slow. Return types that Data() can have:
// std::shared_ptr<T[]>, std::weak_ptr<T[]>, T* weak_ptr<T[]> ~ shared_ptr<T[]>
// because we can instantly call lock(). shared_ptr<T[]> is bad because the user
// might think that if he got shared_ptr, then objects won't be destroyed. It
// can be achieved, but it would significantly reduce performace of the vector
// or require more heap allocations: it would require storing size in it's
// deleter size can't be reference in neither vector nor deleter because it can
// easily become dangling if it's reference in deleter or if it's reference in
// array, then we can call reset() on Data() and mess things up. So, we can make
// it shared_ptr. But it would require one more allocation and I don't like it.
// So, there is T* left. It still can be invalidated, but the user knows about
// it. So, if we stored data in T*, it would be much easier, more perfomant,
// more lightweight, more blazing.
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

    T* Data() const noexcept;

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
    std::shared_ptr<T[]> data_;
};
}  // namespace array

#include "array.ipp"
