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

find_package(SharedCppLib2 REQUIRED)

file(READ "${CMAKE_SOURCE_DIR}/cmake/build_count" CURRENT_BUILD)

# 将字符串转换为数字并加一
math(EXPR NEW_BUILD "${CURRENT_BUILD} + 1")

# 将新的 Build 号写回文件
file(WRITE "${CMAKE_SOURCE_DIR}/cmake/build_count" "${NEW_BUILD}")

# 设置版本
set(PROJECT_VERSION_TWEAK ${NEW_BUILD})
set(PROJECT_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}.${PROJECT_VERSION_TWEAK})

# 版本信息文件
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/version.hpp.in"
    "${CMAKE_CURRENT_BINARY_DIR}/version.hpp"
)

# 头文件目录
include_directories("include")

# 定义所有库
add_library(unidb STATIC src/unidb_typesystem.cpp src/unidb_object.cpp src/unidb_db.cpp src/unidb_delta.cpp)

# 库依赖关系
target_link_libraries(unidb PUBLIC SharedCppLib2::basic SharedCppLib2::indexer)

# 版本文件链接
target_include_directories(unidb PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")

if(BUILD_TESTING)
    add_executable(unidb_test tests/unidb_test.cpp)
    target_link_libraries(unidb_test PRIVATE unidb)
endif()

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
install(FILES "include/unidb.hpp" "include/unidb_exception.hpp"
    DESTINATION ${INSTALL_INCLUDEDIR}
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
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake.in
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
