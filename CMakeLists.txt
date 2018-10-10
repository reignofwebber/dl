# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_BUILD_DIR ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/build)

enable_testing()
# Include sub-projects.
add_subdirectory ("dl")
add_subdirectory ("tests")
