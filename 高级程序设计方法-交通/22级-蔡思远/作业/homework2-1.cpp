#include <iostream>
using namespace std;
class Rectangle{
private:
    struct Point {
        int a;
        int b;
    };

    Point bottomLeft;
    Point topRight;
public:
    Rectangle(int a1, int b1, int a2, int b2)  {
        bottomLeft.a = a1;
        bottomLeft.b = b1;
        topRight.a = a2;
        topRight.b = b2;
    }
    int result(){
        int w = topRight.a - bottomLeft.a;
        int h = topRight.b - bottomLeft.b;
        return w * h;
}
};
int main() {
    Rectangle data(2, 1, 5, 3);
    int area = data.result();
    cout << "矩形的面积为：" << area << endl;

    return 0;
}