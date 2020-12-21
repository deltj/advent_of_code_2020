cmake_minimum_required(VERSION 3.0)

project(advent_of_code_2020)

find_package(Boost 1.75 COMPONENTS regex)
find_package(OpenCV 4.5)

add_subdirectory(day1)
add_subdirectory(day2)
add_subdirectory(day3)
add_subdirectory(day4)
