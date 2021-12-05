cmake_minimum_required(VERSION 3.10)

project(AOC2021)
			  
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(AOC2021 src/main.cpp src/day1.cpp src/day2.cpp src/day3.cpp src/day4.cpp src/day5.cpp src/day6.cpp)

target_include_directories(AOC2021 PUBLIC include)
