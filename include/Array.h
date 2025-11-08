#pragma once
#include <memory>
#include <stdexcept>
#include <iterator>

template<typename T>
class Array {
private:
    std::shared_ptr<T[]> data;
    size_t capacity_;
    size_t size_;

    void reallocate(size_t new_capacity) {
        std::shared_ptr<T[]> new_data(new T[new_capacity]);
        for (size_t i = 0; i < size_; ++i)
            new_data[i] = std::move(data[i]);
        data = std::move(new_data);
        capacity_ = new_capacity;
    }

public:
    Array() : data(nullptr), capacity_(0), size_(0) {}
    
    explicit Array(size_t initial_capacity) 
        : data(new T[initial_capacity]), capacity_(initial_capacity), size_(0) {}

    void push_back(const T& value) {
        if (size_ >= capacity_) {
            size_t new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
            reallocate(new_capacity);
        }
        data[size_++] = value;
    }

    void push_back(T&& value) {
        if (size_ >= capacity_) {
            size_t new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
            reallocate(new_capacity);
        }
        data[size_++] = std::move(value);
    }

    void erase(size_t index) {
        if (index >= size_) throw std::out_of_range("Index out of range");
        for (size_t i = index; i < size_ - 1; ++i)
            data[i] = std::move(data[i + 1]);
        --size_;
    }

    T& operator[](size_t index) {
        if (index >= size_) throw std::out_of_range("Index out of range");
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= size_) throw std::out_of_range("Index out of range");
        return data[index];
    }

    size_t size() const { return size_; }
    size_t capacity() const { return capacity_; }
    bool empty() const { return size_ == 0; }

    T* begin() { return data.get(); }
    const T* begin() const { return data.get(); }
    T* end() { return data.get() + size_; }
    const T* end() const { return data.get() + size_; }
};