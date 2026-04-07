#include "manager.h"
#include "undergraduate.h"
#include "master.h"
#include "phd.h"
#include "publication.h"
#include "person.h"
#include <iostream>
#include <fstream>

// 静态成员定义
int Manager::ungraCreditToGraduate = 0;
int Manager::masterPubToGraduate = 0;
int Manager::phdPubToGraduate = 0;

// 构造与析构与静态成员初始化
Manager::Manager(int creditToGraduate, int masterPubReq, int phdPubReq) {
    ungraCreditToGraduate = creditToGraduate;
    masterPubToGraduate = masterPubReq;
    phdPubToGraduate = phdPubReq;
}

Manager::~Manager() {
    students.clear();
}

// 助手函数：根据 ID 查找特定类型学生
Undergraduate* Manager::findUndergraduateById(int id) {
    Person* p = findById(id);
    if (p && p->getRole() == "Undergraduate") {
        return dynamic_cast<Undergraduate*>(p);
    }
    return nullptr;
}

Master* Manager::findMasterById(int id) {
    Person* p = findById(id);
    if (p && p->getRole() == "Master") {
        return dynamic_cast<Master*>(p);
    }
    return nullptr;
}

PhD* Manager::findPhDById(int id) {
    Person* p = findById(id);
    if (p && p->getRole() == "PhD") {
        return dynamic_cast<PhD*>(p);
    }
    return nullptr;
}


// 增删改查

bool Manager::addUndergraduate(const std::string& name, int age, int id,
                              const std::string& gender, const std::string& major,
                              int year) {
    if (isIdExists(id) || !isValidId(id) || !isValidAge(age)) {
        return false;
    }
    students[id] = std::make_unique<Undergraduate>(name, age, id, gender, major, year);
    return true;
}

bool Manager::addMaster(const std::string& name, int age, int id,
                        const std::string& gender, const std::string& researchArea,
                        const std::string& advisor, const std::string& degreeType) {
    if (isIdExists(id) || !isValidId(id) || !isValidAge(age)) {
        return false;
    }
    students[id] = std::make_unique<Master>(name, age, id, gender, researchArea, advisor, degreeType);
    return true;
}

bool Manager::addPhD(const std::string& name, int age, int id,
                     const std::string& gender, const std::string& researchArea,
                        const std::string& advisor) {
    if (isIdExists(id) || !isValidId(id) || !isValidAge(age)) {
        return false;
    }
    students[id] =  std::make_unique<PhD>(name, age, id, gender, researchArea, advisor);
    return true;
}

bool Manager::removeStudent(int id) {
    return students.erase(id) > 0;
}
// 根据 ID 查找学生，ID唯一
Person* Manager::findById(int id) {
    auto it = students.find(id);
    if (it != students.end()) {
        return it->second.get();
    }
    return nullptr;
}
// 静态，支持静态函数调用
Person* Manager::findById(int id) const {
    auto it = students.find(id);
    if (it != students.end()) {
        return it->second.get();
    }
    return nullptr;
}  
// 查找名字支持多个同名学生
std::vector<Person*> Manager::findByName(const std::string& name) {
    std::vector<Person*> result;
    for (const auto& [id, studentPtr] : students) {
        if (studentPtr->getName() == name) {
            result.push_back(studentPtr.get());
        }
    }
    return result;
}

// 修改学生信息
bool Manager::updateStudentName(int id, const std::string& newName) {
    Person* student = findById(id);
    if (student) {
        student->setName(newName);
        return true;
    }
    return false;
}
bool Manager::updateStudentAge(int id, int newAge) {
    Person* student = findById(id);
    if (student && isValidAge(newAge)) {
        student->setAge(newAge);
        return true;
    }
    return false;
}

std::vector<Person*> Manager::getAllStudents() {
    std::vector<Person*> result;
    for (const auto& [id, studentPtr] : students) {
        result.push_back(studentPtr.get());
    }
    return result;
}

// 按角色获取学生
std::vector<Person*> Manager::getStudentsByRole(const std::string& role) {
    std::vector<Person*> result;
    for (const auto& [id, studentPtr] : students) {
        if (studentPtr->getRole() == role) {
            result.push_back(studentPtr.get());
        }
    }
    return result;
}

std::map<std::string, int> Manager::getCountByMajor() const {
    std::map<std::string, int> majorCount;
    for (const auto& [id, studentPtr] : students) {
        if (studentPtr->getRole() == "Undergraduate") {
            Undergraduate* ug = dynamic_cast<Undergraduate*>(studentPtr.get());
            if (ug) {
                majorCount[ug->getMajor()]++;
            }
        }
    }
    return majorCount;
}

std::map<int, int> Manager::getCountByAge() const {
    std::map<int, int> ageCount;
    for (const auto& [id, studentPtr] : students) {
        ageCount[studentPtr->getAge()]++;
    }
    return ageCount;
}

Manager::StudentStats Manager::getStatistics() const {
    StudentStats stats{0, 0, 0, 0};
    stats.total = students.size();
    for (const auto& [id, studentPtr] : students) {
        if (studentPtr->getRole() == "Undergraduate") {
            stats.undergrads++;
        } else if (studentPtr->getRole() == "Master") {
            stats.masters++;
        } else if (studentPtr->getRole() == "PhD") {
            stats.phds++;
        }
    }
    return stats;
}

// 排序，运用lambda表达式
std::vector<Person*> Manager::sortById(bool ascending) {
    std::vector<Person*> result = getAllStudents();
    if (ascending) {
        std::sort(result.begin(), result.end(), [](Person* a, Person* b) { return a->getId() < b->getId(); });
    } else {
        std::sort(result.begin(), result.end(), [](Person* a, Person* b) { return a->getId() > b->getId(); });
    }
    return result;
}

std::vector<Person*> Manager::sortByName(bool ascending) {
    std::vector<Person*> result = getAllStudents();
    if (ascending) {
        std::sort(result.begin(), result.end(), [](Person* a, Person* b) { return a->getName() < b->getName(); });
    } else {
        std::sort(result.begin(), result.end(), [](Person* a, Person* b) { return a->getName() > b->getName(); });
    }
    return result;
}

std::vector<Person*> Manager::sortByAge(bool ascending) {
    std::vector<Person*> result = getAllStudents();
    if (ascending) {
        std::sort(result.begin(), result.end(), [](Person* a, Person* b) { return a->getAge() < b->getAge(); });
    } else {
        std::sort(result.begin(), result.end(), [](Person* a, Person* b) { return a->getAge() > b->getAge(); });
    }
    return result;
}

// 研究生特殊功能
bool Manager::addPublicationToGraduate(int id, const Publication& pub) {
    Person* student = findById(id);
    if (!student) return false;

    Graduate* grad = dynamic_cast<Graduate*>(student);
    if (!grad) return false;

    if (grad->getRole() == "Master") {
        Master* master = dynamic_cast<Master*>(grad);
        if (master) {
            master->addPublication(pub);
            return true;
        }
    } else if (grad->getRole() == "PhD") {
        PhD* phd = dynamic_cast<PhD*>(grad);
        if (phd) {
            phd->addPublication(pub);
            return true;
        }
    }
    return false;
}

std::vector<Graduate*> Manager::findByResearchArea(const std::string& area) {
    std::vector<Graduate*> result;
    for (const auto& [id, studentPtr] : students) {
        Graduate* grad = dynamic_cast<Graduate*>(studentPtr.get());
        if (grad && grad->getResearchArea() == area) {
            result.push_back(grad);
        }
    }
    return result;
}

std::vector<Graduate*> Manager::findByAdvisor(const std::string& advisor) {
    std::vector<Graduate*> result;
    for (const auto& [id, studentPtr] : students) {
        Graduate* grad = dynamic_cast<Graduate*>(studentPtr.get());
        if (grad && grad->getAdvisor() == advisor) {
            result.push_back(grad);
        }
    }
    return result;
}

// 保存/读取所有学生到 JSON 文件
bool Manager::saveToFile(const std::string& filename) const {
    nlohmann::json j = toJson();
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    file << j.dump(4);
    file.close();
    return true;
}

bool Manager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    nlohmann::json j;
    file >> j;
    fromJson(j);
    file.close();
    return true;
}

nlohmann::json Manager::toJson() const {
    nlohmann::json j;
    // 保存系统设置
    j["settings"]["ungraCreditToGraduate"] = ungraCreditToGraduate;
    j["settings"]["masterPubToGraduate"] = masterPubToGraduate;
    j["settings"]["phdPubToGraduate"] = phdPubToGraduate;
    // 保存学生数据
    j["students"] = nlohmann::json::array();
    for (const auto& [id, studentPtr] : students) {
        j["students"].push_back(studentPtr->toJson());
    }
    return j;
}

void Manager::fromJson(const nlohmann::json& j) {
    // 加载系统设置
    if (j.contains("settings")) {
        const auto& settings = j["settings"];
        if (settings.contains("ungraCreditToGraduate")) {
            ungraCreditToGraduate = settings["ungraCreditToGraduate"];
        }
        if (settings.contains("masterPubToGraduate")) {
            masterPubToGraduate = settings["masterPubToGraduate"];
        }
        if (settings.contains("phdPubToGraduate")) {
            phdPubToGraduate = settings["phdPubToGraduate"];
        }
    }
    students.clear();
    // 第一遍：创建所有学生对象（基本信息）
    for (const auto& item : j["students"]) {
        std::string role = item["role"];
        if (role == "Undergraduate") {
            auto ug = std::make_unique<Undergraduate>(
                item["name"], item["age"], item["id"], item["gender"],
                item["major"], item["year"]);
            students[ug->getId()] = std::move(ug);
        } else if (role == "Master") {
            auto master = std::make_unique<Master>(
                item["name"], item["age"], item["id"], item["gender"],
                item["researchArea"], item["advisor"], item["degreeType"]);
            students[master->getId()] = std::move(master);
        } else if (role == "PhD") {
            auto phd = std::make_unique<PhD>(
                item["name"], item["age"], item["id"], item["gender"],
                item["researchArea"], item["advisor"]);
            students[phd->getId()] = std::move(phd);
        }
    }
    // 第二遍：恢复 classInfos 和 publications
    for (const auto& item : j["students"]) {
        std::string role = item["role"];
        int id = item["id"];
        Person* person = findById(id);
        if (!person) continue;

        if (role == "Undergraduate") {
            Undergraduate* ug = dynamic_cast<Undergraduate*>(person);
            if (ug && item.contains("classInfo")) {
                for (const auto& ci : item["classInfo"]) {
                    ug->addClassInfo(ci["className"], ci["credit"], ci["gpa"]);
                }
            }
        } else if (role == "Master") {
            Master* master = dynamic_cast<Master*>(person);
            if (master && item.contains("publications")) {
                for (const auto& pubJson : item["publications"]) {
                    Publication pub(pubJson["title"], pubJson["journal"], pubJson["year"]);
                    // 根据 authorIds 恢复作者信息
                    if (pubJson.contains("authorIds")) {
                        for (int authorId : pubJson["authorIds"]) {
                            Person* author = findById(authorId);
                            if (author) {
                                pub.addAuthor(author->getName(), author->getId(), author->getRole());
                            }
                        }
                    }
                    master->addPublication(pub);
                }
            }
        } else if (role == "PhD") {
            PhD* phd = dynamic_cast<PhD*>(person);
            if (phd && item.contains("publications")) {
                for (const auto& pubJson : item["publications"]) {
                    Publication pub(pubJson["title"], pubJson["journal"], pubJson["year"]);
                    // 根据 authorIds 恢复作者信息
                    if (pubJson.contains("authorIds")) {
                        for (int authorId : pubJson["authorIds"]) {
                            Person* author = findById(authorId);
                            if (author) {
                                pub.addAuthor(author->getName(), author->getId(), author->getRole());
                            }
                        }
                    }
                    phd->addPublication(pub);
                }
            }
        }
    }
}

// 数据验证
bool Manager::isIdExists(int id) const {
    return students.find(id) != students.end();
}

bool Manager::isValidId(int id) {
    return id > 0;
}

bool Manager::isValidAge(int age) {
    return age >= 18 && age <= 100;
}

// -----学院管理-----
// 本科生选课&退课
bool Manager::addCourse(int id, const std::string& className, int credit, int gpa) {
    Undergraduate* ug = findUndergraduateById(id);
    if (!ug) return false;
    ug->addClassInfo(className, credit, gpa);
    return true;
}

bool Manager::removeCourse(int id, const std::string& className) {
    Undergraduate* ug = findUndergraduateById(id);
    if (!ug) return false;
    auto classInfos = ug->getClassInfos();
    for (auto it = classInfos.begin(); it != classInfos.end(); ++it) {
        if (it->className == className) {
            classInfos.erase(it);
            return true;
        }
    }
    return false;
}

// 研究生发表论文
bool Manager::publishPaper(int phdId, int masterId, const std::string& title,
                           const std::string& journal, int year) {
    PhD* phd = findPhDById(phdId);
    Master* master = findMasterById(masterId);
    if (!phd || !master) return false;
    Publication pub(title, journal, year);
    pub.addAuthor(phd->getName(), phd->getId(), "PhD");
    pub.addAuthor(master->getName(), master->getId(), "Master");
    phd->addPublication(pub);
    master->addPublication(pub);
    return true;
}

bool Manager::createCollaborativePublication(
    const std::vector<int>& authorIds,
    const std::string& title,
    const std::string& journal,
    int year
) {
    Publication pub(title, journal, year);
    for (int id : authorIds) {
        Master* master = findMasterById(id);
        PhD* phd = findPhDById(id);
        Graduate* grad = nullptr;
        if (master) {
            grad = master;
        } else if (phd) {
            grad = phd;
        }
        if (!grad) {
            return false; // 一个作者ID无效，返回false
        }
        pub.addAuthor(grad->getName(), grad->getId(), grad->getRole());
        if (grad->getRole() == "Master") {
            Master* master = dynamic_cast<Master*>(grad);
            if (master) {
                master->addPublication(pub);
            }
        } else if (grad->getRole() == "PhD") {
            PhD* phd = dynamic_cast<PhD*>(grad);
            if (phd) {
                phd->addPublication(pub);
            }
        }
    }
    return true;
}

bool Manager::checkGraduationEligibility(int id) const {
    Person* student = this->findById(id);
    if (!student) return false;
    if (student->getRole() == "Undergraduate") {
        Undergraduate* ug = dynamic_cast<Undergraduate*>(student);
        if (ug) {
            int totalCredits = 0;
            for (const auto& ci : ug->getClassInfos()) {
                totalCredits += ci.credit;
            }
            return totalCredits >= ungraCreditToGraduate;
        }
    } else if (student->getRole() == "Master") {
        Master* master = dynamic_cast<Master*>(student);
        if (master) {
            return master->getPublications().size() >= masterPubToGraduate;
        }
    } else if (student->getRole() == "PhD") {
        PhD* phd = dynamic_cast<PhD*>(student);
        if (phd) {
            return phd->getPublications().size() >= phdPubToGraduate;
        }
    }
    return false;
}

// -----系统设置-------
bool Manager::saveAll() {
    std::string filepath = workingDir.empty() ? "students_data.json" : workingDir + "/students_data.json";
    return saveToFile(filepath);
}

bool Manager::loadAll() {
    std::string filepath = workingDir.empty() ? "students_data.json" : workingDir + "/students_data.json";
    return loadFromFile(filepath);
}

void Manager::setPWD(const std::string& pwd) {
    workingDir = pwd;
}

void Manager::initSettings(int creditToGraduate, int masterPubReq, int phdPubReq) {
    ungraCreditToGraduate = creditToGraduate;
    masterPubToGraduate = masterPubReq;
    phdPubToGraduate = phdPubReq;
}