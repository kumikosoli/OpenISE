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

    // 模糊匹配函数
    MailList Find(const string& regex) {
        
        MailList searchlist;
        
        for (int i = 0; i < student_size_; i++) {
            if (student_[i].find(regex) != string::npos) {
                searchlist.AddMail(student_[i]);
            }
        }

        for (int i = 0; i < teacher_size_; i++) {
            if (teacher_[i].find(regex) != string::npos) {
                searchlist.AddMail(teacher_[i]);
            }
        }

        return searchlist;
    }
    
    // 重载<<运算符(主函数中通过与getline读入函数两个函数一起进行验证)
    friend ostream& operator<<(ostream& os, const MailList& ml) {
    os << "teacher mail:" << endl;
    for (int i = 0; i < ml.teacher_size_; i++) {
        os << ml.teacher_[i] << endl;
    }
    os << "student mail:" << endl;
    for (int i = 0; i < ml.student_size_; i++) {
        os << ml.student_[i] << endl;
    }
    return os;
    }
};

int main(int argc, char const *argv[]) {
    MailList ml;
    ml.AddMail("caisy8@mail2.sysu.edu.cn");
    ml.AddMail("jianggg1@mail.sysu.edu.cn");
    ml.AddMail("lizy66@mail2.sysu.edu.cn");
    ml.AddMail("Zhongzy13@mail2.sysu.edu.cn");
    ml.AddMail("Liuzy60@mail.sysu.edu.cn");
    ml.AddMail("Zhuzl@mail.sysu.edu.cn");

    cout << "学生邮箱：" << endl;
    const string* student = ml.GetStudent();
    int studentSize = ml.GetStudentSize();
    for (int i = 0; i < studentSize; i++) {
    cout << student[i] << " " << endl;
    }
    cout << "老师邮箱：" << endl;
    const string* teacher = ml.GetTeacher();
    int teacherSize = ml.GetTeacherSize();
    for (int i = 0; i < teacherSize; i++) {
        cout << teacher[i] << " " << endl;
    }
    cout << endl;
    string m;
    cout << "请输入需要进行模糊匹配的关键词：" << endl;
    cin >> m;
    MailList searchlist = ml.Find(m);

    const string* student_list = searchlist.GetStudent();
    int student_size = searchlist.GetStudentSize();
    for (int i = 0; i < student_size; i++) {
        cout << student_list[i] << endl;
    }

    const string* teacher_list = searchlist.GetTeacher();
    int teacher_size = searchlist.GetTeacherSize();
    cout << "Teacher emails:" << endl;
    for (int i = 0; i < teacher_size; i++) {
        cout << teacher_list[i] << endl;
    }
    cout << endl;

    // 调用getline函数以逗号为分隔符读入多个邮箱
    cout << "请输入需要读入的邮箱，用逗号作为分隔符：" << endl;
    string line;
    cin.ignore(); // 清除输入流中的换行符
    getline(std::cin, line); 
    size_t pos = 0;
    while ((pos = line.find(',')) != string::npos) {
        string email = line.substr(0, pos);
        ml.AddMail(email);
        line.erase(0, pos + 1);
    }
    ml.AddMail(line);
    cout << ml;

    return 0;
}