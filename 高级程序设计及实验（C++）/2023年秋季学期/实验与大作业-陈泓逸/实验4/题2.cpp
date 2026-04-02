#include<iostream>
#include<cassert>
#include<iomanip>
using namespace std;

class Shape
{
	private:
		double area;
	public:
		Shape():area(100.0) {}
		Shape(double a):area(a) {}
		~Shape() {}
};

class Rectangle:public Shape
{
	private:
		double length, width;
	public:
		double get_area() {return length * width;}
		Rectangle():length(1.5), width(4.5), Shape(55.5) {}
		~Rectangle() {}
};

class Circle:public Shape
{
	private:
		double radius;
	public:
		double get_area() {return 3.14 * radius * radius;}
		Circle():radius(10.0), Shape(66.6) {}
		~Circle() {}
};

class Square:public Rectangle
{
	private:
		double length_;
	public:
		double get_area(int a)
		{
			if(a) return length_ * length_;
			else Rectangle::get_area();
		}
		Square():length_(2.5), Rectangle() {}
		~Square() {}
};

int main()
{
	Rectangle r1;
	Circle c1;
	Square s1;
	cout<<setprecision(3)<<r1.get_area()<<endl;
	cout<<setprecision(3)<<c1.get_area()<<endl;
	cout<<setprecision(3)<<s1.get_area(1)<<" "<<s1.get_area(0)<<endl;
	return 0;
}
