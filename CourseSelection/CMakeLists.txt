# 设置最小需要版本
cmake_minimum_required(VERSION 4.1.1)

set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "d0edc3af-4c50-42ea-a356-e2862fe7a444")
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_MODULE_STD ON)

project(CourseSelection LANGUAGES CXX)

# 添加子项目
add_subdirectory(Domain)
add_subdirectory(DataBase)
add_subdirectory(UiAndLogic)


target_compile_features(UiAndLogic PRIVATE cxx_std_23)
