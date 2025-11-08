#pragma once
#include "Figure.h"
#include <vector>
#include <concepts>
#include <cmath>

template<Scalar T>
class Pentagon : public Figure<T> {
private:
    std::vector<std::unique_ptr<Point<T>>> points;

public:
    Pentagon() {
        for (int i = 0; i < 5; ++i)
            points.push_back(std::make_unique<Point<T>>());
    }

    Pentagon(const Pentagon& other) {
        for (const auto& p : other.points)
            points.push_back(std::make_unique<Point<T>>(*p));
    }

    Pentagon& operator=(const Pentagon& other) {
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
        return Point<T>(cx/5, cy/5);
    }

    operator double() const override {
        double area = 0;
        for (int i = 0; i < 5; ++i) {
            int j = (i + 1) % 5;
            area += points[i]->x * points[j]->y - points[j]->x * points[i]->y;
        }
        return std::abs(area) / 2.0;
    }

    void print(std::ostream& os) const override {
        os << "Pentagon: ";
        for (const auto& p : points)
            os << "(" << p->x << "," << p->y << ") ";
    }

    void read(std::istream& is) override {
        for (const auto& p : points)
            is >> p->x >> p->y;
    }

    bool operator==(const Figure<T>& other) const override {
        const auto* o = dynamic_cast<const Pentagon*>(&other);
        if (!o) return false;
        for (size_t i = 0; i < points.size(); ++i)
            if (*points[i] != *o->points[i]) return false;
        return true;
    }
};