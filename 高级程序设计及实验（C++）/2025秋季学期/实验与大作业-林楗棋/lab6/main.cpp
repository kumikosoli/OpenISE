#include <gtest/gtest.h>
#include "utils.h"

TEST(StringFilter, test) {
	std::string out;
	stringFilter("deefd", out);
	EXPECT_EQ(out, "def");

	stringFilter("afafafaf", out);
	EXPECT_EQ(out, "af");

	stringFilter("pppppppp", out);
	EXPECT_EQ(out, "p");
}

TEST(StringZip, test) {
	std::string out;
	stringZip("cccddecc", out);
	EXPECT_EQ(out, "3c2de2c");

	stringZip("adef", out);
	EXPECT_EQ(out, "adef");

	stringZip("pppppppp", out);
	EXPECT_EQ(out, "8p");
}

TEST(StringUnzip, test) {
	std::string out;
	stringUnzip("8p", out);
	EXPECT_EQ(out, std::string(8, 'p'));

	stringUnzip("3c2de2c", out);
	EXPECT_EQ(out, "cccddecc");

	stringUnzip("12x3y", out);
	EXPECT_EQ(out, std::string(12, 'x') + std::string(3, 'y'));
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

// int main() {
//     std::string out;
//     stringFilter("deefd", out); 
//     std::cout << out << std::endl;
//     stringFilter("afafafaf", out);
//     std::cout << out << std::endl;
// 	stringFilter("pppppppp", out);
//     std::cout << out <<std::endl;
// }
