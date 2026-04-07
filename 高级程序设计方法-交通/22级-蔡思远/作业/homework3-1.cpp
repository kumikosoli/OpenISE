#include <iostream>
#include <cmath>
using namespace std;

class Point {
private:
    double x;
    double y;
    static int number;

public:
    Point(double _x, double _y) : x(_x), y(_y) {
        number++;
    }

    ~Point() {
        number--;
    }

    static void print() {
        cout << "总共存在的点的数量为" << number << endl;
    }

    friend double dis(const Point& point1, const Point& point2);
};

int Point::number = 0;

double dis(const Point& point1, const Point& point2) {
    double dx = point2.x - point1.x;
    double dy = point2.y - point1.y;
    return sqrt(dx * dx + dy * dy);  //勾股定理
}

int main() {
    Point point1(4.7, 3.0);
    Point point2(3.1, 5.9);
    Point point3(9.1, 3.5);

    Point::print();

    double dist13 = dis(point1, point3);
    cout << "point1与point3之间的距离为：" << dist13 << endl;
    double dist23 = dis(point2, point3);
    cout << "point2与point3之间的距离为：" << dist23 << endl;
    double dist12 = dis(point1, point2);
    cout << "point1与point2之间的距离为：" << dist12 << endl;

    return 0;
}