#ifndef ARCEDGE_H
#define ARCEDGE_H
#include "edge.h"
#include "point.h"

class ArcEdge: public Edge {
public:
    ArcEdge(const Point& Start, const Point& End, const Point& Center);
    void Print() const override;
    double Length() const override;
    Point getCenter() const;
    std::pair<Point, Point> get() const;
protected:
    Point center_;
};


#endif // ARCEDGE_H
