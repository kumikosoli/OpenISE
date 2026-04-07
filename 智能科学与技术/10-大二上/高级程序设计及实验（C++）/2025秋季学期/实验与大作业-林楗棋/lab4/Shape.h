#ifndef SHAPE_H
#define SHAPE_H
class Shape {
public:
    virtual ~Shape() = default;
    virtual double Circumference() const = 0;
    virtual double Area() const = 0;
    virtual void Print() const = 0;
    static const int UnknownValue = -1;
};

#endif // SHAPE_H
