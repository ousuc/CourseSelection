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


add_executable(CourseSelection
    main.cpp
)

target_link_libraries(CourseSelection
PRIVATE
    CourseSelectionLib
)

# # 添加库 子项目生成
# target_link_directories(CourseSelection PRIVATE
#     ${CMAKE_CURRENT_BINARY_DIR}/Domain/lib  # 对应 Domain 库的 LIBRARY_OUTPUT_DIRECTORY
# )

# target_link_libraries(CourseSelection PRIVATE Domain)


target_compile_features(CourseSelection PRIVATE cxx_std_23)
