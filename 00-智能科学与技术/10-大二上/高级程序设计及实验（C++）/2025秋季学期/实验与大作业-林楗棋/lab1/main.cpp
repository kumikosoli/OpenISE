#include <gtest/gtest.h>
#include "src/complex.h"
#include "src/matrix.h"

// Complex 测试
TEST(ComplexTest, Add) {
    Complex a(1, 2), b(3, 4);
    a.add(b);
    auto [r, i] = a.show();
    EXPECT_FLOAT_EQ(r, 4.0f);
    EXPECT_FLOAT_EQ(i, 6.0f);
}

TEST(ComplexTest, Mul) {
    Complex a(1, 2), b(3, 4);
    a.add(b);  // a -> (4,6)
    auto [mr, mi] = mul(b, a);
    EXPECT_FLOAT_EQ(mr, -12.0f);
    EXPECT_FLOAT_EQ(mi, 34.0f);
}

TEST(ComplexTest, Div) {
    Complex c(1, 2), d(2, 0);
    auto [dr, di] = div(c, d);
    EXPECT_FLOAT_EQ(dr, 0.5f);
    EXPECT_FLOAT_EQ(di, 1.0f);
}

TEST(ComplexTest, AbsAndCount) {
    int before = Complex::getCount();
    Complex c(3, 4);
    EXPECT_FLOAT_EQ(c.getAbs(), 5.0f);
    EXPECT_GE(Complex::getCount(), before + 1);
}

// Matrix 测试
TEST(MatrixTest, AddAndAccess) {
    std::vector<std::vector<float>> d1 = {{1, 2}, {3, 4}};
    std::vector<std::vector<float>> d2 = {{5, 6}, {7, 8}};
    Matrix m1(2, 2, d1), m2(2, 2, d2);

    m1.add(m2);
    auto [rows, cols] = m1.size();
    EXPECT_EQ(rows, 2);
    EXPECT_EQ(cols, 2);

    auto row0 = m1.getLine(0);
    ASSERT_EQ(row0.size(), 2u);
    EXPECT_FLOAT_EQ(row0[0], 6.0f);
    EXPECT_FLOAT_EQ(row0[1], 8.0f);

    auto col1 = m1.getColumn(1);
    ASSERT_EQ(col1.size(), 2u);
    EXPECT_FLOAT_EQ(col1[0], 8.0f);
    EXPECT_FLOAT_EQ(col1[1], 12.0f);
}

TEST(MatrixTest, Mul) {
    std::vector<std::vector<float>> d1 = {{1, 2}, {3, 4}};
    std::vector<std::vector<float>> d2 = {{5, 6}, {7, 8}};
    Matrix m3(2, 2, d1), m4(2, 2, d2);

    auto C = mul(m3, m4);  // [[19,22],[43,50]]
    ASSERT_EQ(C.size(), 2u);
    ASSERT_EQ(C[0].size(), 2u);
    EXPECT_FLOAT_EQ(C[0][0], 19.0f);
    EXPECT_FLOAT_EQ(C[0][1], 22.0f);
    EXPECT_FLOAT_EQ(C[1][0], 43.0f);
    EXPECT_FLOAT_EQ(C[1][1], 50.0f);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
