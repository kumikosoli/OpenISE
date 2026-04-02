#ifndef CLI_H
#define CLI_H

#include "manager.h"
#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <iomanip>

class CLI {
private:
    Manager& manager;
    bool running;

    // ---------辅助函数---------
    // 清除输入缓冲区
    void clearInput() {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // 读取整数
    int readInt(const std::string& prompt) {
        int value;
        while (true) {
            std::cout << prompt;
            if (std::cin >> value) {
                clearInput();
                return value;
            }
            std::cout << "输入无效，请输入整数。\n";
            clearInput();
        }
    }

    // 读取字符串
    std::string readString(const std::string& prompt) {
        std::string value;
        std::cout << prompt;
        std::getline(std::cin, value);
        return value;
    }

    // 显示学生信息
    void displayStudent(Person* p) {
        if (!p) return;
        std::cout << "----------------------------------------\n";
        std::cout << "ID: " << p->getId() << "\n";
        std::cout << "姓名: " << p->getName() << "\n";
        std::cout << "年龄: " << p->getAge() << "\n";
        std::cout << "性别: " << p->getGender() << "\n";
        std::cout << "类型: " << p->getRole() << "\n";

        if (p->getRole() == "Undergraduate") {
            Undergraduate* ug = dynamic_cast<Undergraduate*>(p);
            if (ug) {
                std::cout << "专业: " << ug->getMajor() << "\n";
                std::cout << "年级: " << ug->getYear() << "\n";
                std::cout << "GPA: " << ug->calGpa() << "\n";
                auto classes = ug->getClassInfos();
                if (!classes.empty()) {
                    std::cout << "课程:\n";
                    for (const auto& c : classes) {
                        std::cout << "  - " << c.className << " (学分:" << c.credit << ", 绩点:" << c.gpa << ")\n";
                    }
                }
            }
        } else if (p->getRole() == "Master" || p->getRole() == "PhD") {
            Graduate* grad = dynamic_cast<Graduate*>(p);
            if (grad) {
                std::cout << "研究方向: " << grad->getResearchArea() << "\n";
                std::cout << "导师: " << grad->getAdvisor() << "\n";
                auto pubs = grad->getPublications();
                if (!pubs.empty()) {
                    std::cout << "论文 (" << pubs.size() << " 篇):\n";
                    for (const auto& pub : pubs) {
                        std::cout << "  - " << pub.getTitle() << " (" << pub.getJournal() << ", " << pub.getYear() << ")\n";
                    }
                }
            }
        }
    }

    // --------学生管理命令--------
    void cmdAddStudent() {
        std::cout << "\n-----添加学生-----\n";
        std::cout << "选择学生类型:\n";
        std::cout << "1. 本科生\n";
        std::cout << "2. 硕士生\n";
        std::cout << "3. 博士生\n";
        int type = readInt("请选择 (1-3): ");

        std::string name = readString("姓名: ");
        int age = readInt("年龄: ");
        int id = readInt("学号: ");
        std::string gender = readString("性别: ");

        bool success = false;
        switch (type) {
            case 1: {
                std::string major = readString("专业: ");
                int year = readInt("年级: ");
                success = manager.addUndergraduate(name, age, id, gender, major, year);
                break;
            }
            case 2: {
                std::string area = readString("研究方向: ");
                std::string advisor = readString("导师: ");
                std::string degreeType = readString("学位类型 (学硕/专硕): ");
                success = manager.addMaster(name, age, id, gender, area, advisor, degreeType);
                break;
            }
            case 3: {
                std::string area = readString("研究方向: ");
                std::string advisor = readString("导师: ");
                success = manager.addPhD(name, age, id, gender, area, advisor);
                break;
            }
            default:
                std::cout << "无效选择。\n";
                return;
        }
        std::cout << (success ? "添加成功！\n" : "添加失败，ID可能已存在。\n");
    }

    void cmdRemoveStudent() {
        std::cout << "\n-----删除学生-----\n";
        int id = readInt("请输入要删除的学号: ");
        if (manager.removeStudent(id)) {
            std::cout << "删除成功！\n";
        } else {
            std::cout << "删除失败，学生不存在。\n";
        }
    }

    void cmdFindStudent() {
        std::cout << "\n-----查找学生-----\n";
        std::cout << "1. 按学号查找\n";
        std::cout << "2. 按姓名查找\n";
        int choice = readInt("请选择 (1-2): ");

        if (choice == 1) {
            int id = readInt("请输入学号: ");
            Person* p = manager.findById(id);
            if (p) {
                displayStudent(p);
            } else {
                std::cout << "未找到该学生。\n";
            }
        } else if (choice == 2) {
            std::string name = readString("请输入姓名: ");
            auto results = manager.findByName(name);
            if (results.empty()) {
                std::cout << "未找到该学生。\n";
            } else {
                std::cout << "找到 " << results.size() << " 名学生:\n";
                for (auto* p : results) {
                    displayStudent(p);
                }
            }
        }
    }

    void cmdUpdateStudent() {
        std::cout << "\n-----修改学生信息-----\n";
        int id = readInt("请输入学号: ");
        Person* p = manager.findById(id);
        if (!p) {
            std::cout << "未找到该学生。\n";
            return;
        }
        displayStudent(p);

        std::cout << "\n修改项目:\n";
        std::cout << "1. 姓名\n";
        std::cout << "2. 年龄\n";
        int choice = readInt("请选择 (1-2): ");

        if (choice == 1) {
            std::string newName = readString("新姓名: ");
            if (manager.updateStudentName(id, newName)) {
                std::cout << "修改成功！\n";
            }
        } else if (choice == 2) {
            int newAge = readInt("新年龄: ");
            if (manager.updateStudentAge(id, newAge)) {
                std::cout << "修改成功！\n";
            }
        }
    }

    void cmdListStudents() {
        std::cout << "\n-----学生列表-----\n";
        std::cout << "排序方式:\n";
        std::cout << "1. 按学号\n";
        std::cout << "2. 按姓名\n";
        std::cout << "3. 按年龄\n";
        int sortBy = readInt("请选择 (1-3): ");

        std::vector<Person*> students;
        switch (sortBy) {
            case 1: students = manager.sortById(); break;
            case 2: students = manager.sortByName(); break;
            case 3: students = manager.sortByAge(); break;
            default: students = manager.getAllStudents();
        }

        if (students.empty()) {
            std::cout << "暂无学生数据。\n";
            return;
        }

        std::cout << std::left << std::setw(10) << "学号"
                  << std::setw(12) << "姓名"
                  << std::setw(6) << "年龄"
                  << std::setw(8) << "性别"
                  << std::setw(15) << "类型" << "\n";
        std::cout << std::string(51, '-') << "\n";

        for (auto* p : students) {
            std::cout << std::left << std::setw(10) << p->getId()
                      << std::setw(12) << p->getName()
                      << std::setw(6) << p->getAge()
                      << std::setw(8) << p->getGender()
                      << std::setw(15) << p->getRole() << "\n";
        }
    }

    void cmdStatistics() {
        std::cout << "\n-----统计信息-----\n";
        auto stats = manager.getStatistics();
        std::cout << "学生总数: " << stats.total << "\n";
        std::cout << "本科生: " << stats.undergrads << "\n";
        std::cout << "硕士生: " << stats.masters << "\n";
        std::cout << "博士生: " << stats.phds << "\n";

        std::cout << "\n按专业统计:\n";
        auto byMajor = manager.getCountByMajor();
        for (const auto& [major, count] : byMajor) {
            std::cout << "  " << major << ": " << count << "\n";
        }
    }

    // --------学院管理命令--------
    void cmdAddCourse() {
        std::cout << "\n-----本科生选课-----\n";
        int id = readInt("学号: ");
        std::string className = readString("课程名称: ");
        int credit = readInt("学分: ");
        int gpa = readInt("绩点: ");

        if (manager.addCourse(id, className, credit, gpa)) {
            std::cout << "选课成功！\n";
        } else {
            std::cout << "选课失败，请检查学号是否为本科生。\n";
        }
    }

    void cmdRemoveCourse() {
        std::cout << "\n-----本科生退课-----\n";
        int id = readInt("学号: ");
        std::string className = readString("课程名称: ");

        if (manager.removeCourse(id, className)) {
            std::cout << "退课成功！\n";
        } else {
            std::cout << "退课失败。\n";
        }
    }

    void cmdPublishPaper() {
        std::cout << "\n-----发表论文-----\n";
        std::cout << "1. 双人合作 (PhD + Master)\n";
        std::cout << "2. 多人合作\n";
        int choice = readInt("请选择 (1-2): ");

        std::string title = readString("论文标题: ");
        std::string journal = readString("期刊名称: ");
        int year = readInt("发表年份: ");

        if (choice == 1) {
            int phdId = readInt("博士生学号: ");
            int masterId = readInt("硕士生学号: ");
            if (manager.publishPaper(phdId, masterId, title, journal, year)) {
                std::cout << "论文发表成功！\n";
            } else {
                std::cout << "发表失败，请检查学号。\n";
            }
        } else {
            std::string idsStr = readString("输入所有作者学号 (空格分隔): ");
            std::vector<int> authorIds;
            std::istringstream iss(idsStr);
            int id;
            while (iss >> id) {
                authorIds.push_back(id);
            }
            if (manager.createCollaborativePublication(authorIds, title, journal, year)) {
                std::cout << "论文发表成功！\n";
            } else {
                std::cout << "发表失败。\n";
            }
        }
    }

    void cmdCheckGraduation() {
        std::cout << "\n-----毕业资格检查-----\n";
        int id = readInt("请输入学号: ");
        Person* p = manager.findById(id);
        if (!p) {
            std::cout << "未找到该学生。\n";
            return;
        }

        displayStudent(p);
        bool eligible = manager.checkGraduationEligibility(id);
        std::cout << "\n毕业资格: " << (eligible ? "符合条件" : "不符合条件") << "\n";
    }

    void cmdFindByAdvisor() {
        std::cout << "\n-----按导师查找-----\n";
        std::string advisor = readString("导师姓名: ");
        auto results = manager.findByAdvisor(advisor);
        if (results.empty()) {
            std::cout << "未找到该导师的学生。\n";
        } else {
            std::cout << "找到 " << results.size() << " 名学生:\n";
            for (auto* g : results) {
                displayStudent(g);
            }
        }
    }

    void cmdFindByResearchArea() {
        std::cout << "\n-----按研究方向查找-----\n";
        std::string area = readString("研究方向: ");
        auto results = manager.findByResearchArea(area);
        if (results.empty()) {
            std::cout << "未找到该研究方向的学生。\n";
        } else {
            std::cout << "找到 " << results.size() << " 名学生:\n";
            for (auto* g : results) {
                displayStudent(g);
            }
        }
    }

    // ------系统设置命令------
    void cmdSave() {
        if (manager.saveAll()) {
            std::cout << "保存成功！\n";
        } else {
            std::cout << "保存失败。\n";
        }
    }

    void cmdLoad() {
        if (manager.loadAll()) {
            std::cout << "加载成功！\n";
        } else {
            std::cout << "加载失败，文件可能不存在。\n";
        }
    }

    void cmdSetWorkingDir() {
        std::cout << "当前工作目录: " << (manager.getPWD().empty() ? "(默认)" : manager.getPWD()) << "\n";
        std::string pwd = readString("新工作目录 (留空保持不变): ");
        if (!pwd.empty()) {
            manager.setPWD(pwd);
            std::cout << "工作目录已设置为: " << pwd << "\n";
        }
    }

    void cmdSettings() {
        std::cout << "\n-----系统设置-----\n";
        int credit = readInt("本科生毕业所需学分: ");
        int masterPub = readInt("硕士生毕业所需论文数: ");
        int phdPub = readInt("博士生毕业所需论文数: ");
        manager.initSettings(credit, masterPub, phdPub);
        std::cout << "设置已更新！\n";
    }

    // --------主菜单--------
    void showMainMenu() {
        std::cout << "\n-----学生信息管理系统-----\n\n";
        std::cout << "[学生管理]\n";
        std::cout << "  1. 添加学生\n";
        std::cout << "  2. 删除学生\n";
        std::cout << "  3. 查找学生\n";
        std::cout << "  4. 修改学生信息\n";
        std::cout << "  5. 学生列表\n";
        std::cout << "  6. 统计信息\n\n";
        std::cout << "[学院管理]\n";
        std::cout << "  7. 本科生选课\n";
        std::cout << "  8. 本科生退课\n";
        std::cout << "  9. 发表论文\n";
        std::cout << " 10. 毕业资格检查\n";
        std::cout << " 11. 按导师查找\n";
        std::cout << " 12. 按研究方向查找\n\n";
        std::cout << "[系统设置]\n";
        std::cout << " 13. 保存数据\n";
        std::cout << " 14. 加载数据\n";
        std::cout << " 15. 设置工作目录\n";
        std::cout << " 16. 毕业要求设置\n";
        std::cout << "  0. 退出系统\n\n";
    }

    void processCommand(int cmd) {
        switch (cmd) {
            // 学生管理
            case 1: cmdAddStudent(); break;
            case 2: cmdRemoveStudent(); break;
            case 3: cmdFindStudent(); break;
            case 4: cmdUpdateStudent(); break;
            case 5: cmdListStudents(); break;
            case 6: cmdStatistics(); break;
            // 学院管理
            case 7: cmdAddCourse(); break;
            case 8: cmdRemoveCourse(); break;
            case 9: cmdPublishPaper(); break;
            case 10: cmdCheckGraduation(); break;
            case 11: cmdFindByAdvisor(); break;
            case 12: cmdFindByResearchArea(); break;
            // 系统设置
            case 13: cmdSave(); break;
            case 14: cmdLoad(); break;
            case 15: cmdSetWorkingDir(); break;
            case 16: cmdSettings(); break;
            case 0:
                std::cout << "是否保存数据？(y/n): ";
                char c;
                std::cin >> c;
                clearInput();
                if (c == 'y' || c == 'Y') {
                    cmdSave();
                }
                std::cout << "再见！\n";
                running = false;
                break;
            default:
                std::cout << "无效选项，请重新输入。\n";
        }
    }

public:
    explicit CLI(Manager& mgr) : manager(mgr), running(true) {}

    void run() {
        std::cout << "欢迎使用学生信息管理系统！\n";
        if (manager.loadAll()) {
            std::cout << "已加载保存的数据。\n";
        }

        // char c;
        // std::cin >> c;
        // clearInput();
        // if (c == 'y' || c == 'Y') {
        //     cmdLoad();
        // }

        while (running) {
            showMainMenu();
            int cmd = readInt("请输入选项: ");
            processCommand(cmd);
        }
    }
};

#endif
