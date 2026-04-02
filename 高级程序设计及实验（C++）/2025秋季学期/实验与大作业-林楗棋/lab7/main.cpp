#include "NameList.h"
#include <gtest/gtest.h>
#include <fstream>
#include <iostream>

TEST(NameList, InitAndPrint) {
    std::ifstream afile;
    afile.open("names.txt");
    if (!afile.is_open()) {
        std::cerr << "Failed to open names.txt" << std::endl;
    }
    std::string name;
    std::getline(afile, name);
    NameList namelist(name);
    while (std::getline(afile, name)) {
        namelist.addName(name);
    }
    afile.close();
    NameList namelist2 = namelist; //测试拷贝构造函数
    NameList namelist3(namelist); 
    testing::internal::CaptureStdout();
    namelist.print(0);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("Zhang san Li si Wang wu Xiao hong Da zhuang Qi qi \n", output);
    testing::internal::CaptureStdout();
    namelist2.print(1);
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("Da zhuang Li si Qi qi Wang wu Xiao hong Zhang san \n", output);
    testing::internal::CaptureStdout();
    namelist3.print(2); 
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("Zhang san Xiao hong Wang wu Qi qi Li si Da zhuang \n", output);
}


TEST(NameList, AddDeleteSearch) {       
    std::ifstream afile;
    afile.open("names.txt");
    if (!afile.is_open()) {
        std::cerr << "Failed to open names.txt" << std::endl;
    }
    std::string name;
    std::getline(afile, name);
    NameList namelist(name);
    while (std::getline(afile, name)) {
        namelist.addName(name);
    }
    afile.close();
    namelist.deleteName("Li si");
    std::vector<std::string> names = namelist.getNames();
    std::vector<std::string> expected_names = {"Zhang san", "Wang wu", "Xiao hong", "Da zhuang", "Qi qi"};
    EXPECT_EQ(names, expected_names);
    namelist.addName("Xiao ming");
    std::vector<std::string> updated_names = namelist.getNames();
    std::vector<std::string> expected_updated_names = {"Zhang san", "Wang wu", "Xiao hong", "Da zhuang", "Qi qi", "Xiao ming"};
    EXPECT_EQ(updated_names, expected_updated_names);
    std::vector<std::string> search_result = namelist.search("an");
    std::vector<std::string> expected_search_result = {"Zhang san", "Wang wu", "Da zhuang"};
    EXPECT_EQ(search_result, expected_search_result);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


// int main() {
//     std::ifstream afile;
//     afile.open("names.txt");
//     if (!afile.is_open()) {
//         std::cerr << "Failed to open names.txt" << std::endl;
//         return 1;
//     }
//     std::string name;
//     std::getline(afile, name);
//     NameList namelist(name);
//     while (std::getline(afile, name)) {
//         namelist.addName(name);
//     }
//     afile.close();
//     namelist.print(0);
//     namelist.print(1);
//     namelist.print(2);
//     return 0;
// }