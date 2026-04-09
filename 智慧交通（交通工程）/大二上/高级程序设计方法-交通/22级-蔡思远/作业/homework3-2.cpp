#include<iostream>
#include<cmath>
using namespace std;

class Point{
private:
    double x;
    double y;
    static int number;
public:
    Point(double _x, double _y) : x(_x), y(_y){
        number++;
    }
    ~Point(){
        number--;
    }
    static void print(){
        cout << "总共存在的点的数量为：" << number << endl;
    }
    friend double dis(const Point& point1, const Point& point2);
};

int Point::number = 0;

double dis(const Point& point1, const Point& point2){
    double dx = point2.x - point1.x;
    double dy = point2.y - point1.y;
    return sqrt(dx * dx + dy * dy);
}

class Triangle{
private:
    Point A;
    Point B;
    Point C;
public:
    Triangle(const Point& _A, const Point& _B, const Point& _C) : A(_A), B(_B), C(_C){}
    static double getLenth(const Triangle& triangle){
        double AB = dis(triangle.A, triangle.B);
        double BC = dis(triangle.B, triangle.C);
        double AC = dis(triangle.A, triangle.C);
        return AB + BC + AC;
    }
    static double getArea(const Triangle& triangle){
        double AB = dis(triangle.A, triangle.B);
        double BC = dis(triangle.B, triangle.C);
        double AC = dis(triangle.A, triangle.C);
        double p = (AB + BC + AC) / 2;
        return sqrt(p*(p - AB)*(p - BC)*(p - AC));   //这里用了海伦公式，S=√p(p-a)(p-b)(p-c)，p为周长的一半
    }
    static bool inTriangle(const Triangle& triangle, const Point& point){
        double areaABC = getArea(triangle);
        double areaPAB = getArea(Triangle(point, triangle.A, triangle.B));
        double areaPAC = getArea(Triangle(point, triangle.A, triangle.C));
        double areaPBC = getArea(Triangle(point, triangle.B, triangle.C));
        return areaABC == (areaPAB + areaPAC + areaPBC);   //店内一点分别与三角形其中两点所围成的三个三角形的面积之和等于大三角形面积，则该点在三角形内
    }
};

int main(){
    Point A(2,4);
    Point B(4,7);
    Point C(8,2);
    cout << "A(2,4)" << endl;
    cout << "B(4,7)" << endl;
    cout << "A(8,2)" << endl;
    Triangle triangle(A, B, C);
    cout << "三角形ABC的周长为：" << Triangle::getLenth(triangle) << endl;
    cout << "三角形ABC的面积为：" << Triangle::getArea(triangle) << endl;
    Point M(5, 6);
    cout << "M(5,6)\n";
    if (Triangle::inTriangle(triangle, M)){
        cout << "点M在三角形ABC内" << endl;
    }
    else{
        cout << "点M在三角形ABC外" << endl;
    }
    return 0;
}