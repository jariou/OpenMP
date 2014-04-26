macro (SETUP_LIB_BY_CMAKE lib)
	
	find_package (${lib} REQUIRED)
	include_directories(${${lib}_INCLUDE_DIRS})
	list(APPEND PROJECT_LIBRARIES ${${lib}_LIBRARIES})
	list(APPEND PROJECT_LIBRARY_DIRS ${${lib}_LIBRARY_DIRS})

endmacro(SETUP_LIB_BY_CMAKE lib)

macro (SETUP_LIB_BY_PKGCONFIG lib)
	
	pkg_check_modules(${lib} REQUIRED ${lib})
	include_directories(${${lib}_INCLUDE_DIRS})
	list(APPEND PROJECT_LIBRARIES ${${lib}_LIBRARIES})
	list(APPEND PROJECT_LIBRARY_DIRS ${${lib}_LIBRARY_DIRS})

endmacro(SETUP_LIB_BY_PKGCONFIG lib)

cmake_minimum_required (VERSION 2.6)

project (OpenMP_Example)

find_package(OpenMP REQUIRED)

set(CMAKE_CXX_FLAGS "-Wall ${OpenMP_CXX_FLAGS}" )
set(CMAKE_C_FLAGS "-Wall ${OpenMP_C_FLAGS}" )

set(SOURCES_EXE01 ./exe01/hello.c)

add_executable(hello ${SOURCES_EXE01})

target_link_libraries(hello)

