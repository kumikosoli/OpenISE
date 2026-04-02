#include "StraightEgde.h"
#include "iostream"
#include "cmath"

void StraightEdge::Print() const{
    std::cout << "从点(" << p1_.getX() << "," << p1_.getY() << ")";
    std::cout << "至点(" << p2_.getX() << "," << p2_.getY() << ")" << std::endl;
}

double StraightEdge::Length() const{
    double dX = p1_.getX() - p2_.getX();
    double dY = p1_.getY() - p2_.getY();
    return std::sqrt(dX * dX + dY * dY);
}

StraightEdge::StraightEdge(const Point& start, const Point& end) : Edge(start, end) {}
