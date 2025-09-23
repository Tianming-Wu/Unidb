cmake_minimum_required(VERSION 3.18)

project(UniDatabase
    VERSION 0.0.9
    LANGUAGES CXX
)

# 基本配置
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 安装路径配置  
include(GNUInstallDirs)
set(INSTALL_LIBDIR ${CMAKE_INSTALL_LIBDIR})
set(INSTALL_INCLUDEDIR ${CMAKE_INSTALL_INCLUDEDIR}/Unidb)

# 添加调试后缀
set(CMAKE_DEBUG_POSTFIX "d")

# 头文件目录
include_directories("include")

# 定义所有库
add_library(unidb STATIC src/unidb.cpp)

# 库依赖关系
# target_link_libraries(logd PUBLIC variant)

# 安装目标
install(TARGETS unidb
    EXPORT UniDatabaseTargets
    ARCHIVE DESTINATION ${INSTALL_LIBDIR}
    LIBRARY DESTINATION ${INSTALL_LIBDIR}
    INCLUDES DESTINATION ${INSTALL_INCLUDEDIR}
)

target_include_directories(unidb PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# 安装头文件
install(DIRECTORY include/
    DESTINATION ${INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.hpp" PATTERN "*.h"
)
set(INSTALL_INCLUDEDIR ${CMAKE_INSTALL_INCLUDEDIR}/Unidb)

# 安装导出文件
install(EXPORT UniDatabaseTargets
    FILE UniDatabaseTargets.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/UniDatabase
)

# 生成配置文件
include(CMakePackageConfigHelpers)
configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/UniDatabaseConfigVersion.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/UniDatabase
)

# 安装配置文件
install(EXPORT UniDatabaseTargets
    FILE UniDatabaseConfig.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/UniDatabase
)

# 生成版本文件
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/UniDatabaseConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

# 安装版本文件
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/UniDatabaseConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/UniDatabase
)
