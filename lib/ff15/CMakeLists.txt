cmake_minimum_required(VERSION 3.22)

project(fatfs C)

add_library(fatfs STATIC)

target_sources(fatfs PRIVATE
	source/ff.c
  	source/ffsystem.c
  	source/ffunicode.c
)

target_include_directories(fatfs PUBLIC
	${CMAKE_CURRENT_LIST_DIR}/source
)
