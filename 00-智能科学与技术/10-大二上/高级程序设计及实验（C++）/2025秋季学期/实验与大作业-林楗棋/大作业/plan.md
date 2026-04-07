## C++期末大作业

![image-20260117223856256](/home/matrix/.config/Typora/typora-user-images/image-20260117223856256.png)

### 第一阶段（核心功能，必须完成）

1. 学生基本信息管理（增删改查）
2. 成绩管理
3. 简单的统计功能
4. 文件读写
5. 基本的 CLI 交互

### 第二阶段（完善功能）

1. 课程管理
2. 选课系统
3. 高级查询和排序
4. 报表生成

### 第三阶段（加分项，时间允许）

1. 奖惩记录
2. 数据备份恢复
3. 命令历史和自动补全
4. 彩色输出（ANSI 颜色）

---

计划使用CMake编译，Gtest测试，JSON储存学生信息，Doxygen生成文档（待定）。

首先需要三种类型的类，学生（包括本科生和硕博生），老师和课程.

本科生要有gpa

```
project/
├── CMakeLists.txt
├── README.md
├── Doxyfile
│
├── include/                      # 头文件目录
│   ├── core/                     # 核心类
│   │   ├── Person.h             # 基类
│   │   ├── Student.h            # 学生类
│   │   ├── Teacher.h            # 教师类
│   │   └── Course.h             # 课程类
│   │
│   ├── manager/                  # 管理器类
│   │   ├── StudentManager.h     # 学生管理器
│   │   ├── TeacherManager.h     # 教师管理器
│   │   ├── CourseManager.h      # 课程管理器
│   │   └── SystemManager.h      # 系统总管理器
│   │
│   ├── utils/                    # 工具类
│   │   ├── FileIO.h             # 文件读写
│   │   ├── JsonHelper.h         # JSON 处理
│   │   ├── Validator.h          # 数据验证
│   │   └── StringUtils.h        # 字符串工具
│   │
│   └── cli/                      # 命令行接口
│       ├── CommandParser.h       # 命令解析器
│       ├── CLI.h                 # CLI 主类
│       └── Commands.h            # 命令处理函数
│
├── src/                          # 源文件目录（与 include 对应）
│   ├── core/
│   │   ├── Person.cpp
│   │   ├── Student.cpp
│   │   ├── Teacher.cpp
│   │   └── Course.cpp
│   │
│   ├── manager/
│   │   ├── StudentManager.cpp
│   │   ├── TeacherManager.cpp
│   │   ├── CourseManager.cpp
│   │   └── SystemManager.cpp
│   │
│   ├── utils/
│   │   ├── FileIO.cpp
│   │   ├── JsonHelper.cpp
│   │   ├── Validator.cpp
│   │   └── StringUtils.cpp
│   │
│   ├── cli/
│   │   ├── CommandParser.cpp
│   │   ├── CLI.cpp
│   │   └── Commands.cpp
│   │
│   └── main.cpp                  # 程序入口
│
├── tests/                        # 测试文件
│   ├── test_student.cpp
│   ├── test_teacher.cpp
│   ├── test_course.cpp
│   ├── test_manager.cpp
│   └── test_fileio.cpp
│
├── data/                         # 数据文件
│   ├── students.json
│   ├── teachers.json
│   ├── courses.json
│   └── sample_data.json
│
└── docs/                         # 文档
    ├── report/                   # LaTeX 报告
    │   ├── main.tex
    │   ├── chapters/
    │   └── figures/
    └── doxygen/                  # Doxygen 生成的文档
```

```mermaid
graph TB
    subgraph 用户交互层
        User([用户]) -->|输入命令| CLI[CLI 命令行界面]
        CLI -->|显示结果| User
        CLI -->|显示菜单提示错误| User
    end
    
    subgraph 业务逻辑层
        CLI -->|调用业务方法| Manager[Manager 管理器]
        Manager -->|返回结果| CLI
        
        Manager -->|增删改查| Operations[核心操作]
        Operations -->|学生管理| StudentOps[添加/删除/查找/修改]
        Operations -->|数据统计| StatOps[统计/排序/筛选]
        Operations -->|数据持久化| FileOps[保存/加载 JSON]
    end
    
    subgraph 数据模型层
        Manager -->|创建/管理| Person[Person 抽象基类]
        Person -->|派生| Undergraduate[Undergraduate<br/>本科生]
        Person -->|派生| Graduate[Graduate<br/>研究生抽象类]
        Graduate -->|派生| Master[Master<br/>硕士生]
        Graduate -->|派生| PhD[PhD<br/>博士生]
        
        Master -.->|包含| Pub1[Publications]
        PhD -.->|包含| Pub2[Publications]
        Undergraduate -.->|包含| Course[Course Info]
    end
    
    subgraph 存储层
        Manager -->|读写| Storage[(students.json<br/>数据文件)]
    end
    
    style User fill:#4CAF50,stroke:#2E7D32,stroke-width:3px,color:#fff
    style CLI fill:#2196F3,stroke:#1565C0,stroke-width:3px,color:#fff
    style Manager fill:#FF9800,stroke:#E65100,stroke-width:3px,color:#fff
    style Person fill:#9C27B0,stroke:#4A148C,stroke-width:2px,color:#fff
    style Undergraduate fill:#E1BEE7,stroke:#4A148C,stroke-width:2px
    style Graduate fill:#CE93D8,stroke:#4A148C,stroke-width:2px
    style Master fill:#BA68C8,stroke:#4A148C,stroke-width:2px
    style PhD fill:#AB47BC,stroke:#4A148C,stroke-width:2px
    style Storage fill:#607D8B,stroke:#37474F,stroke-width:2px,color:#fff
```

```mermaid
sequenceDiagram
    actor User as 用户
    participant CLI as CLI<br/>命令行界面
    participant Mgr as Manager<br/>管理器
    participant Obj as 学生对象<br/>(Person派生类)
    participant File as JSON文件
    
    User->>CLI: 输入命令 "add student"
    activate CLI
    CLI->>User: 显示输入提示
    User->>CLI: 输入学生信息
    CLI->>Mgr: addStudent(info)
    activate Mgr
    
    Mgr->>Mgr: 验证数据
    Mgr->>Obj: 创建对象<br/>(Undergraduate/Master/PhD)
    activate Obj
    Obj-->>Mgr: 对象创建成功
    deactivate Obj
    
    Mgr->>Mgr: 存入 map<int, unique_ptr<Person>>
    Mgr-->>CLI: 返回成功
    deactivate Mgr
    CLI->>User: 显示 "添加成功"
    deactivate CLI
    
    User->>CLI: 输入命令 "save"
    activate CLI
    CLI->>Mgr: saveAll()
    activate Mgr
    Mgr->>Obj: toJson() (多态调用)
    activate Obj
    Obj-->>Mgr: JSON数据
    deactivate Obj
    Mgr->>File: 写入文件
    activate File
    File-->>Mgr: 保存成功
    deactivate File
    Mgr-->>CLI: 返回成功
    deactivate Mgr
    CLI->>User: 显示 "保存成功"
    deactivate CLI
```

