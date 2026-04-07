#include<iostream>
using namespace std;

// 学生类Student
class Student {
public:
    // 姓名、学号、校名
    string name;
    string number;
    string school;

    // 构造函数
    Student(string n, string num, string sc) {
        name = n;
        number = num;
        school = sc;
}

    // print()函数
    void print() {
        cout << "姓名：" << name << endl;
        cout << "学号：" << number << endl;
        cout << "校名：" << school << endl;
}
};

// 研究生类GraduateStudent
class GraduateStudent : public Student {
public:
    // 研究方向、导师名等成员
    string researchDirection;
    string tutorName;

    // 构造函数
    GraduateStudent(string n, string num, string sc, string rd, string tn) : Student(n, num, sc) {
        researchDirection = rd;
        tutorName = tn;
}

    // print()函数
    void print() {
        Student::print();
        cout << "研究方向：" << researchDirection << endl;
        cout << "导师名：" << tutorName << endl; 
}
};


int main() {
    // 基类对象
    Student stu("Caisy", "22321002", "Sun Yat-sen University");
    stu.print();
    cout << endl;
    // 派生类对象
    GraduateStudent graStu("Linj", "22351002", "South China University of Technology", "Pattern Recognization", "Jianggg");
    graStu.print();

    return 0;
}