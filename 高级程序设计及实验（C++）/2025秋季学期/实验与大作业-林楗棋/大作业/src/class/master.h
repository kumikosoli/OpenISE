#ifndef MASTER_H
#define MASTER_H
#include "graduate.h"
#include "publication.h"

// 硕士生类：Master
// 继承自Graduate，增加学位类型属性（学硕/专硕）。
// 与博士生类似，但是毕业要求不同。
class Master : public Graduate {
    private:
        std::vector<Publication> publications;
        std::string degree_type; //区分学硕与专硕
        static int totalMasters;
    public:
        // 构造和析构函数
        Master(const std::string& name, int age, int id, const std::string& gender,
               const std::string& researchArea, const std::string& advisor, const std::string& degreeType)
            : Graduate(name, age, id, gender, researchArea, advisor), degree_type(degreeType) {
                totalMasters++;
            }
        Master(const Master& other)
            : Graduate(other), publications(other.publications), degree_type(other.degree_type) {}
        ~Master() {
            totalMasters--;
        }

        // 赋值运算符
        Master& operator=(const Master& other) {
            if (this != &other) {
                Graduate::operator=(other);
                publications = other.publications;
                degree_type = other.degree_type;
            }
            return *this;
        }

        // 访问私有变量
        std::string getDegreeType() const { return degree_type; }
        static int getTotalMasters() { return totalMasters; }
        std::string getRole() const override { return "Master"; }

        // 序列化为JSON，覆写基类方法
        nlohmann::json toJson() const override {
            nlohmann::json j = Graduate::toJson();
            j["role"] = getRole();
            j["degreeType"] = degree_type;
            j["publications"] = nlohmann::json::array();
            for (const auto& pub : publications) {
                j["publications"].push_back(pub.toJson());
            }
            return j;
        }
        // 修改硕士生特有信息
        void setDegreeType(const std::string& newDegreeType) {
            degree_type = newDegreeType;
        }
        void addPublication(const Publication& pub) {
            publications.push_back(pub);
        }
    };
    inline int Master::totalMasters = 0;
#endif