cmake_minimum_required(VERSION 2.8)
project(win-c)

set(SOURCES "source/getopt.c")
add_library(libwinc ${SOURCES})
target_include_directories(libwinc INTERFACE "include")

if(WINC_BUILD_TESTS)
	add_executable(testLibwinc test/test.cpp)
	target_link_libraries(testLibwinc INTERFACE libwinc)

	add_executable(test_getopt_long test/test_getopt_long.cpp)
	target_link_libraries(test_getopt_long INTERFACE libwinc)
endif()

install(TARGETS libwinc DESTINATION lib)
