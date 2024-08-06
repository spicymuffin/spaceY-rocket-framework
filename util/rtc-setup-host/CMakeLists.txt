cmake_minimum_required(VERSION 3.22)

if (WIN32 OR UNIX)
	set(PROJECT rtc-setup)
	project(${PROJECT} C CXX)
	add_executable(${PROJECT})

	file(GLOB_RECURSE SOURCES src/*.cpp)
	target_sources(${PROJECT} PRIVATE 
		${SOURCES}
	)

	target_include_directories(${PROJECT} PRIVATE 
		src
	)

	set_property(TARGET ${PROJECT} PROPERTY CXX_STANDARD 17)
else()
	message(WARNING "Unsupported platform")
endif()

if (WIN32)
	target_link_libraries(${PROJECT} PRIVATE 
		OneCore.lib
		Setupapi.lib
	)

	target_compile_definitions(${PROJECT} PRIVATE 
		# _CRT_SECURE_NO_WARNINGS
		_CRT_NONSTDC_NO_DEPRECATE
		# _SCL_SECURE_NO_WARNINGS
		_UNICODE
		UNICODE
		WIN32_LEAN_AND_MEAN
		NOMINMAX
	)
elseif(UNIX)
	find_package(Curses REQUIRED)
	
	target_include_directories(${PROJECT} PRIVATE 
		${CURSES_INCLUDE_DIR}
	)

	target_link_libraries(${PROJECT} PRIVATE 
		${CURSES_LIBRARIES}
	)
endif()
