#-----------------------------------------------------------
cmake_minimum_required(VERSION 4.1.1)

#https://github.com/Kitware/CMake/blob/v4.1.1/Help/dev/experimental.rst

# 设置CMake中的实验属性，可以生成模块
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "d0edc3af-4c50-42ea-a356-e2862fe7a444")
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_MODULE_STD ON)


project(DataBase LANGUAGES CXX)

# 当有文件被添加进来的时候自动添加
file(GLOB TextFiles ${CMAKE_CURRENT_SOURCE_DIR}/*.txt)
file(GLOB MdFiles ${CMAKE_CURRENT_SOURCE_DIR}/*.md
                ${CMAKE_CURRENT_SOURCE_DIR}/*.MD)
file(GLOB ModuleInterfaces ${CMAKE_CURRENT_SOURCE_DIR}/*.cppm
                            ${CMAKE_CURRENT_SOURCE_DIR}/*.ixx)

# 排除搜索CMakeList文件
list(FILTER TextFiles EXCLUDE REGEX "CMakeLists\.txt$")

#
add_executable(DataBase
    main.cpp
    DataBroker.cppm
    StudentBroker.cppm
    DataBase.cppm
    TeacherBroker.cppm
    CourseBroker.cppm
    TeachingTaskBroker.cppm


)

target_sources(DataBase
    PRIVATE
        # 普通源文件（实现单元/辅助文件）
        # C++模块文件集
        FILE_SET cxx_modules
            TYPE CXX_MODULES
            BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
            FILES ${ModuleInterfaces}              # 模块接口单元
)


# 将这个文件展示出来
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX "cppm模块接口文件" FILES ${ModuleInterfaces})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX "Md文件" FILES ${MdFiles})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX "txt文本文件" FILES ${TextFiles})

target_compile_features(DataBase PRIVATE cxx_std_23)




#-------------------------DataBase-------------------------------------#
# ===== 新增部分：添加 PostgreSQL (libpqxx) 支持 =====

# 查找 pkg-config（用于找 libpqxx）
find_package(PkgConfig REQUIRED)

# 查找 libpqxx
pkg_check_modules(PQXX REQUIRED libpqxx)

# 包含头文件路径
target_include_directories(DataBase PRIVATE ${PQXX_INCLUDE_DIRS})

# 链接 libpqxx 和 libpq（必须两个都链接）
target_link_libraries(DataBase ${PQXX_LIBRARIES} pq)

# ==================================================

