#include "complex.h"
#include <cmath>

int Complex::count = 0;

Complex::Complex(float r, float i) {
    real = r;
    imag = i;
    abs = sqrt(r * r + i * i);
    Complex::count++;
} 

float Complex::getAbs() { return abs; }

Complex::Complex(float r) {
    real = r;
    imag = 0; // 赋值为0防止未初始化
    abs = fabs(r);
    Complex::count++;
}

Complex::Complex(Complex& copy) {
    auto [r, i] = copy.show();
    real = r;
    imag = i;
    abs = copy.abs;
    Complex::count++;
}

void Complex::add(Complex& other) {
    auto [r, i] = other.show();
    real += r;
    imag += i;
    abs = sqrt(real * real + imag * imag);
}

std::pair<float, float> Complex::show() {
    std::pair<float, float> ret{real, imag};
    return ret;
}

std::pair<float, float> mul(Complex& a, Complex& b) {
    auto [c, d] = b.show();
    auto [x, y] = a.show();
    return std::pair<float, float> {x * c - y * d, y * c + x * d};
}

std::pair<float, float> div(Complex& a, Complex& b) {
    auto [c, d] = b.show();
    auto [x, y] = a.show();
    float deno = c * c + d * d;
    return std::pair<float, float> {(x * c + y * d) / deno, (y * c - x * d) / deno};
}

Complex::~Complex() {
    Complex::count--;
}
