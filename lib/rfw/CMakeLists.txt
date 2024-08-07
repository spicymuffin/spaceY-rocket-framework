cmake_minimum_required(VERSION 3.22)

project(rfw C CXX)

file(GLOB_RECURSE SOURCES "src/*.c" "src/*.cpp")

add_library(rfw STATIC ${SOURCES})

target_include_directories(rfw
	PUBLIC
	${CMAKE_CURRENT_LIST_DIR}/include
)

