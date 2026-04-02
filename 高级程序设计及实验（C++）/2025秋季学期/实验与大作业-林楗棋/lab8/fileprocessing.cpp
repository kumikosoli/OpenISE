#include "utils.h"
#include "fileprocessing.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <fstream>
#include <algorithm>

FileProcessing::FileProcessing(const std::string& filename) {
    std::map<std::string, std::vector<std::pair<int, int>>> wordMap;
    utils::File2WordMap(filename, wordMap);
    this->wordMap = wordMap;
    for (const auto& entry : wordMap) {
        wordSet.insert(entry.first);
    }
}

FileProcessing::FileProcessing(const FileProcessing& other) {
    this->wordMap = other.wordMap;
    this->wordSet = other.wordSet;
}

FileProcessing& FileProcessing::operator=(const FileProcessing& other) {
    if (this != &other) {
        this->wordMap = other.wordMap;
        this->wordSet = other.wordSet;
    }
    return *this;
}

bool FileProcessing::IsWordAppear(const std::string& word) {
    return wordMap.find(word) != wordMap.end();
}

int FileProcessing::CountWordOccurrences(const std::string& word) {
    auto it = wordMap.find(word);
    if (it != wordMap.end()) {
        return it->second.size();
    }
    return 0;
}

void FileProcessing::AddNewWord(const std::string& word, int row, int col) {
    auto it = wordMap.find(word);
    if (!utils::CheckViable(row, col, this->wordMap)) {
        std::cerr << "输入位置非法" << std::endl;
        return;
    }
    wordMap[word].emplace_back(row, col);
}

void FileProcessing::SaveToFile(const std::string& filename) {
    std::ofstream output(filename);
    if (!output.is_open()) {
        std::cerr << "无法打开文件进行写入: " << filename << std::endl;
        return;
    }
    for (const auto& entry : wordMap) {
        const std::string& word = entry.first;
        const auto& positions = entry.second;
        for (const auto& pos : positions) {
            output << word << " " << pos.first << " " << pos.second << std::endl;
        }
    }
    output.close();
}

void FileProcessing::DeleteWord(const std::string& word) {
    auto it = wordMap.find(word);
    if (it == wordMap.end()) {
        return;
    }

    std::map<int, std::vector<int>> rowToDeleteCols;
    for (const auto& pos : it->second) {
        rowToDeleteCols[pos.first].push_back(pos.second);
    }
    for (auto& entry : rowToDeleteCols) {
        std::sort(entry.second.begin(), entry.second.end());
    }

    std::map<std::string, std::vector<std::pair<int, int>>> newWordMap;
    for (const auto& entry : wordMap) {
        const std::string& curWord = entry.first;
        const auto& positions = entry.second;
        std::vector<std::pair<int, int>> newPositions;
        newPositions.reserve(positions.size());

        for (const auto& pos : positions) {
            auto rowIt = rowToDeleteCols.find(pos.first);
            if (rowIt != rowToDeleteCols.end()) {
                const auto& delCols = rowIt->second;
                if (curWord == word && std::binary_search(delCols.begin(), delCols.end(), pos.second)) {
                    continue;
                }
                int shift = std::lower_bound(delCols.begin(), delCols.end(), pos.second) - delCols.begin();
                newPositions.emplace_back(pos.first, pos.second - shift);
            } else {
                newPositions.emplace_back(pos);
            }
        }
        if (!newPositions.empty()) {
            newWordMap[curWord] = std::move(newPositions);
        }
    }

    wordMap = std::move(newWordMap);
    wordSet.clear();
    for (const auto& entry : wordMap) {
        wordSet.insert(entry.first);
    }
}

void FileProcessing::DisplayWords() {
    for (const auto& entry : wordMap) {
        std::cout << entry.first << ":";
        for (const auto& pos : entry.second) {
            std::cout << "(" << pos.first << ", " << pos.second << ")";
        }
        std::cout << std::endl;
    }
}

void FileProcessing::PrintWordOccur() {
    std::vector<std::pair<std::string, int>> wordCount = utils::getCount(wordMap);
    for (auto& entry : wordCount) {
        std::cout << entry.first << " ";
    }
    std::cout << std::endl;
}

void FileProcessing::PrintWordCount() {
    std::vector<std::pair<std::string, int>> wordCount = utils::getCount(wordMap);
    for (auto& entry : wordCount) {
        std::cout << entry.first << ':' << entry.second << ' ';
    }
    std::cout << std::endl;
}

void FileProcessing::PrintTopWords(int n) {
    std::vector<std::pair<std::string, int>> wordCount = utils::getCount(wordMap);
    n = n > wordCount.size() ? wordCount.size(): n;
    for (int i = 0; i < n; i++) {
        std::cout << wordCount[n].first << ' ';
    }
    std::cout << std::endl;
}

void FileProcessing::PrintWordsAscend() {
    std::vector<std::pair<std::string, int>> wordCount = utils::getCount(wordMap);
    std::sort(wordCount.begin(), wordCount.end(), [](const auto& a, const auto& b){ return a.first < b.first; });
    for (const auto& word : wordCount) {
        std::cout << word.first << ' ';
    }
    std::cout << std::endl;
}
