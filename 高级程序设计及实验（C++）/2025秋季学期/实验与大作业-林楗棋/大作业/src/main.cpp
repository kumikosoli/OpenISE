#include "cli.h"
#include "manager.h"

int main() {
    // 创建管理器，设置默认毕业要求：
    // - 本科生: 155 学分
    // - 硕士生: 1 篇论文
    // - 博士生: 2 篇论文
    Manager manager(155, 1, 2);

    // 启动命令行界面
    CLI cli(manager);
    cli.run();

    return 0;
}
