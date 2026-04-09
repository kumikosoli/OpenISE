#include <iostream>
#include <cmath>
using namespace std;

class Vector {
private:
    double x;
    double y;
public:
    Vector(double _x, double _y) : x(_x), y(_y) {}

    static double getAngle(const Vector& v1, const Vector& v2) {
        double dotProduct = v1.x * v2.x + v1.y * v2.y;
        double v1Length = sqrt(v1.x * v1.x + v1.y * v1.y);
        double v2Length = sqrt(v2.x * v2.x + v2.y * v2.y);
        double cos = dotProduct / (v1Length * v2Length);  //两向量的点乘结果与其cos值的公式来反求cos:a点乘b=|a||b|cos<a,b>
        return acos(cos); //通过反函数求出夹角弧度制
    }

    friend class Point;
};

class Point {
private:
    double x;
    double y;
public:
    Point(double _x, double _y) : x(_x), y(_y) {}
    
    void print() const {
        cout << "(" << x << "," << y << ")" << endl;  //常函数输出向量
    }

    double getX() const {
        return x;
    }

    double getY() const {
        return y;
    }

    void getVectorAngle(const Point& p) const {
        Vector v1(x, y);
        Vector v2(p.x, p.y);
        double angle = Vector::getAngle(v1, v2);
        cout << "两向量夹角的弧度值为：" << angle << endl;
    }
};

int main() {
    Point p1(2.0, 3.0);
    Point p2(4.0, 5.0);
    p1.print();
    p2.print();
    p1.getVectorAngle(p2);
    
    Vector const x(1.0, 0.0);  //常对象定义x轴的单位向量
    
    Vector v(p1.getX(), p1.getY());
    double angle = Vector::getAngle(v, x);
    cout << "第一个向量与x轴夹角的余弦值为：" << cos(angle) << endl;

    return 0;
}