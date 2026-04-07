#include "Sector.h"
#include <cmath>
#include <iostream>

namespace {
double SectorDistance(const Point& a, const Point& b) {
    const double dX = a.getX() - b.getX();
    const double dY = a.getY() - b.getY();
    return std::sqrt(dX * dX + dY * dY);
}
} // namespace

Sector::Sector(const Point& cen, double radius, const ArcEdge& aredg): Circle(cen, radius), arcedge(aredg), center_(cen), radius_(radius) {
    if (aredg.getCenter().get() != cen.get()) {
        std::cerr << "扇形的圆心与弧边的圆心不一致！" << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

double Sector::Circumference() const {
    return  2 * SectorDistance(center_, arcedge.get().first) + arcedge.Length();
}

void Sector::Print() const {
    std::cout << "周长为" << Circumference() << "面积为" << Area() << "劣弧扇形的";
    arcedge.Print();
}

double Sector::Area() const {
    double R = SectorDistance(center_, arcedge.get().first);
    double alpha = std::acos((arcedge.get().first.getX() - center_.getX()) * (arcedge.get().second.getX() - center_.getX()) +
                             (arcedge.get().first.getY() - center_.getY()) * (arcedge.get().second.getY() - center_.getY())) / (R * R);
    return 0.5 * R * R * alpha;
}
