#include "utils.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <fstream>
#include <sstream>
#include <algorithm>

namespace utils {
    void File2WordMap(const std::string& filename, std::map<std::string, std::vector<std::pair<int, int>>>& wordMap) {
        std::ifstream input(filename);
        if (!input.is_open()) {
            std::cerr << "Failed to open file: " << filename << std::endl;
            return;
        }
        std::string line;
        int lineNumber = 0;
        while (std::getline(input, line)) {
            lineNumber++;
            std::istringstream iss(line);
            std::string word;
            int columnNumber = 0;
            while (iss >> word) {
                columnNumber++;
                wordMap[word].emplace_back(lineNumber, columnNumber);
            }
        }
    }

    /* 检查这个位置能否放置字，首先检查是否有重叠，其次检查这个位置之前有没有词。当然要排除非法的位置（如小于1），如果空集直接返回真 */
    bool CheckViable(int row, int col, std::map<std::string, std::vector<std::pair<int, int>>>& wordMap) {
        if (row < 1 || col < 1) {
            return false;
        }
        if (wordMap.empty()) {
            return true;
        }
        bool isDup = true;
        std::pair<int, int> pos = std::make_pair(row, col);
        for (auto word : wordMap) {
            for (auto position : word.second) {
                if (pos == position) {
                    return false;
                }
            }
        }
        for (auto word : wordMap) {
            for (auto position : word.second) {
                if (position.first == row && position.second + 1 == col) {
                    return true;
                }
            }
        }
        if (col == 1) { // 不允许跨行
            for (auto word : wordMap) {
                for (auto position : word.second) {
                    if (position.first == row - 1) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
    
    std::vector<std::pair<std::string, int>> getCount(std::map<std::string, std::vector<std::pair<int, int>>>& wordMap) {
        std::vector<std::pair<std::string, int>> wordCount;
        for (auto entry : wordMap) {
            std::pair<std::string, int> pair = std::make_pair(entry.first, entry.second.size());
            wordCount.push_back(pair);
        }
        std::sort(wordCount.begin(), wordCount.end(), [](const auto& a, const auto& b) {return a.second < b.second;});
        //https://blog.csdn.net/m0_60134435/article/details/136151698
        // https://blog.csdn.net/weixin_41588502/article/details/86620305
        return wordCount;
    }
}