#include <iostream>
#include <cmath>
#include <string>
using namespace std;

class Complex{
private:
    double real;  //实部
    double imag;  //虚部
    double mod; //模
    static int count;  //静态成员变量，用于记录复数的个数

public:
    //初始化构造函数
    Complex() : real(0), imag(0), mod(0) { count++; }
    Complex(double r, double i) : real(r), imag(i), mod(sqrt(r*r + i*i)) { count++; }
    Complex(double r) : real(r), imag(0), mod(abs(r)) { count++; }

    //复制构造函数
    Complex(const Complex &c) : real(c.real), imag(c.imag), mod(c.mod) { count++; }

    //实现“e.g.将结果存在c1”
    void add(const Complex &c) {
        real += c.real;
        imag += c.imag;
        mod = sqrt(real*real + imag*imag);   //复数模计算公式
    }
    
    //显示静态数据成员函数
    void show() const {
        cout << real << " + " << imag << "i" << endl;
    }

    //静态成员函数，记录复数的个数
    static void showCount() {
        cout << "复数的个数为：" << count << endl;
    }

    //友元函数
    friend Complex mul(const Complex &c1, const Complex &c2);
};

//初始化静态成员变量count
int Complex::count = 0;

//使用友元函数就算两个复数相乘结果
Complex mul(const Complex &c1, const Complex &c2) {
    double r = c1.real*c2.real - c1.imag*c2.imag;
    double i = c1.real*c2.imag + c1.imag*c2.real;
    return Complex(r,i);
}

int main() {
    Complex C1;   //初始化
    Complex C2(1,1); 
    Complex C3(1); 
    Complex C = C3;  //复制构造
    C1.add(C2);  //结果存在C1中
    C1.show();  //显示C1
    Complex::showCount();  //复数个数
    cout << "c1(1+i)与c2(1+i)相乘的结果为：" ;
    Complex C4 = mul(C1, C2);   //计算两个复数相乘
    C4.show();
    return 0;
}