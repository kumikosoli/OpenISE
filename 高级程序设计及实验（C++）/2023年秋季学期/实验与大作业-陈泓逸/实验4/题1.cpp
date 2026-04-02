#include<iostream>
#include<cassert>
using namespace std;

class Animal
{
	public:
		int age;
	public:
		Animal():age(0) {}
		Animal(int a):age(a) {}
		Animal(const Animal& a):age(a.get_age()) {}
		~Animal() {}
		int get_age() const {return age;}
		void print_age() const {cout<<"age: "<<age<<endl;}
};

class Dog:public Animal
{
	public:
		Dog() {}
		Dog(int b):Animal(b) {}
		~Dog() {}
		void set_age(int a) {age = a;}
};

int main()
{
	Dog d1(3);
	d1.set_age(5);
	d1.print_age();
	return 0;
}
