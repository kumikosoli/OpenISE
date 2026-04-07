#include<iostream>
#include<vector>
using namespace std;
//传感器基类
class Sensor{
protected:
    int frequency;// 传感器频率(frequency秒/次)
    int counter;  // 计数器，用于实现每frequency次进行一次更新和发送
public:
    Sensor(int freq):frequency(freq),counter(0){} // 构造函数，初始化频率和计数器
    // 更新传感器数据
    virtual void updateData()=0;
    // 发送传感器数据
    virtual void sendData()=0;
};

// Radar类，继承自Sensor
class Radar:public Sensor{
public:
    vector<int> data;
    Radar(int freq):Sensor(freq){}
    void updateData()override{
        if(++counter%frequency==0){   // 每frequency次进行一次更新
            //这里省略了更新数据的具体操作，可以根据实际需要添加
            cout<<"Radar data updated."<<endl;  //提示信息，表示数据已更新
        }
    }
    void sendData()override{  //重写基类的sendData函数
        if(counter%frequency==0){//每frequency次进行一次发送
            //这里省略了发送数据的具体操作，可以根据实际需要添加
            cout<<"Radar data sent."<<endl;  //提示信息，表示数据已发送
        }
    }
};

//惯性测量单元类，继承自Sensor
class Imu:public Sensor{
public:
    int x,y,z;  //IMU数据，假设为三维坐标
    Imu(int freq):Sensor(freq),x(0),y(0),z(0){} //构造函数，调用基类的构造函数初始化频率和计数器，并初始化数据为0
    void updateData()override{  //重写基类的updateData函数
        if(++counter%frequency==0){//每frequency次进行一次更新
            //这里省略了更新数据的具体操作，可以根据实际需要添加
            cout<<"IMU data updated."<<endl;  //提示信息，表示数据已更新
        }
    }
    void sendData()override{  //重写基类的sendData函数
        if(counter%frequency==0){//每frequency次进行一次发送
            //这里省略了发送数据的具体操作，可以根据实际需要添加
            cout<<"IMU data sent."<<endl;  //提示信息，表示数据已发送
        }
    }
};

//无人机类
class Drone{
public:
    vector<Sensor*> sensors;  //无人机的传感器，可以是任意类型的传感器，包括Radar和Imu
    void Fly(){  //无人机飞行函数
        for(auto sensor:sensors){  //遍历所有传感器
            sensor->updateData();  //更新传感器数据
            sensor->sendData();  //发送传感器数据
        }
    }
};

int main(){
    Drone drone;  //创建一个无人机
    drone.sensors.push_back(new Radar(1));  //给无人机添加一个频率为1的雷达
    drone.sensors.push_back(new Imu(2));  //给无人机添加一个频率为2的IMU
    for(int i=0;i<10;i++){  //模拟无人机飞行10秒
        drone.Fly();  //无人机飞行，更新并发送所有传感器的数据
    }
    return 0;
}