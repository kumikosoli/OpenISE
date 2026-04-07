#ifndef UNDERGRADUATE_H
#define UNDERGRADUATE_H

#include "person.h"
// 本科生类：Undergraduate
// 继承自Person，增加专业、年级、已修课程等属性和方法。
// 本科生有自己的毕业要求如学分等。
class Undergraduate : public Person {
    public:
        struct classInfo {
            std::string className;
            int credit;
            int gpa;
        };
    private:
        std::string major;
        int year;
        static int totalStudents;
        static int creditToGraduate;
        int GPA;
        std::vector<classInfo> classInfos;
    public:
        // 构造和析构函数
        Undergraduate(const std::string& name, int age, int id, const std::string& gender,
                      const std::string& major, int year)
            : Person(name, age, id, gender), major(major), year(year) { totalStudents++; }
        Undergraduate(const Undergraduate& other)
            : Person(other), major(other.major), year(other.year), classInfos(other.classInfos) {}
        ~Undergraduate() override = default;

        // 赋值运算符
        Undergraduate& operator=(const Undergraduate& other) {
            if (this != &other) {
                Person::operator=(other);
                major = other.major;
                year = other.year;
                GPA = other.GPA;
                classInfos = other.classInfos;
            }
            return *this;
        }
        // 访问私有变量
        static int getTotalStudents() { return totalStudents; }
        static int getCreditToGraduate() { return creditToGraduate; }
        std::string getMajor() const { return major; }
        int getYear() const { return year; }
        std::string getRole() const override { return "Undergraduate"; }
        std::vector<classInfo> getClassInfos() const { return classInfos; }

        // 修改本科生特有信息
        void addClassInfo(const std::string& className, int credit, int gpa) {
            classInfos.push_back({className, credit, gpa});
        }
        // 计算GPA
        int calGpa() const {
            if (classInfos.empty()) return 0;
            int totalGpa = 0;
            int totalCredit = 0;
            for (const auto& ci : classInfos) {
                totalGpa += ci.gpa * ci.credit;
                totalCredit += ci.credit;
            }
            return totalCredit == 0 ? 0 : totalGpa / totalCredit;
        }
        // 序列化为JSON，覆写基类方法
        nlohmann::json toJson() const override {
            nlohmann::json j = Person::toJson();
            j["major"] = major;
            j["year"] = year;
            j["role"] = getRole();
            j["classInfo"] = nlohmann::json::array();
            for (const auto& ci : classInfos) {
                nlohmann::json ciJson;
                ciJson["className"] = ci.className;
                ciJson["gpa"] = ci.gpa;
                ciJson["credit"] = ci.credit;
                j["classInfo"].push_back(ciJson);
            }
            return j;
        }

        // 修改专业和年级
        void setMajor(const std::string& newMajor) { major = newMajor; }
        void setYear(int newYear) { year = newYear; }

    };

    inline int Undergraduate::totalStudents = 0;
    inline int Undergraduate::creditToGraduate = 0;

#endif

