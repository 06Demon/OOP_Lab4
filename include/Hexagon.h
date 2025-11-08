#pragma once
#include "Figure.h"
#include <vector>
#include <concepts>
#include <cmath>

template<Scalar T>
class Hexagon : public Figure<T> {
private:
    std::vector<std::unique_ptr<Point<T>>> points;

public:
    Hexagon() {
        for (int i = 0; i < 6; ++i)
            points.push_back(std::make_unique<Point<T>>());
    }

    Hexagon(const Hexagon& other) {
        for (const auto& p : other.points)
            points.push_back(std::make_unique<Point<T>>(*p));
    }

    Hexagon& operator=(const Hexagon& other) {
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
        return Point<T>(cx/6, cy/6);
    }

    operator double() const override {
        double area = 0;
        for (int i = 0; i < 6; ++i) {
            int j = (i + 1) % 6;
            area += points[i]->x * points[j]->y - points[j]->x * points[i]->y;
        }
        return std::abs(area) / 2.0;
    }

    void print(std::ostream& os) const override {
        os << "Hexagon: ";
        for (const auto& p : points)
            os << "(" << p->x << "," << p->y << ") ";
    }

    void read(std::istream& is) override {
        for (const auto& p : points)
            is >> p->x >> p->y;
    }

    bool operator==(const Figure<T>& other) const override {
        const auto* o = dynamic_cast<const Hexagon*>(&other);
        if (!o) return false;
        for (size_t i = 0; i < points.size(); ++i)
            if (*points[i] != *o->points[i]) return false;
        return true;
    }
};