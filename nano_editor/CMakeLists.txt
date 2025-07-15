cmake_minimum_required(VERSION 3.31)
project(nano_editor)

set(CMAKE_CXX_STANDARD 26)
find_package(Curses REQUIRED)

include_directories(${CURSES_INCLUDE_DIR})
add_executable(nano_editor src/main.cpp
        src/lib/helper_functions.h
        src/lib/buffer.h)

target_link_libraries(nano_editor ${CURSES_LIBRARIES})