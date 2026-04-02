#ifndef FILEPROCESSING_H
#define FILEPROCESSING_H
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <set>
#include "utils.h"

class FileProcessing {
public:
    FileProcessing(const std::string& filename);
    ~FileProcessing() = default;
    FileProcessing(const FileProcessing& other);
    FileProcessing& operator=(const FileProcessing& other);
    bool IsWordAppear(const std::string& word);
    int CountWordOccurrences(const std::string& word);
    void AddNewWord(const std::string& word, int row, int col);
    void SaveToFile(const std::string& filename);
    void DeleteWord(const std::string& word);
    void DisplayWords();
    void PrintWordOccur();
    void PrintWordsAscend();
    void PrintWordCount();
    void PrintTopWords(int n);
private:
    std::map<std::string, std::vector<std::pair<int, int>>> wordMap; 
    std::set<std::string> wordSet;
};
#endif 


// 设计一个类（运用STL的知识,e.g. vector, set, map等）FileProcessing，实现
// 1. 将文本中的单词逐行读取，纪录单词及其行、列号（第几行，第几个）。
// 2. 提供查询函数，查询给定单词是否在文本中出现
// 3. 提供统计函数，统计给定单词出现的次数
// 4. 提供函数，增加新的单词
// 5. 提供保存函数，输出到文本（并保持行列的位置，新增加的放在最后）
// 6. 提供删除函数，删除给定的单词 (选做)
// 7. 提供显示函数，显示单词及其行列
// 8. 提供排序函数，按照单词出现的次数输出（选做）
// 9. 提供构造函数，析构函数，复制构造函数，重载

// 在实验八的基础上完成 （自己提供一个文本）：
// 1. void PrintWordsAscend() 将所有单词按字典升序排列，重新打印
// 2. void PrintWordCount(), 打印每个单词出现的次数，如the: 36, word: 12
// 3. void PrintTopWords(int n), 打印词频最高的n个单词及其出现的次数（至少完成n=1的情况, n>1选做）