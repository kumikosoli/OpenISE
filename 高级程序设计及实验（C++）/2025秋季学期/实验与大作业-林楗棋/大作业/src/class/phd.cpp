#include "phd.h"
#include "master.h"
#include "publication.h"

// 为博士生和硕士生添加联合发表的论文
void addPublication(PhD& phd, Master& master, const std::string& title, const std::string& journal, int year) {
    Publication pub(title, journal, year);
    pub.addAuthor(phd.getName(), phd.getId(), phd.getRole());
    pub.addAuthor(master.getName(), master.getId(), master.getRole());
    phd.addPublication(pub); 
    master.addPublication(pub);
}