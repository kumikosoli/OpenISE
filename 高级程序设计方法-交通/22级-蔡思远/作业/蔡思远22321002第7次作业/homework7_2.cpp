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
    // 将老师/学生邮箱分配到对应的数组存储
        if (mailname == "mail2.sysu.edu.cn") {
            student_[student_size_++] = mail;
        } else if (mailname == "mail.sysu.edu.cn"){
            teacher_[teacher_size_++] = mail;
        }
    }
    // 获取private中的元素，使主函数得以使用
    int GetStudentSize() const {
        return student_size_;
    }
    const string* GetStudent() const {
        return student_;
    }
    int GetTeacherSize() const {
        return teacher_size_;
    }
    const string* GetTeacher() const {
        return teacher_;
    }
};

int main() {
    MailList ml;
    ml.AddMail("caisy8@mail2.sysu.edu.cn");
    ml.AddMail("jianggg1@mail.sysu.edu.cn");
    cout << "学生邮箱：";
    const string* student = ml.GetStudent();
    int studentSize = ml.GetStudentSize();
    for (int i = 0; i < studentSize; i++) {
    cout << student[i] << " ";
    }
    cout << endl;
    cout << "老师邮箱：";
    const string* teacher = ml.GetTeacher();
    int teacherSize = ml.GetTeacherSize();
    for (int i = 0; i < teacherSize; i++) {
        cout << teacher[i] << " ";
    }
    
    return 0;
}



