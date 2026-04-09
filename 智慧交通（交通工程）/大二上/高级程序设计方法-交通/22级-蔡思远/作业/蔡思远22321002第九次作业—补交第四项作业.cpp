#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Vehicle {
protected:
    string number; // 车牌号
    int label;    // 车的类型(大中小), 收费不一样

public:
    Vehicle(){}
    Vehicle(string number_, int label_){
        number = number_;
        label = label_;
    }
// 通过公共的访问函数来访问label成员变量
    int getLabel() const {
        return label;
    }
};
// 派生类：大车
class Bigvehicle: public Vehicle {
public:
    Bigvehicle(): Vehicle(){}
    Bigvehicle(string number_): Vehicle(number_, 0){} 
};
// 派生类：中车
class Middlevehicle: public Vehicle {
public:
    Middlevehicle(): Vehicle(){}
    Middlevehicle(string number_): Vehicle(number_, 1){}
};
// 派生类：小车
class Smallvehicle: public Vehicle {
public:
    Smallvehicle(): Vehicle(){}
    Smallvehicle(string number_): Vehicle(number_, 2){}
};

class ParkingLot {
private:
    vector<Vehicle*> vehPool_;   // 保存车辆的数组
    static const int max_small = 1;  // 小型车数量上限
    static const int max_mid = 1;  // 中型车数量上限
    static const int max_big = 1;  // 大型车数量上限
    int small;
    int mid;
    int big; 
public:
    ParkingLot() : small(0), mid(0), big(0) {
    }

    bool hasPosition(int label) {
        if (label == 0) {
            if (big >= max_big) {
                cout << "大型车已没有位置" << endl;
                return false;
            }
            return true;
        } else if (label == 1) {
            if (mid >= max_mid) {
                cout << "中型车已没有位置" << endl;
                return false;
            }
            return true;
        } else if (label == 2) {
            if (small >= max_small) {
                cout << "小型车已没有位置" << endl;
                return false;
            }
            return true;
        } else {
            return false;
        }
    }

    void VehicleIn(Vehicle* veh) {
        if (hasPosition(veh->getLabel())) {
            if (vehPool_.size() < max_small + max_mid + max_big) {
                vehPool_.push_back(veh);
                if (veh->getLabel() == 0) {
                    big++;
                } else if (veh->getLabel() == 1) {
                    mid++;
                } else if (veh->getLabel() == 2) {
                    small++;
                }
            }
        }
    }
};

int main() {
    ParkingLot parkingLot;
    Vehicle* Benz = new Bigvehicle("粤A00001");
    Vehicle* BMW = new Middlevehicle("浙B00002");
    Vehicle* Audi = new Smallvehicle("沪C00003");
    Vehicle* Tesla = new Middlevehicle("赣D00004");
    // 将以下四辆车停入停车场，若停车场容量不够则输出相应内容
    parkingLot.VehicleIn(Benz);
    parkingLot.VehicleIn(BMW);
    parkingLot.VehicleIn(Audi);
    parkingLot.VehicleIn(Tesla);

    return 0;
}