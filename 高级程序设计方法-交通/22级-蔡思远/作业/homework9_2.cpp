#include <iostream>
using namespace std;

class Shape{
public:
    Shape():area(0.0){}
    virtual ~Shape(){}
    virtual double GetArea() = 0;
protected:
    double area;
};

//派生类Rectangle
class Rectangle : public Shape{
public:
    Rectangle(double l, double w):length(l), width(w){}
    double GetArea() {
        area = length * width;
        return area;
    }
protected:
    double length;
    double width;
};

//派生类Circle
class Circle : public Shape{
public:
    Circle(double r):radius(r){}
    double GetArea() {
        area = 3.14159265 * radius * radius;
        return area;
    }
private:
    double radius;
};

//派生类Square
class Square : public Rectangle{
public:
    Square(double s):Rectangle(s,s){}
    double GetArea() {
        area = length * width;
        return area;
    }
};

int main(){
    Rectangle rect(2.0, 6.0);
    Circle cir(5.0);
    Square sq(4.0);
    cout << "长方形长和宽分别为6和2" << endl;
    cout << "圆形半径为5" << endl;
    cout << "正方形边长为4" << endl;
    cout << endl;
    cout << "长方形面积为：" << rect.GetArea() << endl;
    cout << "圆形面积为：" << cir.GetArea() << endl;
    cout << "正方形面积为：" << sq.GetArea() << endl;

    return 0;
}