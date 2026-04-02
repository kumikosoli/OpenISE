#include <gtest/gtest.h>
#include "manager.h"

class ManagerTest : public ::testing::Test {
protected:
    Manager manager{120, 1, 2};  // 学分要求120, 硕士1篇, 博士2篇
};

// 测试添加本科生
TEST_F(ManagerTest, AddUndergraduate) {
    EXPECT_TRUE(manager.addUndergraduate("张三", 20, 1001, "男", "计算机", 2));
    EXPECT_EQ(manager.getTotalCount(), 1);

    // 重复ID应该失败
    EXPECT_FALSE(manager.addUndergraduate("李四", 21, 1001, "女", "数学", 1));
    EXPECT_EQ(manager.getTotalCount(), 1);
}

// 测试添加研究生
TEST_F(ManagerTest, AddGraduate) {
    EXPECT_TRUE(manager.addMaster("王五", 24, 2001, "男", "人工智能", "李教授", "学硕"));
    EXPECT_TRUE(manager.addPhD("赵六", 26, 3001, "女", "机器学习", "王教授"));
    EXPECT_EQ(manager.getTotalCount(), 2);
}

// 测试查找
TEST_F(ManagerTest, FindById) {
    manager.addUndergraduate("张三", 20, 1001, "男", "计算机", 2);

    Person* p = manager.findById(1001);
    ASSERT_NE(p, nullptr);
    EXPECT_EQ(p->getName(), "张三");
    EXPECT_EQ(p->getRole(), "Undergraduate");

    // 不存在的ID
    EXPECT_EQ(manager.findById(9999), nullptr);
}

// 测试删除
TEST_F(ManagerTest, RemoveStudent) {
    manager.addUndergraduate("张三", 20, 1001, "男", "计算机", 2);
    EXPECT_EQ(manager.getTotalCount(), 1);

    EXPECT_TRUE(manager.removeStudent(1001));
    EXPECT_EQ(manager.getTotalCount(), 0);

    // 删除不存在的
    EXPECT_FALSE(manager.removeStudent(1001));
}

// 测试本科生选课
TEST_F(ManagerTest, AddCourse) {
    manager.addUndergraduate("张三", 20, 1001, "男", "计算机", 2);

    EXPECT_TRUE(manager.addCourse(1001, "高等数学", 4, 85));
    EXPECT_TRUE(manager.addCourse(1001, "线性代数", 3, 90));

    // 给非本科生选课应该失败
    manager.addMaster("王五", 24, 2001, "男", "AI", "李教授", "学硕");
    EXPECT_FALSE(manager.addCourse(2001, "高等数学", 4, 85));
}

// 测试统计
TEST_F(ManagerTest, Statistics) {
    manager.addUndergraduate("张三", 20, 1001, "男", "计算机", 2);
    manager.addUndergraduate("李四", 21, 1002, "女", "计算机", 3);
    manager.addMaster("王五", 24, 2001, "男", "AI", "李教授", "学硕");
    manager.addPhD("赵六", 26, 3001, "女", "ML", "王教授");

    auto stats = manager.getStatistics();
    EXPECT_EQ(stats.total, 4);
    EXPECT_EQ(stats.undergrads, 2);
    EXPECT_EQ(stats.masters, 1);
    EXPECT_EQ(stats.phds, 1);
}

// 测试毕业资格检查
TEST_F(ManagerTest, GraduationEligibility) {
    manager.addUndergraduate("张三", 20, 1001, "男", "计算机", 2);

    // 学分不够，不能毕业
    manager.addCourse(1001, "高数", 4, 85);
    EXPECT_FALSE(manager.checkGraduationEligibility(1001));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
