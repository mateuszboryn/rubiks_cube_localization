cmake_minimum_required(VERSION 2.8)

project(rubiks_cube_localization)
add_executable(rkl main.cpp)

execute_process(COMMAND pkg-config opencv --cflags --libs
	OUTPUT_VARIABLE opencv_flags
)
STRING(REGEX REPLACE "\n" " " opencv_flags "${opencv_flags}")
set(CMAKE_CXX_FLAGS ${opencv_flags})

