#include "ArcEdge.h"
#include "iostream"
#include "cmath"

namespace {
double Distance(Point a, Point b) {
    const double dX = a.getX() - b.getX();
    const double dY = a.getY() - b.getY();
    return std::sqrt(dX * dX + dY * dY);
}
} 

ArcEdge::ArcEdge(const Point& start, const Point& end, const Point& center): Edge(start, end), center_(center) {
    if (Distance(start, center) != Distance(end, center)) {
        std::cerr << "中心距两点距离不一致！" << std::endl;
        std::exit(EXIT_FAILURE);
    }
};
// 一个派生类只能初始化其自身的成员和其直接基类的成员。

void ArcEdge::Print() const{
    std::cout << "圆心为(" << center_.getX() << "," << center_.getY() << ')';
    std::cout << "两端点为(" << p1_.getX() << "," << p1_.getY() << ")和(" << p2_.getX() << ',' << p2_.getY() << ")" << std::endl;
}

double ArcEdge::Length() const { // 用内积计算角度大小，求劣弧长
    double R = Distance(center_, p1_);
    double res = (p1_.getX() - center_.getX()) * (p2_.getX() - center_.getX()) + (p1_.getY() - center_.getY()) * (p2_.getY() - center_.getY());
    double alpha = std::acos(res / (R*R));
    return R * alpha;
}

Point ArcEdge::getCenter() const {
    return center_;
}

std::pair<Point, Point> ArcEdge::get() const {
    return std::make_pair(p1_, p2_);
}
