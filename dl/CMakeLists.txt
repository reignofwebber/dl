# CMakeList.txt : CMake project for dl, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project(dl)
# Add source to this project's executable.
find_package(CURL)

message(...${CURL_INCLUDE_DIRS})
message(...${CURL_LIBRARIES})

set(dl_SRC main.cpp
           dl.cpp
		   dl.h
		   htmlparser.cpp
		   htmlparser.h)

add_executable (dl ${dl_SRC})
target_include_directories(dl PRIVATE ${CURL_INCLUDE_DIRS})
target_link_libraries(dl PRIVATE ${CURL_LIBRARIES})

add_library(html htmlparser.cpp htmlparser.h)

# TODO: Add tests and install targets if needed.
