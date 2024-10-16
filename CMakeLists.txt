cmake_minimum_required(VERSION 3.5.0)
project(flappy-bird-renderer VERSION 0.1.0 LANGUAGES C CXX)

find_package(SFML COMPONENTS graphics window system REQUIRED)

add_executable(flappy-bird-renderer 
    src/main.cpp 
    src/window.cpp 
    src/bird.cpp
    src/pipe.cpp)

target_link_libraries(flappy-bird-renderer sfml-graphics sfml-window sfml-system)

file(COPY ${PROJECT_SOURCE_DIR}/lib DESTINATION ${CMAKE_BINARY_DIR})
