#pragma once
#include "Figure.h"
#include <cmath>
#include <vector>

template<Scalar T>
class Rhombus : public Figure<T> {
private:
    std::vector<std::unique_ptr<Point<T>>> points;

public:
    Rhombus() {
        for (int i = 0; i < 4; ++i)
            points.push_back(std::make_unique<Point<T>>());
    }

    Rhombus(const Rhombus& other) {
        for (const auto& p : other.points)
            points.push_back(std::make_unique<Point<T>>(*p));
    }

    Rhombus& operator=(const Rhombus& other) {
        if (this != &other) {
            points.clear();
            for (const auto& p : other.points)
                points.push_back(std::make_unique<Point<T>>(*p));
        }
        return *this;
    }

    Point<T> center() const override {
    T cx = 0, cy = 0;
    for (const auto& p : points) {
        cx += p->x;
        cy += p->y;
    }
    return Point<T>(cx/4, cy/4);
}

    operator double() const override {
        double d1 = std::hypot(points[0]->x - points[2]->x, points[0]->y - points[2]->y);
        double d2 = std::hypot(points[1]->x - points[3]->x, points[1]->y - points[3]->y);
        return d1 * d2 / 2;
    }

    void print(std::ostream& os) const override {
        os << "Rhombus: ";
        for (const auto& p : points)
            os << "(" << p->x << "," << p->y << ") ";
    }

    void read(std::istream& is) override {
        for (const auto& p : points)
            is >> p->x >> p->y;
    }

    bool operator==(const Figure<T>& other) const override {
        const auto* o = dynamic_cast<const Rhombus*>(&other);
        if (!o) return false;
        for (size_t i = 0; i < points.size(); ++i)
            if (*points[i] != *o->points[i]) return false;
        return true;
    }
};