#ifndef UTILS_H
#define UTILS_H
#include <string>
#include <vector>
#include <utility>
#include <map>
namespace utils {
    void File2WordMap(const std::string& filename, std::map<std::string, std::vector<std::pair<int, int>>>& wordMap); 
    bool CheckViable(int row, int col, std::map<std::string, std::vector<std::pair<int, int>>>& wordMap);
    std::vector<std::pair<std::string, int>> getCount(std::map<std::string, std::vector<std::pair<int, int>>>& wordMap);
};
#endif
