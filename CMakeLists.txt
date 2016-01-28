cmake_minimum_required(VERSION 3.4)
project(Snake)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp src/Block.cpp src/Board.cpp src/Food.cpp src/Game.cpp src/Snake.cpp)
add_executable(Snake ${SOURCE_FILES})

target_link_libraries(Snake sfml-graphics)
target_link_libraries(Snake sfml-window)
target_link_libraries(Snake sfml-system)

configure_file(res/Font.ttf ${CMAKE_SOURCE_DIR}/bin/res/Font.ttf COPYONLY)
