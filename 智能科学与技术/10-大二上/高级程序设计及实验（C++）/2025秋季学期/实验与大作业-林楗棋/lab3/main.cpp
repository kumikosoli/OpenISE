#include "SparseMatrix.h"
#include "gtest/gtest.h"
#include "matrix.h"

TEST(sparseMatrix, Spare2Dense) {
    SparseMatrix sparse(3, 3);
    sparse.set(0, 0, 1.0);
    sparse.set(1, 2, 2.0);
    sparse.set(2, 1, 3.0);

    Matrix dense = sparse.toDenseMatrix();

    EXPECT_EQ(dense.get(0, 0), 1.0);
    EXPECT_EQ(dense.get(1, 2), 2.0);
    EXPECT_EQ(dense.get(2, 1), 3.0);
    EXPECT_EQ(dense.get(0, 1), 0.0);
    EXPECT_EQ(dense.get(1, 1), 0.0);
    EXPECT_EQ(dense.get(2, 2), 0.0);
}

TEST(sparseMatrix, Dense2Sparse) {
    Matrix dense(2, 2);
    dense.set(0, 0, 4.0);
    dense.set(1, 1, 5.0);

    SparseMatrix sparse = dense.toSparseMatrix();

    EXPECT_EQ(sparse.get(0, 0), 4.0);
    EXPECT_EQ(sparse.get(1, 1), 5.0);
    EXPECT_EQ(sparse.get(0, 1), 0.0);
    EXPECT_EQ(sparse.get(1, 0), 0.0);
}

TEST(sparseMatrix, Init) {
    SparseMatrix sparse(2, 3);
    EXPECT_FLOAT_EQ(sparse.get(0, 0), 0.0);
    EXPECT_FLOAT_EQ(sparse.get(1, 2), 0.0);
    sparse.set(0, 1, 7.0);
    EXPECT_FLOAT_EQ(sparse.get(0, 1), 7.0);
    SparseMatrix sparse2 (sparse);
    EXPECT_FLOAT_EQ(sparse2.get(0, 1), 7.0);
    EXPECT_FLOAT_EQ(sparse2.get(1, 1), 0.0);
    Matrix dense(2, 2);
    dense.set(0, 0, 3.0);
    dense.set(1, 1, 4.0);
    SparseMatrix sparse3(dense);
    EXPECT_FLOAT_EQ(sparse3.get(0, 0), 3.0);
    EXPECT_FLOAT_EQ(sparse3.get(1, 1), 4.0);
    EXPECT_FLOAT_EQ(sparse3.get(0, 1), 0.0);
    SparseMatrix sparse4 = sparse2;
    EXPECT_FLOAT_EQ(sparse4.get(0, 1), 7.0);
}

TEST(sparseMatrix, AdditionAndSub) {
    SparseMatrix sparse1(2, 2);
    sparse1.set(0, 0, 1.0);
    sparse1.set(1, 1, 2.0);

    SparseMatrix sparse2(2, 2);
    sparse2.set(0, 0, 3.0);
    sparse2.set(0, 1, 4.0);

    SparseMatrix result = sparse1 + sparse2;
    SparseMatrix result2 = sparse1 - sparse2;

    EXPECT_FLOAT_EQ(result.get(0, 0), 4.0);
    EXPECT_FLOAT_EQ(result.get(0, 1), 4.0);
    EXPECT_FLOAT_EQ(result.get(1, 1), 2.0);
    EXPECT_FLOAT_EQ(result.get(1, 0), 0.0);

    EXPECT_FLOAT_EQ(result2.get(0, 0), -2.0);
    EXPECT_FLOAT_EQ(result2.get(0, 1), -4.0);
    EXPECT_FLOAT_EQ(result2.get(1, 1), 2.0);
    EXPECT_FLOAT_EQ(result2.get(1, 0), 0.0);

    sparse1.sub(sparse2);
    EXPECT_FLOAT_EQ(sparse1.get(0, 0), -2.0);
    EXPECT_FLOAT_EQ(sparse1.get(0, 1), -4.0);
    EXPECT_FLOAT_EQ(sparse1.get(1, 1), 2.0);
    EXPECT_FLOAT_EQ(sparse1.get(1, 0), 0.0);

    sparse1.add(sparse2);
    EXPECT_FLOAT_EQ(sparse1.get(0, 0), 1.0);
    EXPECT_FLOAT_EQ(sparse1.get(0, 1), 0.0);
    EXPECT_FLOAT_EQ(sparse1.get(1, 1), 2.0);
    EXPECT_FLOAT_EQ(sparse1.get(1, 0), 0.0);
}

TEST(sparseMatrix, TestPrint) {
    SparseMatrix sparse(2, 2);
    sparse.set(0, 0, 1.5);
    sparse.set(1, 1, 2.5);
    testing::internal::CaptureStdout();
    sparse.print();
    std::string output = testing::internal::GetCapturedStdout();
    std::string expected_output = "1.5 0 \n0 2.5 \n";
    EXPECT_EQ(output, expected_output);

    testing::internal::CaptureStdout();
    std::cout << sparse;
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, expected_output);
}

TEST(sparseMatrix, testExample) {
    Matrix ma = Matrix(4, 5);
    ma.set(0, 2, 3);
    ma.set(0, 4, 4);
    ma.set(1, 2, 5);
    ma.set(1, 3, 7);
    ma.set(3, 1, 2);
    ma.set(3, 2, 6);
    SparseMatrix sa = ma.toSparseMatrix();

    testing::internal::CaptureStdout();
    sa.print();
    std::string output = testing::internal::GetCapturedStdout();
    std::string expected_output = "0 0 3 0 4 \n0 0 5 7 0 \n0 0 0 0 0 \n0 2 6 0 0 \n";
    EXPECT_EQ(output, expected_output);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

// #include "SparseMatrix.cpp"
// #include "matrix.cpp"
// #include <iostream>

// int main() {
//     SparseMatrix sparse(3, 3);
//     sparse.set(0, 0, 1.0);
//     sparse.set(1, 2, 2.0);
//     sparse.set(2, 1, 3.0);

//     sparse.get(1, 1);
// }