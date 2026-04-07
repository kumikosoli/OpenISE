#ifndef PUBLICATION_H
#define PUBLICATION_H

#include <string>
#include <nlohmann/json.hpp>
#include <vector>

class Graduate; // 前向声明，防止循环依赖

// 论文类：Publication
// 用于保存论文的基本信息如标题、期刊、年份、作者等。
// 论文可以有多个作者，作者可以是硕士生或博士生。
// 由于防止Json循环引用，作者信息只保存姓名、ID和角色，不保存完整对象引用。
class Publication {
    public:
        struct AuthorInfo {
            std::string name;
            int id;
            std::string role;  // "Master" or "PhD"
            
            AuthorInfo(const std::string& n, int i, const std::string& r)
                : name(n), id(i), role(r) {}
        };
    private:
        std::string title;
        std::string journal;
        int year;
        std::vector<AuthorInfo> authors;
    public:
        // 构造和析构函数
        Publication(const std::string& title, const std::string& journal, int year)
            : title(title), journal(journal), year(year) {}
        Publication(const Publication& other)
            : title(other.title), journal(other.journal), year(other.year), authors(other.authors) {}
        ~Publication() = default;

        // 赋值运算符
        Publication& operator=(const Publication& other) {
            if (this != &other) {
                title = other.title;
                journal = other.journal;
                year = other.year;
                authors = other.authors;
            }
            return *this;
        }
        // 访问私有变量
        std::string getTitle() const { return title; }
        std::string getJournal() const { return journal; }
        int getYear() const { return year; }
        const std::vector<AuthorInfo>& getAuthors() const { return authors; }
    
        void addAuthor(const std::string& name, int id, const std::string& role) {
            authors.emplace_back(name, id, role);
        }
        nlohmann::json toJson() const;
};
#endif
