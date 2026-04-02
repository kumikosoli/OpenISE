#include "publication.h"

// 序列化为JSON
nlohmann::json Publication::toJson() const {
    nlohmann::json j;
    j["title"] = title;
    j["journal"] = journal;
    j["year"] = year;
    // 只保存作者id，避免交叉引用时数据冗余
    j["authorIds"] = nlohmann::json::array();
    for (const auto& author : authors) {
        j["authorIds"].push_back(author.id);
    }
    return j;
}