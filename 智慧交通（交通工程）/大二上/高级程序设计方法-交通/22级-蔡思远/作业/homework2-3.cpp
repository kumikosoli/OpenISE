#include<iostream>
using namespace std;
class Rectangle {
private:
    int length;
    int width;

public:
    Rectangle(int l, int w) : length(l), width(w) {}
    
    int Area() {
        return length * width;
    }
};

int main() {
    Rectangle data(3, 8);
    cout << "矩形的面积大小是 : " << data.Area() << endl;
    return 0;
}