#include "circle.h"
#include <cmath>
#include <iostream>

Circle::Circle(const Point& center, double radius) : center_(center), radius_(radius) {
    if (radius <= 0) {
        std::cerr << "半径不能为非正数！" << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

double Circle::Circumference() const {
    return 2 * M_PI * radius_;
}

double Circle::Area() const {
    return radius_ * radius_ * M_PI;
}

void Circle::Print() const {
    std::cout << "圆心位于(" << center_.getX() << ',' << center_.getY() << ")，";
    std::cout << "半径为" << radius_ << "，面积为" << Area() << "，周长为" << Circumference() << "的圆";
}
