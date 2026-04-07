#include <iostream>
#include <vector>
#include <thread>  // mac上用于运行sleep功能


using namespace std;

class Vehicle {
protected:
    double current_v;
    const double max_v;
    const double max_a;

public:
    Vehicle(double mv, double ma) : max_v(mv), max_a(ma), current_v(0) {}  // 构造函数
    virtual void Run() = 0;
    virtual void BeforeRun() = 0;
    virtual void AfterRun() = 0;

    virtual ~Vehicle() {}  // 析构函数
};

class ElectricMotor : public Vehicle {
private:
    double power;
    double distance;

public:
    ElectricMotor(double mv, double ma, double p) : Vehicle(mv, ma), power(p), distance(0) {}

    void BeforeRun() override {
        cout << "ElectricMotor is ready to start!" << endl;
        cout << endl;
    }

    void Run() override {
        if (current_v < max_v && power > 0) {
            current_v += max_a;
            cout << "ElectricMotor: Accelerate to " << current_v << " m/s" << endl;
            distance += current_v;  // 每次加速，更新行驶距离
            power -= 5;  // 每次加速消耗电量5%
            cout << "ElectricMotor: Current position: " << distance << " m " << endl;
            cout << endl;
        }
    }

    void AfterRun() override {
        cout << "ElectricMotor: Reach maximum speed or out of power" << endl;
        cout << "ElectricMotor: Total distance: " << distance << " m, Power: " << power << "%" << endl;
        cout << endl;
    }
};

class Bus : public Vehicle {
private:
    double fuel;
    double distance;

public:
    Bus(double mv, double ma, double f) : Vehicle(mv, ma), fuel(f), distance(0) {}

    void BeforeRun() override {
        cout << "Bus is ready to start!" << endl;
        cout << endl;
    }

    void Run() override {
        if (current_v < max_v && fuel > 0) {
            current_v += max_a;
            cout << "Bus: Accelerate to " << current_v << " m/s" << endl;
            fuel -= 2;  // 每次加速消耗燃料2L
            cout << endl;
        }
    }

    void AfterRun() override {
        cout << "Bus: Reach maximum speed or out of fuel" << endl;
        cout << "Fuel: " << fuel << "L" << endl;
        cout << endl;
    }
};

void FuncCallRun(vector<Vehicle*> vehs) {
    int sec = 0;
    for (int i = 0; i < vehs.size(); i++) {
        vehs[i]->BeforeRun();
    }
    while (sec < 10) {
        for (int i = 0; i < vehs.size(); i++) {
            vehs[i]->Run();
        }
    this_thread::sleep_for(std::chrono::seconds(1));   // 延迟1秒  
    sec++;
    }
    for (int i = 0; i < vehs.size(); i++) {
        vehs[i]->AfterRun();
    }
}

int main() {
    ElectricMotor em1(27, 3, 70); // 最大速度：27m/s  加速度：3m/s  剩余电量：70%
    ElectricMotor em2(32, 4, 60); // 最大速度：32m/s  加速度：4m/s  剩余电量：60%
    Bus bus1(20, 2, 100); // 最大速度：20m/s  加速度：2m/s  剩余电量：100L
    Bus bus2(25, 2.5, 90); // 最大速度：25m/s  加速度：2.5m/s  剩余电量：90L

    vector<Vehicle*> vehicles1;
    vehicles1.push_back(&em1);
    vehicles1.push_back(&bus1);

    vector<Vehicle*> vehicles2;
    vehicles2.push_back(&em2);
    vehicles2.push_back(&bus2);

    FuncCallRun(vehicles1);
    FuncCallRun(vehicles2);

    return 0;
}