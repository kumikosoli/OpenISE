#include <gtest/gtest.h>
#include "matrix.h"

TEST(MatrixTest, AddAndAccess) {
    float** d1 = new float*[2];
    d1[0] = new float[2]{1, 2};
    d1[1] = new float[2]{3, 4};
    float** d2 = new float*[2];
    d2[0] = new float[2]{5, 6};
    d2[1] = new float[2]{7, 8};
    Matrix m1(2, 2, d1);
    Matrix m2(2, 2, d2);
    
    m1.add(m2);
    float* row0 = m1.getl(0);
    EXPECT_FLOAT_EQ(row0[0], 6.0f);
    EXPECT_FLOAT_EQ(row0[1], 8.0f);
    delete[] row0;

    float* col1 = m1.getc(1);
    EXPECT_FLOAT_EQ(col1[0], 8.0f);
    EXPECT_FLOAT_EQ(col1[1], 12.0f);
    delete[] col1;
}

TEST(MatrixTest, Sub) {
    float** d1 = new float*[2];
    d1[0] = new float[2]{5, 6};
    d1[1] = new float[2]{7, 8};
    Matrix m1(2, 2, d1);
    Matrix m2(2, 2);

    m2.sub(m1);
    float* row0 = m2.getl(0);
    EXPECT_FLOAT_EQ(row0[0], -5.0f);
    EXPECT_FLOAT_EQ(row0[1], -6.0f);
    delete[] row0;
}

TEST(MatrixTest, InitAndOpertaor) {
    float** d1 = new float*[2];
    d1[0] = new float[2]{1, 2};
    d1[1] = new float[2]{3, 4};
    float** d2 = new float*[2];
    d2[0] = new float[2]{5, 6};
    d2[1] = new float[2]{7, 8};
    
    Matrix m1(2, 2, d1);
    Matrix m2(2, 2, d2);
    Matrix m3 = m1;
    Matrix m4(m2);

    Matrix re1 = m1 + m2;
    EXPECT_FLOAT_EQ(re1.getl(0)[0], 6.0f);
    EXPECT_FLOAT_EQ(re1.getl(0)[1], 8.0f);

    Matrix re2 = m1 - m2;
    EXPECT_FLOAT_EQ(re2.getl(0)[0], -4.0f);
    EXPECT_FLOAT_EQ(re2.getl(0)[1], -4.0f);

    m1.sub(m2);
    m2.add(m3); // 打乱两者内容

    Matrix re3 = m3 * m4;
    EXPECT_FLOAT_EQ(re3.getl(0)[0], 19.0f);
    EXPECT_FLOAT_EQ(re3.getl(0)[1], 22.0f);
}

TEST(MatrixTest, SizeAndElements) {
    float** d1 = new float*[2];
    d1[0] = new float[2]{1, 2};
    d1[1] = new float[2]{3, 4};
    Matrix m1(2, 2, d1);
    
    EXPECT_EQ(m1.nElements(), 4);
    EXPECT_EQ(m1.size(), 16);
}

TEST(MatrixTest, SetAndGet) {
    float** d1 = new float*[2];
    d1[0] = new float[2]{1, 2};
    d1[1] = new float[2]{3, 4};
    Matrix m(2, 2, d1);
    EXPECT_FLOAT_EQ(1.0, m.get(0, 0));
    m.set(0, 0, 5.0);
    EXPECT_FLOAT_EQ(5.0, m.get(0, 0));
}

TEST(MatrixTest, Error) {
    float** d1 = new float*[2];
    d1[0] = new float[2]{1, 2};
    d1[1] = new float[2]{3, 4};
    Matrix m1(2, 2, d1);
    Matrix m2(3, 3);

    // 测试加法错误
    m1.add(m2);
    
    // 测试减法错误
    m1.sub(m2);
    
    // 测试乘法错误
    m1 * m2;
    
    // 测试获取行和列错误
    m1.getl(3);
    m1.getc(3);
    // 测试显示矩阵
    m1.display();
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
