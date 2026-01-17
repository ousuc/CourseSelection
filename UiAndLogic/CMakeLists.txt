cmake_minimum_required(VERSION 4.1.1)

#https://github.com/Kitware/CMake/blob/v4.1.1/Help/dev/experimental.rst

set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "d0edc3af-4c50-42ea-a356-e2862fe7a444")
set(CMAKE_CXX_MODULE_STD ON)

# project(UiAndLogic LANGUAGES CXX)

# # set(MODULE_LIB_DIR1 /opt/utils/modules)  # 模块库的目录的设置
# add_executable(UiAndLogic                            # 模块实现单元
#     main.cpp
# )
# # 私有连接
# target_link_libraries(UiAndLogic
# PRIVATE
#     Domain DataBaseLib
# )
# set(PRESENTATION_MODULES
#     inputhelper.cppm
#     tableformatter.cppm
#     terminalui.cppm
# )

# set(APPLICATIONLOGIC_MODULES
#     maincontroller.cppm
#     studentcontroller.cppm
#     teachercontroller.cppm
#     secretarycontroller.cppm
#     coursecontroller.cppm
#     gradecontroller.cppm
#     datatype.cppm
#     registrar.cppm
# )
# source_group("presentation" FILES ${PRESENTATION_MODULES})
# source_group("applicationlogic" FILES ${APPLICATIONLOGIC_MODULES})
# target_sources(UiAndLogic  PRIVATE FILE_SET cxx_modules TYPE CXX_MODULES
#     BASE_DIRS                              # 配置BASE_DIRS，用于组织构建输出目录，以便构建不同目录中(同名的)模块文件.
#         #${MODULE_LIB_DIR1}
#         ${CMAKE_CURRENT_SOURCE_DIR}
#     FILES ${PRESENTATION_MODULES} ${APPLICATIONLOGIC_MODULES}
# )
# target_compile_features(UiAndLogic PRIVATE cxx_std_23)


# 直接创建库
add_library(
    CourseSelectionLib
    SHARED
)
# 关联库先
target_link_libraries(CourseSelectionLib
PRIVATE
    Domain DataBaseLib
)

target_sources(CourseSelectionLib
PUBLIC
    FILE_SET CXX_MODULES
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
    FILES
        maincontroller.cppm
        studentcontroller.cppm
        teachercontroller.cppm
        secretarycontroller.cppm
        coursecontroller.cppm
        gradecontroller.cppm
        datatype.cppm
        registrar.cppm
        inputhelper.cppm
        tableformatter.cppm
        terminalui.cppm
)


target_include_directories(CourseSelectionLib
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)


set_target_properties(
    CourseSelectionLib PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib
    VERSION 1.0.0
    SOVERSION 1
    # window 兼容
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin
    # macOS 未知 需要完成
)


































# target_link_directories(UiAndLogic PRIVATE /opt/utils/lib)  # -L /opt/utils/lib 设置链接路径
# target_link_libraries(UiAndLogic PRIVATE utils)             # -lutils           设置链接库名

# set_target_properties(UiAndLogic PROPERTIES
#     INSTALL_RPATH_USE_LINK_PATH  True                           # 使用链接路径作为安装文件的RPath，等价于"-Wl,-rpath=/opt/utils/lib"
# )

#add_library(UiAndLogic SHARED
#  utils.cpp
#)

#set_target_properties( UiAndLogic PROPERTIES
#    PUBLIC_HEADER utils.cppm
#    VERSION   2.5.1
#    SOVERSION 2
#    LIBRARY_OUTPUT_DIRECTORY  "${CMAKE_BINARY_DIR}/lib"
#)

#install(TARGETS UiAndLogic
#    LIBRARY DESTINATION /opt/utils/lib
#    PUBLIC_HEADER DESTINATION  /opt/utils/modules
#)

#add_custom_command(TARGET UiAndLogic
#    POST_BUILD
#    COMMAND cmake --install "${CMAKE_CURRENT_BINARY_DIR}"
#)
