#ifndef MYPOLYGON_H
#define MYPOLYGON_H
#include "Shape.h"
#include "point.h"
#include "edge.h"
#include <vector>
class MyPolygon : public Shape {
public:
    MyPolygon(const std::vector<Edge*>& edges);
    ~MyPolygon() override;
    double Circumference() const override;
    double Area() const override;
    void Print() const override;
private:
    std::vector<Edge*> edges_;
};

#endif // MYPOLYGON_H
