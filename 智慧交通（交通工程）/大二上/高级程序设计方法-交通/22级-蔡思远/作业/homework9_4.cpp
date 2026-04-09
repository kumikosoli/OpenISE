#include<iostream>
using namespace std;

class Pet {
    public:
        virtual void eat() {
            cout << "吧唧吧唧" << endl;
        }
};

class Cat : public Pet {
    public:
        void eat() {
            cout << "猫：吧唧吧唧" << endl;
        }
};

class Dog : public Pet {
    public:
        void eat() {
            cout << "狗：吧唧吧唧" << endl;
        }
};

class Bird : public Pet {
    public:
        void eat() {
            cout << "鸟：吧唧吧唧" << endl;
        }
};

int main() {
    Pet* a = new Cat();
    Pet* b = new Dog();
    Bird c;
    Pet& p = c;

    a->eat();
    b->eat();
    p.eat();

    delete a;
    delete b;

    return 0;
}