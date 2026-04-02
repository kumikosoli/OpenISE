// StudentManager.h
#ifndef STUDENT_MANAGER_H
#define STUDENT_MANAGER_H

#include <map>
#include <memory>
#include <vector>
#include <string>
#include <stdexcept>
#include "person.h"
#include "undergraduate.h"
#include "master.h"
#include "phd.h"

class Manager {
private:
    // 主要存储：使用 map 按 ID 索引
    std::map<int, std::unique_ptr<Person>> students;
    static int ungraCreditToGraduate;
    static int masterPubToGraduate;
    static int phdPubToGraduate;
    std::string workingDir;  // 工作目录
    Undergraduate* findUndergraduateById(int id);
    Master* findMasterById(int id);
    PhD* findPhDById(int id);
public:
    Manager(int creditToGraduate, int masterPubReq, int phdPubReq);
    ~Manager();
    
    // 禁止拷贝
    Manager(const Manager&) = delete;
    Manager& operator=(const Manager&) = delete;
    

    // ------学生管理--------
    // 基本增删改查功能
    bool addUndergraduate(const std::string& name, int age, int id, 
                         const std::string& gender, const std::string& major, 
                         int year);
    
    bool addMaster(const std::string& name, int age, int id, 
                   const std::string& gender, const std::string& researchArea,
                   const std::string& advisor, const std::string& degreeType);
    
    bool addPhD(const std::string& name, int age, int id, 
                const std::string& gender, const std::string& researchArea,
                const std::string& advisor);
    
    bool removeStudent(int id);
    
    // 根据 ID 查找学生，ID唯一
    Person* findById(int id);
    Person* findById(int id) const;
    // 查找名字支持多个同名学生
    std::vector<Person*> findByName(const std::string& name);
    // 修改学生信息
    bool updateStudentName(int id, const std::string& newName);
    bool updateStudentAge(int id, int newAge);
    
    
    std::vector<Person*> getAllStudents();
    
    // 按角色获取学生
    std::vector<Person*> getStudentsByRole(const std::string& role);
    size_t getTotalCount() const { return students.size(); }
    std::map<std::string, int> getCountByMajor() const;
    

    std::map<int, int> getCountByAge() const;
    struct StudentStats {
        int total;
        int undergrads;
        int masters;
        int phds;
    };
    StudentStats getStatistics() const;
    
    // 排序
    std::vector<Person*> sortById(bool ascending = true);
    std::vector<Person*> sortByName(bool ascending = true);
    std::vector<Person*> sortByAge(bool ascending = true);
    
    // 研究生特殊功能
    bool addPublicationToGraduate(int id, const Publication& pub);
    std::vector<Graduate*> findByResearchArea(const std::string& area);
    std::vector<Graduate*> findByAdvisor(const std::string& advisor);
    
    // 保存/读取所有学生到 JSON 文件
    bool saveToFile(const std::string& filename) const;
    bool loadFromFile(const std::string& filename);
    nlohmann::json toJson() const;
    void fromJson(const nlohmann::json& j);
    
    // 数据验证
    bool isIdExists(int id) const;
    static bool isValidId(int id);
    static bool isValidAge(int age);

    // -----学院管理-----
    // 本科生选课&退课
    bool addCourse(int id, const std::string& className, int credit, int gpa);
    bool removeCourse(int id, const std::string& className);

    // 研究生发表论文
    bool publishPaper(int phdId, int masterId, const std::string& title, 
                      const std::string& journal, int year);
    bool createCollaborativePublication(
        const std::vector<int>& authorIds,
        const std::string& title,
        const std::string& journal,
        int year
    );
    bool checkGraduationEligibility(int id) const;

    // -----系统设置-------
    bool saveAll();
    bool loadAll();
    void setPWD(const std::string& pwd);
    std::string getPWD() const { return workingDir; }
    void initSettings(int creditToGraduate, int masterPubReq, int phdPubReq);
};

#endif