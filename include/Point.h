#pragma once
#include <concepts>

template<typename T>
concept Scalar = std::is_scalar_v<T>;

template<Scalar T>
class Point {
public:
    T x, y;
    
    Point() : x(0), y(0) {}
    Point(T x, T y) : x(x), y(y) {}
    
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};