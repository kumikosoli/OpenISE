#include <iostream>
using namespace std;

// 虚基类Vehicle
class Vehicle {
public:
    Vehicle(int maxSpeed, int weight) : maxSpeed(maxSpeed), weight(weight) {}
    virtual ~Vehicle() {}
    virtual void run() = 0;
    virtual void stop() = 0;

protected:
    int maxSpeed;
    int weight;
};

// 派生类Bicycle
class Bicycle : virtual public Vehicle {
public:
    Bicycle(int maxSpeed, int weight, int height) : Vehicle(maxSpeed, weight), height(height) {}
    void run() {
        cout << "Bicycle run" << endl;
    }
    void stop() {
        cout << "Bicycle stop" << endl;
    }
protected:
    int height;
};

class Automobile : virtual public Vehicle {
public:
    Automobile(int maxSpeed, int weight, int seatCount) : Vehicle(maxSpeed, weight), seatCount(seatCount) {}
    void run() {
        cout << "Automobile run" << endl;
    }
    void stop() {
        cout << "Automobile stop" << endl;
    }
protected:
    int seatCount;
};

// 派生类Motorcycle
class Motorcycle : public Bicycle, public Automobile {
public:
	// 构造函数
    Motorcycle(int maxSpeed, int weight, int height, int seatCount) : Vehicle(maxSpeed, weight), Bicycle(maxSpeed, weight, height), Automobile(maxSpeed, weight, seatCount) {}
    // 复制构造函数
    Motorcycle(const Motorcycle &m) : Vehicle(m.maxSpeed, m.weight), Bicycle(m.maxSpeed, m.weight, m.height), Automobile(m.maxSpeed, m.weight, m.seatCount) {}
    // 析构函数
    ~Motorcycle() {
        cout << "Motorcycle disappear" << endl;
    }
    void run() {
        cout << "Motorcycle run" << endl;
	}
    void stop() {
        cout << "Motorcycle stop" << endl;
    }
};

int main(){
    Motorcycle motorcycle1(200,500,4,2);
    motorcycle1.run();
    motorcycle1.stop();
    Motorcycle motorcycle2 = motorcycle1;
    motorcycle2.run();
    motorcycle2.stop();
    return 0;
}