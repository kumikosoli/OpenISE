#include<iostream>
#include<vector>
using namespace std;

class Sensor{
protected:
    int frequency;
    int counter;
public:
    Sensor(int freq):frequency(freq),counter(0){}
    // 更新传感器数据
    virtual void updateData() = 0;
    // 发送传感器数据（每次更新后都要发送）
    virtual void sendData() = 0;
};

// Radar类，继承自Sensor类
class Radar:public Sensor{
public:
    vector<int> data;

    Radar(int freq) : Sensor(freq), data(10) {
        // 初始化雷达数据为1到10
        for(int i = 0; i < 10; ++i){
            data[i] = i+1;  
        }
    }
    
    // 更新雷达数据
    void updateData() override {
        if (++counter % frequency == 0) {
            cout << "Radar data updated." << endl;
        }
    }
    
    // 发送雷达数据
    void sendData() override{
        if(counter % frequency == 0){
            cout << "Radar data sent: ";
            for(const auto& d : data){
                cout << d << ' ';
            }
            cout << endl;
        }
    }
};

// IMU类，继承自Sensor类
class Imu:public Sensor{
public:
    int x, y, z;
    Imu(int freq):Sensor(freq),x(0),y(0),z(0){}
    void updateData() override{
        if(++counter % frequency == 0){
            // 初始化IMU数据为1,2,3
            x = 1, y = 2, z = 3;
            cout << "IMU data updated." << endl;
        }
    }
    // 发送IMU数据
    void sendData() override{
        if(counter % frequency == 0){
            cout << "IMU data sent: " << x << ' ' << y << ' ' << z << endl;
        }
    }
};

// 无人机类
class Drone{
public:
    vector<Sensor*> sensors;
    // 无人机飞行函数，更新和发送所有传感器的数据
    void Fly(){
        for(auto sensor : sensors){
            sensor->updateData();
            sensor->sendData();
        }
    }
};

int main(){
    Drone drone;
    drone.sensors.push_back(new Radar(1));// 1代表Radar对象的更新频率。频率为1意味着每次调用Fly()方法时，Radar对象都会更新和发送数据。下面Imu对象同。
    drone.sensors.push_back(new Imu(1));
    // 无人机飞行10次，每次飞行都会更新和发送所有传感器的数据
    for(int i = 0;i < 10; i++){
        drone.Fly();
    }
    return 0;
}