#ifndef STRAIGHTEDGE_H
#define STRAIGHTEDGE_H
#include "edge.h"
class StraightEdge: public Edge {
public:
    StraightEdge(const Point& start, const Point& end);
    void Print() const override;
    double Length() const override;
};

#endif // STRAIGHTEDGE_H
