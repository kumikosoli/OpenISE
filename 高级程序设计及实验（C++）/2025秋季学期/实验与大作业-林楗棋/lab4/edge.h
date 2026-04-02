#ifndef EDGE_H
#define EDGE_H
#include "point.h"
#include <iostream>
#include <cmath>

class Edge {
public:
    Edge(const Point& start, const Point& end) : p1_(start), p2_(end) {}
    virtual ~Edge() {}; // 讲解虚函数
    std::pair<Point, Point> get() {
        return std::make_pair(p1_, p2_);
    }
    virtual void Print() const = 0;
    virtual double Length() const = 0;
protected:
    Point p1_;
    Point p2_;
};
#endif // EDGE_H