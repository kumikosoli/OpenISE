#include "fileprocessing.h"
#include <gtest/gtest.h>
#include <fstream>
#include <string>
#include <vector>

namespace {
std::string WriteFile(const std::string& filename, const std::string& content) {
    std::ofstream out(filename);
    out << content;
    out.close();
    return filename;
}

std::vector<std::string> ReadLines(const std::string& filename) {
    std::ifstream in(filename);
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(in, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        lines.push_back(line);
    }
    return lines;
}
} // namespace

TEST(FileProcessing, LoadAndCount) {
    std::string filename = WriteFile("gtest_input.txt", "apple banana apple\nbanana cherry\n");
    FileProcessing fp(filename);
    EXPECT_TRUE(fp.IsWordAppear("apple"));
    EXPECT_FALSE(fp.IsWordAppear("orange"));
    EXPECT_EQ(fp.CountWordOccurrences("apple"), 2);
    EXPECT_EQ(fp.CountWordOccurrences("banana"), 2);
    EXPECT_EQ(fp.CountWordOccurrences("cherry"), 1);
}

TEST(FileProcessing, AddNewWordAndSave) {
    std::string filename = WriteFile("gtest_input2.txt", "apple banana apple\nbanana cherry\n");
    FileProcessing fp(filename);
    fp.AddNewWord("date", 2, 3);
    testing::internal::CaptureStderr();
    fp.AddNewWord("date", 2, 5);
    std::string err = testing::internal::GetCapturedStderr();
    EXPECT_EQ(err, "输入位置非法\n");
    EXPECT_EQ(fp.CountWordOccurrences("date"), 1);

    std::string outFile = "gtest_output2.txt";
    fp.SaveToFile(outFile);
    std::vector<std::string> lines = ReadLines(outFile);
    std::vector<std::string> expected = {
        "apple 1 1",
        "apple 1 3",
        "banana 1 2",
        "banana 2 1",
        "cherry 2 2",
        "date 2 3",
    };
    EXPECT_EQ(lines, expected);
}

TEST(FileProcessing, DeleteWordShiftsPositions) {
    std::string filename = WriteFile("gtest_input3.txt", "apple banana apple\nbanana cherry\n");
    FileProcessing fp(filename);
    fp.DeleteWord("banana");

    std::string outFile = "gtest_output3.txt";
    fp.SaveToFile(outFile);
    std::vector<std::string> lines = ReadLines(outFile);
    std::vector<std::string> expected = {
        "apple 1 1",
        "apple 1 2",
        "cherry 2 1",
    };
    EXPECT_EQ(lines, expected);
}

TEST(FileProcessing, PrintWordsAscend) {
    std::string filename = WriteFile("gtest_input4.txt", "banana apple cherry\n");
    FileProcessing fp(filename);
    testing::internal::CaptureStdout();
    fp.PrintWordsAscend();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("apple banana cherry \n", output);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
