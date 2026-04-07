#include "NameList.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

NameList::NameList(std::string name) : names{std::move(name)} {
}

NameList::~NameList() {
    names.clear();
}

NameList::NameList(const NameList& other) : names(other.names) {
}

NameList& NameList::operator=(const NameList& other) {
    if (this != &other) {
        names = other.names;
    }
    return *this;
}

void NameList::addName(const std::string& newName) {
    this->names.push_back(newName);
}

void NameList::deleteName(const std::string& deName) { //采用find() + erase(),见https://blog.csdn.net/mashiromylove/article/details/137673545
    auto iter  = std::find(names.begin(), names.end(), deName);
    while (iter != names.end()) {
        names.erase(iter);
        iter = std::find(names.begin(), names.end(), deName);
    }
}

std::vector<std::string> NameList::getNames() const {
    return names;
}

std::vector<std::string> increseOrder(const NameList& list) { //辅助函数，升序排列，见https://blog.csdn.net/2301_79396857/article/details/136129239
    std::vector<std::string> iterlist = list.getNames();
    std::sort(iterlist.begin(), iterlist.end());
    return iterlist;
}

bool cmp(std::string const a, std::string const b) {
    return a > b;
}

std::vector<std::string> decreaseOrder(const NameList& list) {
    std::vector<std::string> iterlist = list.getNames();
    std::sort(iterlist.begin(), iterlist.end(), cmp);
    return iterlist;
}

// order=0表示按存储顺序打印，1表示升序，2表示降序
void NameList::print(int order) {
    switch (order) {
        case 0: {
            for (auto name : names) {
                std::cout << name << ' ';
            }
            std::cout << std::endl;
            break;
        }
        case 1: {
            for (auto name : increseOrder(*this)) {
                std::cout << name << ' ';
            }
            std::cout << std::endl;
            break;
        }
        case 2: {
            for (auto name : decreaseOrder(*this)) {
                std::cout << name << ' ';
            }
            std::cout << std::endl;
            break;
        }
    }

}

// 查找包含字串的所有名字，见https://blog.csdn.net/llllllliuhz_/article/details/147228341
std::vector<std::string> NameList::search(const std::string& substr) {
    std::vector<std::string> contains;
    for (auto name : names) {
        if (name.find(substr) != std::string::npos) {
            contains.push_back(name);
        }
    }
    return contains;
}

