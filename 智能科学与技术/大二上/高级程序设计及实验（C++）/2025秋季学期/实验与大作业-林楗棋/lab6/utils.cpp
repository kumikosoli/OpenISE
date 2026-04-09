#include <iostream>
#include <string>
#include <unordered_set>

/* 
* 编写字符串过滤函数规则如下：
* 字符串中多个相同的字符，将非首次出现的字符过滤掉。
* 比如字符串“abacacde”过滤结果为“abcde”。
*/
void stringFilter(const std::string &inputStr, std::string &outStr) {
    outStr.clear();
    if (inputStr.empty()) {
        return;
    }
    std::unordered_set<char> seenChars;
    for (char c : inputStr) {
        if (!seenChars.count(c)) {
            outStr += c;
            seenChars.insert(c);
        }
    }
}

/*
编写字符串压缩函数，将字符串中连续重复字母压缩。规则如下：
* 1. 仅压缩连续重复出现的字符。比如"abcbc"无连续重复字符，压缩为"abcbc".
* 2. 压缩字段的格式为"字符重复的次数+字符"。例如：字符串"xxxyyyyyyz"压缩为"3x6yz"
* 示例 输入：“cccddecc” ，“adef”，“pppppppp”输出：“3c2de2c”，“adef”，“8p”
*/
void stringZip(const std::string &inputStr, std::string &outStr) {
    outStr.clear();
    if (inputStr.empty()) {
        return;
    }
    for (int i = 0; i < inputStr.size();i++) {
        char currentChar = inputStr[i];
        int count = 1;
        while (i + 1 < inputStr.size() && inputStr[i + 1] == currentChar) {
            count++;
            i++;
        }
        if (count > 1) {
            outStr.append(std::to_string(count));
        }
        outStr += currentChar;
    }
}


/*
* 编写一个字符串解压程序，实现2中反向功能；
* 输入：“8p” 输出：“pppppppp”
*/
void stringUnzip(const std::string &inputStr, std::string &outStr) {
    outStr.clear();
    if (inputStr.empty()) {
        return;
    }
    int size = inputStr.size();
    for (int i = 0; i < size; i++) {
        if (isdigit(inputStr[i]) && i + 1 < size) {
            int count = 0, j = i;
            while (j < size && isdigit(inputStr[j])) {
                count = count * 10 + inputStr[j] - '0';
                j++;
            }
            char str = inputStr[j];
            outStr.append(count, str);
            i = j; 
        } else {
            outStr += inputStr[i];
        }
    }
}