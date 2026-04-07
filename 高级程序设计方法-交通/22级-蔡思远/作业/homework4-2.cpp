#include <iostream>
using namespace std;

class Person {
private:
    int id;
    int height;
public:
    Person() : id(0), height(0) {}   //添加默认构造函数
    
    Person(int id, int height) : id(id), height(height) {}   //构造函数

    int getId() const {return id;}

    int getHeight() const {return height;}
};

class PersonArray {   //设计PersonArray类
private:
    Person* arr;
    int size;
public:
    PersonArray(int size) : size(size) {
        arr = new Person[size]();   //调用默认构造函数初始化数组
    }

    void setPerson(int index, const Person& person) {
        arr[index] = person;
    }

    ~PersonArray() {   //析构函数
        delete[] arr;
    }

    int get_id_height(int id) const {   //设计通过ID查找身高的函数
        for (int i = 0; i < size; ++i) {
            if (arr[i].getId() == id) {
                return arr[i].getHeight();
            }
        }
    }
};

int main() {
    PersonArray personArray(4);   //创建PersonArray对象和Person数组
    Person person1(1, 172);
    Person person2(2, 183);
    Person person3(3, 179);
    Person person4(4, 191);

    personArray.setPerson(0, person1); 
    personArray.setPerson(1, person2);
    personArray.setPerson(2, person3);
    personArray.setPerson(3, person4);

    int id;   //// 输入id，输出对应的成员身高
    cout << "请输入id：" << endl;
    cin >> id;
    int height = personArray.get_id_height(id);
    cout << "身高为：" << height << "cm" << endl;
    return 0;
}