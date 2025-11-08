#pragma once
#include "Point.h"
#include <iostream>
#include <memory>

template<Scalar T>
class Figure {
public:
    virtual ~Figure() = default;
    
    virtual Point<T> center() const = 0;
    virtual operator double() const = 0;
    virtual void print(std::ostream& os) const = 0;
    virtual void read(std::istream& is) = 0;
    virtual bool operator==(const Figure& other) const = 0;

    friend std::ostream& operator<<(std::ostream& os, const Figure& f) {
        f.print(os);
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Figure& f) {
        f.read(is);
        return is;
    }
};