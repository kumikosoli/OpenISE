#include <iostream>
#include <string>

using namespace std;

class MailList {
private:
    string* student_;   // 学生邮箱名数组
    int student_size_;  // 学生邮箱名数组长度
    string* teacher_;   // 老师邮箱名数组
    int teacher_size_;  // 老师邮箱名数组长度

public:
    // 默认构造函数
    MailList() {
        student_ = new string[1000];
        student_size_ = 0; 
        teacher_ = new string[1000];
        teacher_size_ = 0; 
    }

    // 复制构造函数
    MailList(const MailList& ml) {
        student_ = new string[1000];
        student_size_ = ml.student_size_;
        copy(ml.student_, ml.student_ + ml.student_size_, student_);

        teacher_ = new string[1000];
        teacher_size_ = ml.teacher_size_;
        copy(ml.teacher_, ml.teacher_ + ml.teacher_size_, teacher_);
    }

    // 析构函数
    ~MailList() {
        delete [] student_;
        delete [] teacher_;
    }

    // 重载=运算符
    MailList& operator=(const MailList& ml)  {   // 重载=运算符（参数是const String&）
        if (this == &ml) {
		    return *this;
        }
        delete [] student_;
        delete [] teacher_;
        student_size_ = ml.student_size_;
        teacher_size_ = ml.teacher_size_;
        student_ = new string[student_size_ + 1];
        teacher_ = new string[teacher_size_ + 1];
        copy(ml.student_, ml.student_ + student_size_, student_);
        copy(ml.teacher_, ml.teacher_ + teacher_size_, teacher_);
        return *this;
    };

    // 新增邮箱函数
    void AddMail(const string& mail) {
        size_t pos = mail.find('@');
        string name = mail.substr(0, pos);
        string mailname = mail.substr(pos + 1);

        if (mailname == "mail2.sysu.edu.cn") {
            student_[student_size_++] = name;
        } else if (mailname == "mail.sysu.edu.cn"){
            teacher_[teacher_size_++] = name;
        }
    }
};

int main() {
    MailList ml;

    ml.AddMail("student1@mail2.sysu.edu.cn");
    ml.AddMail("student2@mail2.sysu.edu.cn");
    ml.AddMail("teacher1@mail.sysu.edu.cn");

    cout << "学生邮箱名：";
    for (int i = 0; i < ml.student_size_; i++) {
        cout << ml.student_[i] << " ";
    }
    cout << endl;

    cout << "老师邮箱名：";
    for (int i = 0; i < ml.teacher_size_; i++) {
        cout << ml.teacher_[i] << " ";
    }
    cout << endl;

    return 0;
}