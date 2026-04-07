#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

class Complex {
public:
    // 构造函数
    Complex(int real = 0, int imag = 0) : real_(real), imag_(imag) {}

    // 析构函数
    ~Complex() {}

    // +运算符重载
    Complex operator+(const Complex& other) const {
        return Complex(real_ + other.real_, imag_ + other.imag_);
    }

    // -运算符重载
    Complex operator-(const Complex& other) const {
        return Complex(real_ - other.real_, imag_ - other.imag_);
    }

    // 前置++运算符重载
    Complex& operator++() {
        ++real_;
        return *this;
    }

    // 后置++运算符重载
    Complex operator++(int) {
        Complex temp = *this;
        ++imag_;
        return temp;
    }

    // 前置--运算符重载
    Complex& operator--() {
        --real_;
        return *this;
    }

    // 后置--运算符重载
    Complex operator--(int) {
        Complex temp = *this;
        --imag_;
        return temp;
    }

    // <运算符重载
    bool operator<(const Complex& other) const {
        return sqrt(real_ * real_ + imag_ * imag_) < sqrt(other.real_ * other.real_ + other.imag_ * other.imag_);
    }
    
    // 以复数格式输出
    friend ostream& operator<<(ostream& out, const Complex& c) {
        out << c.real_ << "+" << c.imag_ << "i";
        return out;
    }

private:
    int real_, imag_;
};

int main() {
    vector<Complex> vec;

    // 示例复数
    vec.push_back(Complex(1, 2));
    vec.push_back(Complex(6, 4));
    vec.push_back(Complex(0, -6));
    vec.push_back(Complex(-3, 3));

    // 使用标准库sort函数排序
    sort(vec.begin(), vec.end());

    for (const auto& c : vec) {
        cout << c << endl;
    }

    return 0;
}
