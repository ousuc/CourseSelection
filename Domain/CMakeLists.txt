cmake_minimum_required(VERSION 4.1.1)

#https://github.com/Kitware/CMake/blob/v4.1.1/Help/dev/experimental.rst

set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "d0edc3af-4c50-42ea-a356-e2862fe7a444")
set(CMAKE_CXX_MODULE_STD ON)

project(domain LANGUAGES CXX)



# 然后就是创建动态库了
add_library(
    Domain
    SHARED
)

target_sources(Domain
PUBLIC
    FILE_SET CXX_MODULES
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
    FILES Course.cppm Role.cppm SecretaryRole.cppm
        StudentRole.cppm TeacherRole.cppm
        TeachingTask.cppm
)

target_include_directories(Domain
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# 设置目标属性，仅对Linux生效
# todo: 跨平台设置
set_target_properties(
    Domain PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib
    VERSION 1.0.0
    SOVERSION 1
    # window 兼容
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin
    # macOS 未知 需要完成
)

target_compile_features(Domain PRIVATE cxx_std_23)


