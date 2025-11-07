#include "array.hpp"

#include <cassert>
#include <cstddef>

#include "out_of_range_exception.hpp"

namespace array {
namespace {
constexpr std::size_t DEFAULT_CAPACITY = 10;

template <class T>
inline T* AllocateRaw(std::size_t count) {
    return reinterpret_cast<T*>(
        ::operator new[](count * sizeof(T), std::align_val_t(alignof(T))));
}

template <class T>
void RawMemoryDeleter<T>::operator()(T* ptr) const {
    ::operator delete[](ptr, std::align_val_t(alignof(T)));
}
}  // namespace

template <class T>
Array<T>::Array()
    : capacity_(0)
    , size_(0)
    , data_() {}

template <class T>
Array<T>::Array(std::size_t size) requires std::is_default_constructible_v<T>
    : capacity_(size),
      size_(size),
      data_(std::shared_ptr<T[]>(AllocateRaw<T>(capacity_),
                                 RawMemoryDeleter<T>())) {
    for (std::size_t i = 0; i < capacity_; ++i) {
        new (std::addressof(data_[i])) T();
    }
}

template <class T>
Array<T>::Array(std::size_t size,
                const T& obj) requires std::is_copy_constructible_v<T>
    : capacity_(size),
      size_(size),
      data_(std::shared_ptr<T[]>(AllocateRaw<T>(capacity_),
                                 RawMemoryDeleter<T>())) {
    for (std::size_t i = 0; i < size_; ++i) {
        new (std::addressof(data_[i])) T(obj);
    }
}

template <class T>
Array<T>::Array(
    const std::initializer_list<T>& il) requires std::is_copy_constructible_v<T>
    : capacity_(il.size()),
      size_(il.size()),
      data_(std::shared_ptr<T[]>(AllocateRaw<T>(capacity_),
                                 RawMemoryDeleter<T>())) {
    std::size_t i = 0;
    for (const T& obj : il) {
        new (std::addressof(data_[i])) T(obj);
        ++i;
    }
}

template <class T>
Array<T>::Array(const Array<T>& other)
    : capacity_(other.capacity_)
    , size_(other.size_)
    , data_(std::shared_ptr<T[]>(AllocateRaw<T>(capacity_),
                                 RawMemoryDeleter<T>())) {
    for (std::size_t i = 0; i < size_; ++i) {
        new (std::addressof(data_[i])) T(other[i]);
    }
}

template <class T>
Array<T>::Array(Array&& other) noexcept
    : capacity_(other.capacity_)
    , size_(other.size_)
    , data_(std::move(other.data_)) {
    other.size_ = 0;
    other.capacity_ = 0;
}

template <class T>
Array<T>::~Array() noexcept {
    Clear();
}

template <class T>
void Array<T>::Swap(Array<T>& other) noexcept {
    using std::swap;
    swap(capacity_, other.capacity_);
    swap(size_, other.size_);
    swap(data_, other.data_);
}

// You can't overload/specialize std::swap for template classes. Overload: can't
// list all T, Specilazation: partial specialization for functions is not
// allowed. Only ADL in possible
template <class T>
void swap(Array<T>& first, Array<T>& second) {
    first.Swap(second);
}

template <class T>
Array<T>& Array<T>::operator=(const Array<T>& other) {
    if (this == &other) {
        return *this;
    }
    Array<T> temp = other;
    this->Swap(temp);
    return *this;
}

template <class T>
Array<T>& Array<T>::operator=(Array<T>&& other) noexcept {
    if (this == &other) {
        return *this;
    }
    Array<T> temp = std::move(other);
    this->Swap(temp);
    return *this;
}

template <class T>
template <class... Args>
void Array<T>::EmplaceBack(Args&&... args) {
    CheckCapacity(size_ + 1);
    new (std::addressof(data_[size_])) T(std::forward<Args>(args)...);
    ++size_;
}

// If it was universal reference, then the requires would have become bloated.
// Also, in std it's overloaded
template <class T>
void Array<T>::PushBack(const T& obj) requires std::is_copy_constructible_v<T> {
    EmplaceBack(obj);
}

template <class T>
void Array<T>::PushBack(T&& obj) requires std::is_move_constructible_v<T> {
    EmplaceBack(std::move(obj));
}

template <class T>
void Array<T>::Insert(std::size_t pos,
                      const T& obj) requires std::is_copy_assignable_v<T> &&
    std::is_move_constructible_v<T> && std::is_move_assignable_v<T> {
    CheckCapacity(size_ + 1);
    // Move the last object
    new (std::addressof(data_[size_])) T(std::move(Back()));
    // Moving others
    for (std::size_t i = size_; i >= pos + 2; --i) {
        data_[i - 1] = std::move(data_[i - 2]);
    }
    data_[pos] = obj;
}

template <class T>
void Array<T>::Insert(std::size_t pos, T&& obj) requires
    std::is_move_constructible_v<T> && std::is_move_assignable_v<T> {
    CheckCapacity(size_ + 1);
    // Move the last object
    new (std::addressof(data_[size_])) T(std::move(Back()));
    // Moving others
    for (std::size_t i = size_; i >= pos + 2; --i) {
        data_[i - 1] = std::move(data_[i - 2]);
    }
    data_[pos] = std::move(obj);
    ++size_;
}

template <class T>
T& Array<T>::Front() {
    assert(size_ > 0);
    return data_[0];
}

template <class T>
const T& Array<T>::Front() const {
    assert(size_ > 0);
    return data_[0];
}

template <class T>
T& Array<T>::Back() {
    assert(size_ > 0);
    return data_[size_ - 1];
}

template <class T>
const T& Array<T>::Back() const {
    assert(size_ > 0);
    return data_[size_ - 1];
}

template <class T>
T& Array<T>::operator[](std::size_t i) {
    assert(i < size_);
    return data_[i];
}

template <class T>
const T& Array<T>::operator[](std::size_t i) const {
    assert(i < size_);
    return data_[i];
}

template <class T>
T& Array<T>::At(std::size_t i) {
    if (i >= size_) {
        throw exceptions::OutOfRangeArrayException("Out of range exception");
    }
    return data_[i];
}

template <class T>
const T& Array<T>::At(std::size_t i) const {
    if (i >= size_) {
        throw exceptions::OutOfRangeArrayException("Out of range exception");
    }
    return data_[i];
}

template <class T>
void Array<T>::Pop(std::size_t pos) {
    assert(pos < size_);
    for (std::size_t i = pos; i < size_ - 1; ++i) {
        data_[i] = std::move(data_[i + 1]);
    }
    Back().~T();
    --size_;
}

template <class T>
void Array<T>::PopBack() {
    assert(size_ > 0);
    Back().~T();
    --size_;
}

template <class T>
void Array<T>::Clear() noexcept {
    for (std::size_t i = 0; i < size_; ++i) {
        data_[i].~T();
    }
    size_ = 0;
}

template <class T>
const T* Array<T>::Data() const noexcept {
    return data_.get();
}

template <class T>
T* Array<T>::Data() noexcept {
    return data_.get();
}

template <class T>
std::size_t Array<T>::Size() const noexcept {
    return size_;
}

template <class T>
std::size_t Array<T>::Capacity() const noexcept {
    return capacity_;
}

template <class T>
bool Array<T>::Empty() const noexcept {
    return size_ == 0;
}

template <class T>
void Array<T>::Reserve(
    std::size_t size) requires std::is_move_constructible_v<T> {
    if (size <= capacity_) {
        return;
    }
    std::shared_ptr<T[]> newData(AllocateRaw<T>(size), RawMemoryDeleter<T>());
    for (std::size_t i = 0; i < size_; ++i) {
        new (std::addressof(newData[i])) T(std::move(data_[i]));
        data_[i].~T();
    }
    capacity_ = size;
    data_ = newData;
}

template <class T>
void Array<T>::CheckCapacity(
    std::size_t size) requires std::is_move_constructible_v<T> {
    if (size > capacity_) {
        Reserve(std::max(2 * capacity_, DEFAULT_CAPACITY));
    }
}
}  // namespace array
