cmake_minimum_required (VERSION 3.5)
project (advent2021)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native -Ofast -Wfatal-errors -std=c++2a")

add_executable(advent2021
	src/main.cpp
	src/day01.cpp
	src/day02.cpp
	src/day03.cpp
	src/day04.cpp
	src/day05.cpp
	src/day06.cpp
	src/day07.cpp
	src/day08.cpp
	src/day09.cpp
	src/day10.cpp
	src/day11.cpp
	src/day12.cpp
	src/day13.cpp
	src/day14.cpp
	src/day15.cpp
	src/day16.cpp
	src/day17.cpp
	src/day18.cpp
	src/day19.cpp
	src/day20.cpp
	src/day21.cpp
	src/day22.cpp
	src/day23.cpp
	src/day24.cpp
	src/day25.cpp
)

# target_link_directories(advent2021 PUBLIC .)
target_compile_definitions(advent2021 PUBLIC SOURCE_DIR=${CMAKE_SOURCE_DIR})