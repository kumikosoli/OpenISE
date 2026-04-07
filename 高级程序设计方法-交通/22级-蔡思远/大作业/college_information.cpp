#include <iostream>
#include <vector>
#include <string>
using namespace std;

// 基类：高校人员
class CollegePerson {
public:
    CollegePerson(int id, string name, char gender, int age)
        : id(id), name(name), gender(gender), age(age) {}

    // 虚函数，用于在派生类中实现不同的显示信息方法
    virtual void display() const {
        cout << "编号: " << id << ", 姓名: " << name << ", 性别: " << gender << ", 年龄: " << age;
    }

    int getId() const { return id; }
    const string& getName() const { return name; } // 添加获取姓名的成员函数
    char getGender() const { return gender; } // 添加获取性别的成员函数

    // 添加虚函数以供编辑信息
    virtual void editInfo() {
        // 在派生类中实现编辑信息的具体逻辑
    }

private:
    int id;
    string name;
    char gender;
    int age;
};

// 派生类：教师
class Teacher : public CollegePerson {
public:
    Teacher(int id, string name, char gender, int age, string department, string major, string title)
        : CollegePerson(id, name, gender, age), department(department), major(major), title(title) {}

    // 覆盖基类的虚函数以实现特定的显示信息方法
    void display() const override {
        CollegePerson::display();
        cout << ", 系部: " << department << ", 专业: " << major << ", 职称: " << title << endl;
    }

    // 实现编辑信息的虚函数
    void editInfo() override {
        // 在这里实现编辑教师信息的具体逻辑
    }

private:
    string department;
    string major;
    string title;
};

// 派生类：实验员
class LabAssistant : public CollegePerson {
public:
    LabAssistant(int id, string name, char gender, int age, string lab, string position)
        : CollegePerson(id, name, gender, age), lab(lab), position(position) {}

    // 覆盖基类的虚函数以实现特定的显示信息方法
    void display() const override {
        CollegePerson::display();
        cout << ", 实验室: " << lab << ", 职务: " << position << endl;
    }

    // 实现编辑信息的虚函数
    void editInfo() override {
        // 在这里实现编辑实验员信息的具体逻辑
    }

private:
    string lab;
    string position;
};

// 派生类：行政人员
class Administrator : public CollegePerson {
public:
    Administrator(int id, string name, char gender, int age, string politicalAffiliation, string jobTitle)
        : CollegePerson(id, name, gender, age), politicalAffiliation(politicalAffiliation), jobTitle(jobTitle) {}

    // 覆盖基类的虚函数以实现特定的显示信息方法
    void display() const override {
        CollegePerson::display();
        cout << ", 政治面貌: " << politicalAffiliation << ", 职称: " << jobTitle << endl;
    }

    // 实现编辑信息的虚函数
    void editInfo() override {
        // 在这里实现编辑行政人员信息的具体逻辑
    }

private:
    string politicalAffiliation;
    string jobTitle;
};

// 静态变量，用于生成唯一的编号
static int nextId = 1;

// 存储所有人员记录的容器
vector<CollegePerson*> collegePeople;

// 添加高校人员记录的函数
void addCollegePerson() {
    char choice;
    cout << "请选择要添加的人员类别 (T: 教师, L: 实验员, A: 行政人员, Q: 返回主菜单): ";
    cin >> choice;

    if (choice == 'Q' || choice == 'q') {
        return;
    }

    int id = nextId++;
    string name, department, major, title, lab, position, politicalAffiliation, jobTitle;
    char gender;
    int age;

    cout << "请输入姓名: ";
    cin >> name;
    cout << "请输入性别 (M/F): ";
    cin >> gender;
    cout << "请输入年龄: ";
    cin >> age;

    switch (choice) {
        case 'T':
        case 't':
            cout << "请输入所在系部: ";
            cin >> department;
            cout << "请输入专业: ";
            cin >> major;
            cout << "请输入职称: ";
            cin >> title;
            collegePeople.push_back(new Teacher(id, name, gender, age, department, major, title));
            break;
        case 'L':
        case 'l':
            cout << "请输入所在实验室: ";
            cin >> lab;
            cout << "请输入职务: ";
            cin >> position;
            collegePeople.push_back(new LabAssistant(id, name, gender, age, lab, position));
            break;
        case 'A':
        case 'a':
            cout << "请输入政治面貌: ";
            cin >> politicalAffiliation;
            cout << "请输入职称: ";
            cin >> jobTitle;
            collegePeople.push_back(new Administrator(id, name, gender, age, politicalAffiliation, jobTitle));
            break;
        default:
            cout << "无效的选项" << endl;
            break;
    }

    cout << "成功添加人员记录!" << endl;
}

// 查询高校人员记录的函数
void searchCollegePerson() {
    int choice;
    cout << "请选择查询方式 (1: 根据编号, 2: 根据姓名, 3: 返回主菜单): ";
    cin >> choice;

    if (choice == 3) {
        return;
    }

    bool found = false;
    int targetId;
    string targetName;

    switch (choice) {
        case 1:
            cout << "请输入要查询的人员编号: ";
            cin >> targetId;
            break;
        case 2:
            cout << "请输入要查询的人员姓名: ";
            cin >> targetName;
            break;
        default:
            cout << "无效的选项" << endl;
            return;
    }

    for (const auto& person : collegePeople) {
        if ((choice == 1 && person->getId() == targetId) || (choice == 2 && person->getName() == targetName)) {
            person->display();
            found = true;
        }
    }

    if (!found) {
        cout << "未找到匹配的记录" << endl;
    }
}

// 显示所有高校人员记录的函数
void displayAllCollegePeople() {
    if (collegePeople.empty()) {
        cout << "记录为空！" << endl;
    } else {
        cout << "当前系统中的所有记录：" << endl;
        for (const auto& person : collegePeople) {
            person->display();
        }
    }
}

// 编辑高校人员记录的函数
void editCollegePerson() {
    int choice;
    cout << "请选择编辑方式 (1: 根据编号, 2: 根据姓名, 3: 返回主菜单): ";
    cin >> choice;

    if (choice == 3) {
        return;
    }

    bool found = false;
    int targetId;
    string targetName;

    switch (choice) {
        case 1:
            cout << "请输入要编辑的人员编号: ";
            cin >> targetId;
            break;
        case 2:
            cout << "请输入要编辑的人员姓名: ";
            cin >> targetName;
            break;
        default:
            cout << "无效的选项" << endl;
            return;
    }

    for (auto& person : collegePeople) {
        if ((choice == 1 && person->getId() == targetId) || (choice == 2 && person->getName() == targetName)) {
            person->display();
            cout << "请输入新的信息:" << endl;
            person->editInfo(); // 调用虚函数以供编辑信息
            found = true;
        }
    }

    if (!found) {
        cout << "未找到匹配的记录" << endl;
    }
}

// 删除高校人员记录的函数
void deleteCollegePerson() {
    if (collegePeople.empty()) {
        cout << "记录为空！" << endl;
        return;
    }

    int choice;
    cout << "请选择删除方式 (1: 根据编号, 2: 根据姓名, 3: 返回主菜单): ";
    cin >> choice;

    if (choice == 3) {
        return;
    }

    bool found = false;
    int targetId;
    string targetName;

    switch (choice) {
        case 1:
            cout << "请输入要删除的人员编号: ";
            cin >> targetId;
            break;
        case 2:
            cout << "请输入要删除的人员姓名: ";
            cin >> targetName;
            break;
        default:
            cout << "无效的选项" << endl;
            return;
    }

    for (auto it = collegePeople.begin(); it != collegePeople.end(); ++it) {
        if ((choice == 1 && (*it)->getId() == targetId) || (choice == 2 && (*it)->getName() == targetName)) {
            delete *it;
            collegePeople.erase(it);
            cout << "删除成功!" << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "未找到匹配的记录" << endl;
    }
}

// 统计高校人员记录的函数
void countCollegePeople() {
    int teacherCount = 0, labAssistantCount = 0, administratorCount = 0, totalCount = 0;
    int maleCount = 0, femaleCount = 0;

    for (const auto& person : collegePeople) {
        if (dynamic_cast<Teacher*>(person)) {
            teacherCount++;
        } else if (dynamic_cast<LabAssistant*>(person)) {
            labAssistantCount++;
        } else if (dynamic_cast<Administrator*>(person)) {
            administratorCount++;
        }

        if (person->getGender() == 'M' || person->getGender() == 'm') {
            maleCount++;
        } else if (person->getGender() == 'F' || person->getGender() == 'f') {
            femaleCount++;
        }
    }

    totalCount = collegePeople.size();

    cout << "教师数量: " << teacherCount << endl;
    cout << "实验员数量: " << labAssistantCount << endl;
    cout << "行政人员数量: " << administratorCount << endl;
    cout << "总人数: " << totalCount << endl;
    cout << "男性员工数量: " << maleCount << endl;
    cout << "女性员工数量: " << femaleCount << endl;
}

// 主函数
int main() {
    while (true) {
        cout << "高校人员系统管理程序" << endl;
        cout << "1. 添加人员记录" << endl;
        cout << "2. 查询人员记录" << endl;
        cout << "3. 显示所有人员记录" << endl;
        cout << "4. 编辑人员记录" << endl;
        cout << "5. 删除人员记录" << endl;
        cout << "6. 统计人员信息" << endl;
        cout << "7. 退出程序" << endl;
        cout << "请选择操作: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                addCollegePerson();
                break;
            case 2:
                searchCollegePerson();
                break;
            case 3:
                displayAllCollegePeople();
                break;
            case 4:
                editCollegePerson();
                break;
            case 5:
                deleteCollegePerson();
                break;
            case 6:
                countCollegePeople();
                break;
            case 7:
                // 释放动态分配的内存
                for (auto& person : collegePeople) {
                    delete person;
                }
                collegePeople.clear();
                return 0;
            default:
                cout << "无效的选项" << endl;
                break;
        }
    }

    return 0;
}
