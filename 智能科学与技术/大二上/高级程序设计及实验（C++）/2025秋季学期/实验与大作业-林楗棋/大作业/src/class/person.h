#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <nlohmann/json.hpp>


// 抽象基类：Person
// 用于保存最基本的学生信息如姓名、年龄、ID、性别等。派生出本科生和研究生类。
// 本科生类有专业、年级、已修课程等属性和方法。
// 研究生类有研究方向、导师、发表论文等属性和方法。
// 研究生类分为硕士生和博士生，分别继承自研究生类，增加各自特有的属性和方法。
// 硕士生分为学硕和专硕，硕博生有不同的毕业要求。
class Person {
    friend class Manager; // 友元类，方便管理学生信息
    protected:
        std::string name;
        int age;
        int id;
        std::string gender;

    public:
        // 构造和析构函数
        Person(const std::string& name, int age, int id, const std::string& gender)
            : name(name), age(age), id(id), gender(gender) {}
        Person(const Person& other)
            : name(other.name), age(other.age), id(other.id), gender(other.gender) {}
        virtual ~Person() = default;

        // 赋值运算符
        Person& operator=(const Person& other) {
            if (this != &other) {
                name = other.name;
                age = other.age;
                id = other.id;
                gender = other.gender;
            }
            return *this;
        }

        // 访问私有变量
        std::string getName() const { return name; }
        int getAge() const { return age; }
        int getId() const { return id; }
        std::string getGender() const { return gender; }
        virtual std::string getRole() const = 0;
        // 序列化为JSON
        virtual nlohmann::json toJson() const {
            nlohmann::json j;
            j["name"] = name;
            j["age"] = age;
            j["id"] = id;
            j["gender"] = gender;
            return j;
        }
        // 修改基本信息
        void setName(const std::string& newName) { name = newName; }
        void setAge(int newAge) { age = newAge; }
        void setGender(const std::string& newGender) { gender = newGender; }
};





#endif