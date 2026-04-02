#include<iostream>
#include<iomanip>
#include<cassert>
using namespace std;

class Vihicle
{
	private:
		double max_speed, weight, kilo;
	public:
		Vihicle():max_speed(50.0), weight(2000.0),kilo(0.0) {}
		Vihicle(double x, double y):max_speed(x), weight(y),kilo(0.0) {}
		~Vihicle() {}
		void run(double i)
		{
			cout.setf(ios::fixed); //repalce 'cout.precision(2); cout<<...<<endl;'
			cout<<"run for "<<setprecision(2)<<i<<" kilos"<<endl;
			kilo += i;
		}
		void stop() {cout<<setiosflags(ios::fixed)<<"stop at "<<setprecision(2)<<kilo<<" kilos"<<endl;}
		
};

class Bicycle:virtual public Vihicle
{
	private:
		double height;
	public:
		Bicycle():height(1.5),Vihicle(25.0, 20.0) {}
		Bicycle(double x):height(x),Vihicle(25.0, 20.0) {}
		Bicycle(double x, double y, double z):height(x),Vihicle(y, z) {}
		~Bicycle() {}
};

class Automobile:virtual public Vihicle
{
	private:
		int seat_count;
	public:
		Automobile():seat_count(5),Vihicle(180.0, 3000.0) {}
		Automobile(int x):seat_count(x),Vihicle(180.0, 3000.0) {}
		Automobile(int x, double y, double z):seat_count(x),Vihicle(y, z) {}
		~Automobile() {}
};

class Motorcycle:public Bicycle, public Automobile
{
	public:
		Motorcycle():Bicycle(), Automobile() {} 
		~Motorcycle() {}
};

int main()
{
	Motorcycle m1;
	m1.run(111.0);
	m1.stop();
	return 0;
}
