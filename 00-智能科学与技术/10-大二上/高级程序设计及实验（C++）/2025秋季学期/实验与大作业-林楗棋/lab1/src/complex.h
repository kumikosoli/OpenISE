#include <utility>
#ifndef COMPLEX_H
#define COMPLEX_H

class Complex {
    float real, imag;
    float abs;
    static int count;
public:
    Complex(float r, float i);
    Complex(float r);
    Complex(Complex& copy);
    ~Complex();
    void add(Complex& other);
    float getAbs();
    std::pair<float, float> show();
    friend std::pair<float, float> mul(Complex& a, Complex& b);
    friend std::pair<float, float> div(Complex& a, Complex& b);
    static int getCount() { return count; }
};
#endif
