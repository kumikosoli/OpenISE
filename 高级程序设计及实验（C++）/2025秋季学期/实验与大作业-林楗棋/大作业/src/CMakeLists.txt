cmake_minimum_required(VERSION 3.16)
project(StudentManagementSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

find_package(nlohmann_json REQUIRED)
find_package(GTest REQUIRED)

include_directories(class manageCli)

# 主程序
add_executable(student_manager
    main.cpp
    class/publication.cpp
    class/phd.cpp
    manageCli/manager.cpp
)
target_link_libraries(student_manager nlohmann_json::nlohmann_json)

# 测试
enable_testing()
add_executable(run_tests
    tests/testManager.cpp
    class/publication.cpp
    class/phd.cpp
    manageCli/manager.cpp
)
target_link_libraries(run_tests GTest::gtest nlohmann_json::nlohmann_json)
add_test(NAME ManagerTests COMMAND run_tests)
