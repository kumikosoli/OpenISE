#include<iostream>
#include<cmath>
using namespace std;

class Complex
{
	private:
		double real,imag,magni;
		static int count;
	public:
		Complex(double x,double y);
		Complex(double x);
		Complex();
		Complex(const Complex &p);
		~Complex();
		static void show_count();
		void show();
		void add(const Complex &p);
		friend Complex multiply(const Complex &p,const Complex &q);
};

int Complex::count=0;

Complex::Complex(double x,double y):real(x),imag(y)
{
	magni=sqrt(real*real+imag*imag);
	count++;
}

Complex::Complex(double x):real(x),imag(0.0)
{
	magni=sqrt(real*real+imag*imag);
	count++;
}

Complex::Complex():real(0.0),imag(0.0)
{
	magni=sqrt(real*real+imag*imag);
	count++;
}

Complex::Complex(const Complex &p):real(p.real),imag(p.imag)
{
	magni=sqrt(real*real+imag*imag);
	count++;
}

void Complex::show_count()
{
	cout<<"conut: "<<count<<endl;
}

void Complex::show()
{
	cout<<real<<" + "<<imag<<"i"<<endl;
}

void Complex::add(const Complex &p)
{
	real+=p.real;
	imag+=p.imag;
}

Complex multiply(const Complex &p,const Complex &q)
{
	Complex a;
	a.real=p.real*q.real-p.imag*q.imag;
	a.imag=p.imag*q.real+p.real*q.imag;
	return a;
}

Complex::~Complex()
{
}

int main()
{
	Complex c1,c2(1,1),c3(1);
	Complex c4=1,c5=c2;
	c5.add(c2);
	c5.show();
	Complex::show_count();
	Complex c6=multiply(c1,c2);
	cout<<"show all now:"<<endl;
	c1.show();
	c2.show();
	c3.show();
	c4.show();
	c5.show();
	c6.show();
	return 0;
}
