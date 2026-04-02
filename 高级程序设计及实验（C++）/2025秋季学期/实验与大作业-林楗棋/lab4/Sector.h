#ifndef SECTOR_H
#define SECTOR_H
#include "circle.h"
#include "ArcEdge.h"
class Sector: public Circle {
public:
    Sector(const Point& center, double radius, const ArcEdge& edge);
    double Circumference() const override;
    double Area() const override;
    void Print() const override;
    static const int UnknownValue = -1;
private:
    ArcEdge arcedge;
    Point center_;
    double radius_;
};



#endif
