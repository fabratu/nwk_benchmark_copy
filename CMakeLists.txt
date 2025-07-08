cmake_minimum_required (VERSION 3.17)
project(nwk_eval CXX)

set(CMAKE_CXX_STANDARD 20)

find_package(PkgConfig)
pkg_check_modules(NETWORKIT REQUIRED IMPORTED_TARGET networkit)

add_executable(nwk_eval main.cpp)
target_include_directories(nwk_eval PUBLIC "${PROJECT_SOURCE_DIR}/." ${NETWORKIT_INCLUDE_DIRS})
target_link_libraries(nwk_eval PUBLIC PkgConfig::NETWORKIT)
install(TARGETS nwk_eval DESTINATION ${CMAKE_INSTALL_PREFIX})