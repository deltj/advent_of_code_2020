add_executable(day3part1 part1.cpp)
add_executable(day3part2 part2.cpp)

target_link_libraries(day3part1 ${OpenCV_LIBS})
target_link_libraries(day3part2 ${OpenCV_LIBS})
