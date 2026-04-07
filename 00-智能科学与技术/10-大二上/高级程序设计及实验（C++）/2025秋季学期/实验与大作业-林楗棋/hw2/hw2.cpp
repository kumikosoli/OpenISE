#include"iostream"
#include "string"
#include "vector"

bool is_num(std::string str) {
    for (char c : str) {
        if (!isdigit(c) && c != '.') {
            return false;
        }
    }
    return true;
}

bool is_flt(std::string str) {
    for (char c : str) {
        if (c == '.') {
            return true;
        }
    }
    return false;
}

int main() {
    std::string blackHole = "EHT measured the black hole's mass to be approximately 6.5 billion solar masses and measured the diameter of its event horizon to be approximately 40 billion kilometres (270 AU; 0.0013 pc; 0.0042 ly)";
    std::vector<std::string> str;
    std::vector<int> integer;
    std::vector<float> flt;
    std::string temp;
    for (char tempStr : blackHole) {
        if (tempStr == ' ' || tempStr == '(' || tempStr == ')' || tempStr == ';') {
            if (temp.empty()) {
                continue;
            }
            if (is_num(temp)) {
                if (is_flt(temp)) {
                    flt.push_back(std::stof(temp));
                }
                else {
                    integer.push_back(std::stoi(temp));
                }
            } 
            else {
                str.push_back(temp);
            }           
            temp.clear();
        }
        else {
            temp.push_back(tempStr);
        }
    }
    std::cout << "单词有" << str.size() << "个:\n";
    for (const auto& w : str) std::cout << w << " ";
    std::cout << "\n整数有" << integer.size() << "个\n";
    for (const auto& i : integer) std::cout << i << " ";
    std::cout << "\n小数有" << flt.size() << "个\n";
    for (const auto& f : flt) std::cout << f << " ";
    std::cout << std::endl;
}