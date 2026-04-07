#include <iostream>
#include <vector>
using namespace std;


template<class T>
void my_swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

int main() {
    // int类型
    int int_a = 5, int_b = 10;
    cout << "int_a:" << int_a << ", int_b:" << int_b << endl;
    my_swap(int_a, int_b);
    cout << "int_a:" << int_a << ", int_b:" << int_b << endl;
    cout << endl;

    // double类型
    double double_a = 3.64, double_b = 8.18;
    cout << "double_a:" << double_a << ", double_b:" << double_b << endl;
    my_swap(double_a, double_b);
    cout << "double_a:" << double_a << ", double_b:" << double_b << endl;
    cout << endl;

    // vector<int>类型
    vector<int> vec_a;
    vec_a.push_back(1);
    vec_a.push_back(2);
    vec_a.push_back(3);
    vector<int> vec_b;
    vec_b.push_back(4);
    vec_b.push_back(5);
    vec_b.push_back(6);

    cout << "vec_a:";
    for (int i : vec_a) cout << i << " ";
    cout << ", vec_b:";
    for (int i : vec_b) cout << i << " ";
    cout << endl;
    my_swap(vec_a, vec_b);
    cout << "vec_a:";
    for (int i : vec_a) cout << i << " ";
    cout << ", vec_b:";
    for (int i : vec_b) cout << i << " ";
    cout << endl;

    return 0;
}
