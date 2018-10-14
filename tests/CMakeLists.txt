# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project (tests)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)
include_directories(${Boost_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/dl)

file(GLOB TEST_SRCS RELATIVE ${CMAKE_CURRENT_LIST_DIR} *.cpp)



foreach(testSrc ${TEST_SRCS})
    get_filename_component(testName ${testSrc} NAME_WE)

	add_executable(${testName} ${testSrc})

	target_link_libraries(${testName} ${Boost_LIBRARIES} html)

#	set_target_properties(${testName} 
# 	     PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/testBin)

	add_test(NAME ${testName}
#	         WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/testBin
			 COMMAND ${testName})
endforeach(testSrc)
