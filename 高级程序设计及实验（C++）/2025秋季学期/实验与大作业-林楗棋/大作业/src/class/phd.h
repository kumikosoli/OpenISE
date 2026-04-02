#ifndef PHD_H
#define PHD_H
#include "graduate.h"
#include "publication.h"

class Master; // 前向声明，防止循环依赖

// 博士生类：PhD
// 继承自Graduate，增加博士生特有的属性和方法。
// 与硕士生类似，但是毕业要求不同。
class PhD : public Graduate {
    private:
        static int totalPhDs;
        std::vector<Publication> publications;
    public:
        // 构造和析构函数
        PhD(const std::string& name, int age, int id, const std::string& gender,
            const std::string& researchArea, const std::string& advisor)
            : Graduate(name, age, id, gender, researchArea, advisor) {
                totalPhDs++;
            }
        PhD(const PhD& other)
            : Graduate(other), publications(other.publications) {}
        ~PhD() {
            totalPhDs--;
        }

        // 赋值运算符
        PhD& operator=(const PhD& other) {
            if (this != &other) {
                Graduate::operator=(other);
                publications = other.publications;
            }
            return *this;
        }
        // 访问私有变量
        static int getTotalPhDs() { return totalPhDs; }
        std::string getRole() const override { return "PhD"; }
        // 序列化为JSON，覆写基类方法
        nlohmann::json toJson() const override {
            nlohmann::json j = Graduate::toJson();
            j["role"] = getRole();
            j["publications"] = nlohmann::json::array();
            for (const auto& pub : publications) {
                j["publications"].push_back(pub.toJson());
            }
            return j;
        }
        // 修改博士生特有信息
        void addPublication(const Publication& pub) {
            publications.push_back(pub);
        }

        friend void addPublication(PhD& phd, Master& master, const std::string& title, const std::string& journal, int year);
    };
    // 初始化博士生总数
    inline int PhD::totalPhDs = 0;
#endif