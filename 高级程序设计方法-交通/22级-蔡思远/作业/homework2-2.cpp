#include <iostream>
using namespace std;
class Date {
private:
    int day;
    int month;
    int year;
public:
    Date(int d, int m, int y) : day(d), month(m), year(y) {}
    void display() {
        cout << day << "/" << month << "/" << year << endl;
    }
};

class Person {
private:
    int id;
    string gender;
    Date dob;
    string idCard;
public:
    Person(int i, string g, Date d, string id) : id(i), gender(g), dob(d), idCard(id) {}
    Person(const Person& p) : id(p.id), gender(p.gender), dob(p.dob), idCard(p.idCard) {}
    ~Person() {
        cout << "data destroyed" << endl;
    }
    void display() {
        cout << "ID: " << id << endl;
        cout << "Gender: " << gender << endl;
        cout << "Date of Birth: ";
        dob.display();
        cout << "ID Card: " << idCard << endl;
    }
};

int main() {
    Date dob(26, 9, 2023);
    Person person1(22321002, "Male", dob, "440105202309260017");
    Person person2 = person1; 

    cout << "Person 1:" << endl;
    person1.display();

    cout << "Person 2 :" << endl;
    person2.display();

    return 0;
}