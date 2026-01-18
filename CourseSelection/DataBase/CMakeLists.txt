#-----------------------------------------------------------
cmake_minimum_required(VERSION 4.1.1)

#https://github.com/Kitware/CMake/blob/v4.1.1/Help/dev/experimental.rst

# 设置CMake中的实验属性，可以生成模块
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "d0edc3af-4c50-42ea-a356-e2862fe7a444")
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_MODULE_STD ON)


project(DataBase LANGUAGES CXX)

# 接下来是创建动态库了
add_library(
    DataBaseLib
    SHARED
)

target_link_libraries(DataBaseLib
PRIVATE
    Domain
)
target_sources(DataBaseLib
PUBLIC
    FILE_SET CXX_MODULES
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
    FILES     DataBroker.cppm
    StudentBroker.cppm
    DataBase.cppm
    TeacherBroker.cppm
    CourseBroker.cppm
    TeachingTaskBroker.cppm
)
target_include_directories(DataBaseLib
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# 设置目标属性，仅对Linux生效
# todo: 跨平台设置
set_target_properties(
    DataBaseLib PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib
    VERSION 1.0.0
    SOVERSION 1
    # window 兼容
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin
    # macOS 未知 需要完成
)

#-------------------------DataBase-------------------------------------#
# ===== 新增部分：添加 PostgreSQL (libpqxx) 支持 =====

# 查找 pkg-config（用于找 libpqxx）
find_package(PkgConfig REQUIRED)

# 查找 libpqxx
pkg_check_modules(PQXX REQUIRED libpqxx)

# 包含头文件路径
target_include_directories(DataBaseLib PRIVATE ${PQXX_INCLUDE_DIRS})

# 链接 libpqxx 和 libpq
target_link_libraries(DataBaseLib
    PRIVATE
    ${PQXX_LIBRARIES} pq)

# ==================================================

target_compile_features(DataBaseLib PRIVATE cxx_std_23)
