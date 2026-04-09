#ifndef GRADUATE_H
#define GRADUATE_H
#include "person.h"
#include "publication.h"
#include <vector>

// 抽象基类：Graduate
// 继承自Person，增加研究方向、导师、发表论文等属性和方法这些硕博生通用的属性和方法。
// 硕士生和博士生类分别继承自Graduate，增加各自特有的属性和方法。
// 硕士生分为学硕和专硕，硕博生有不同的毕业要求。
class Graduate : public Person {
    private:
        std::string researchArea;
        std::string advisor;
        std::vector<Publication> publications;        
    public:
        // 构造和析构函数
        Graduate(const std::string& name, int age, int id, const std::string& gender,
                 const std::string& researchArea, const std::string& advisor)
            : Person(name, age, id, gender), researchArea(researchArea), advisor(advisor) {}
        Graduate(const Graduate& other)
            : Person(other), researchArea(other.researchArea), advisor(other.advisor), publications(other.publications) {}
        ~Graduate() = default;

        // 赋值运算符
        Graduate& operator=(const Graduate& other) {
            if (this != &other) {
                Person::operator=(other);
                researchArea = other.researchArea;
                advisor = other.advisor;
                publications = other.publications;
            }
            return *this;
        } 

        // 访问私有变量
        std::string getResearchArea() const { return researchArea; }
        std::string getAdvisor() const { return advisor; }
        virtual std::string getRole() const = 0;

        // 论文相关方法
        void addPublication(const Publication& pub) { publications.push_back(pub); }
        const std::vector<Publication>& getPublications() const { return publications; }

        // 序列化为JSON，覆写基类方法
        nlohmann::json toJson() const override {
            nlohmann::json j = Person::toJson();
            j["researchArea"] = researchArea;
            j["advisor"] = advisor;
            j["role"] = getRole();
            return j;
        }
        // 修改研究生特有信息
        void setResearchArea(const std::string& newResearchArea) { researchArea = newResearchArea; }
        void setAdvisor(const std::string& newAdvisor) { advisor = newAdvisor; }
}; 

#endif