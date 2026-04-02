#ifndef CIRCLE_H
#define CIRCLE_H
#include "Shape.h"
#include "point.h"

class Circle: public Shape {
public:
    Circle(const Point& center, double radius);
    double Circumference() const override;
    double Area() const override;
    void Print() const override;
    static const int UnknownValue = -1;
private:
    Point center_;
    double radius_;
};

#endif
