#include <cmath>
#include <iostream>
#include <memory>
#include <string>

class Shape {
public:
    virtual ~Shape() = default;
    virtual double area() const = 0;
    virtual double volume() const = 0;
    virtual std::string name() const = 0;
};

class Cubic : public Shape {
public:
    Cubic(double side_length) : a_(side_length) {}
    ~Cubic() = default;

    double area() const override { return 6.0 * a_ * a_; }
    double volume() const override { return a_ * a_ * a_; }
    std::string name() const override { return "正方体Cubic"; }

private:
    double a_; 
};

class Sphere : public Shape {
public:
    Sphere(double radius) : r_(radius) {}
    ~Sphere() = default;

    double area() const override { return 4.0 * M_PI * r_ * r_; }
    double volume() const override { return (4.0 / 3.0) * M_PI * r_ * r_ * r_; }
    std::string name() const override { return "球体Sphere"; }

private:
    double r_;
};

class Cylinder : public Shape {
public:
    Cylinder(double radius, double height) : r_(radius), h_(height) {}
    ~Cylinder() = default;

    double area() const override { return 2.0 * M_PI * r_ * (r_ + h_); }
    double volume() const override { return M_PI * r_ * r_ * h_; }
    std::string name() const override { return "圆柱体Cylinder"; }

private:
    double r_;
    double h_;
};

int main() {
    std::unique_ptr<Shape> shapes[3];
    shapes[0] = std::make_unique<Cubic>(3.0);
    shapes[1] = std::make_unique<Sphere>(2.5);
    shapes[2] = std::make_unique<Cylinder>(2.0, 5.0);

    for (int i = 0; i < 3; ++i) {
        std::cout << shapes[i]->name() << " - "
                  << "面积: " << shapes[i]->area()
                  << ", 体积: " << shapes[i]->volume() << '\n';
    }

    return 0;
}
