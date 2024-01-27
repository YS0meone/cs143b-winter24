project(PRM)
cmake_minimum_required(VERSION 3.10)
add_executable(${PROJECT_NAME} src/main.cpp
        src/prm.cpp
        src/pcb.cpp
        src/rcb.cpp
        src/rl.cpp
)
include_directories(${PROJECT_NAME} src include)