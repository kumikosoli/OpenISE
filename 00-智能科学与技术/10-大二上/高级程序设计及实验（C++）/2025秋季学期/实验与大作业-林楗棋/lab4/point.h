#ifndef POINT_H
#define POINT_H
#include <utility>
#include <iostream>

class Point {
public:
    Point(double x = 0.0, double y = 0.0){
        this->x_ = x;
        this->y_ = y;
    };
    virtual ~Point() {};
    double getX() const{
        return x_;
    };
    double getY() const{
        return y_;
    };
    void Print() const {
        std::cout << "点(" << x_ << ", " << y_ << ")" << std::endl;
    };
    std::pair<double, double> get() const{
        return std::make_pair(x_, y_);
    };
private:
    double x_;
    double y_;
};

#endif // POINT_H