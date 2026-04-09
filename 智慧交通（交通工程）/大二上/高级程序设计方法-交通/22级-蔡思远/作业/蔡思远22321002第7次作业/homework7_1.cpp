#include <iostream>
#include <cstring>
using namespace std;

// 老师/助教好！由于mac系统上编写的程序转移到windows系统上的dev c++后容易出现注释乱码的问题，我将作业的代码专门放入了一个word文档中。若注释出现乱码，在该word文档中可查看注释。代码运行无影响。

class String {
private:
    char* str; // pointer to string
    int len; // length of string

    static int npos; // 查找函数查找不到使返回的值

public:
	// constructors and other methods    
    String(const char* s) {   // constructor
        len = strlen(s);
        str = new char[len + 1];
        strcpy(str, s);
};
    String() {   // default constructor
        len = 0;
        str = new char[1];
        str[0] = '\0';
};

    String(const String& s) {   // copy constructor
        len = s.len;
        str = new char[len + 1];
        strcpy(str, s.str);
};
    ~String() {   // destructor
        delete[] str;
}; 

    String& operator=(const char* s) {   // 重载=运算符（参数是const char*）
    delete[] str;
    len = strlen(s);
    str = new char[len + 1];
    strcpy(str, s);
    return *this;
};

    String& operator=(const String& s)  {   // 重载=运算符（参数是const String&）
        if (this == &s) {
		    return *this;
        }
        delete[] str;
        len = s.len;
        str = new char[len + 1];
        strcpy(str, s.str);
        return *this;
};

    // 查找函数
    int find(char c) {
    for (int i = 0; i < len; i++) {
        if (str[i] == c) {
            return i;
        }
    }
    return npos;
};

    // 插入n个相同字符函数
    void insert(int pos, int n, char c) {
        char *temp = new char[len + n + 1];
        for(int i = 0; i < pos; ++i) {
            temp[i] = str[i];
            }
        for(int i = pos; i < pos + n; ++i) {
            temp[i] = c;
            }
        for(int i = pos; i <= len; ++i) {
            temp[i + n] = str[i];
            }
        delete[] str;
        str = temp;
        len = len + n;
    };    

    // 返回字符串的子串函数substr函数
    String substr(int pos, int n = String::npos){
        if (n == String::npos) {   // 如果n未设置，则将n设置为从给定位置到字符串结尾的长度
            n = len - pos;
        }
        char* sub_str = new char[n + 1];
        strncpy(sub_str, str + pos, n);
        sub_str[n] = '\0';
        String result(sub_str);
        delete[] sub_str;
        return result;
    };
    
    const char* str2() const {   // 添加成员函数用于访问str
    return str;
    };
};

int String::npos = -1;

int main() {
	
    String s1("I'm from SYSU");
    cout << "s1：" << s1.str2() << endl;
    String s2(s1);
    cout << "s2: " << s2.str2() << endl;
    s1.insert(1, 3, 'x');
    cout << "在s1/s2的第2个位置插入3个x：" << s1.str2() << endl;
    String s3 = s1.substr(2, 5);
    cout << "返回以上字符串从第3个位置开始的5个字符的子串：" << s3.str2() << endl;
    int find_result = s1.find('U');
    cout << "'U'第一次出现的位置为第" << (find_result - 2) << "位" << endl;

    return 0;
}

