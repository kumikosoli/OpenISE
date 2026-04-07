#ifndef NAMELIST_H
#define NAMELIST_H
#include <string>
#include <vector>
class NameList {
public:
    NameList(std::string name);
    ~NameList();
    NameList(const NameList&);
    NameList& operator=(const NameList&);
    void addName(const std::string&);
    void deleteName(const std::string&);
    std::vector<std::string> search(const std::string& substr);
    void print(int order);
    std::vector<std::string> getNames() const;
private:
    std::vector<std::string> names;
};
#endif