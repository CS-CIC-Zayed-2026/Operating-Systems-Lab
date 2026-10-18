cmake_minimum_required(VERSION 4.3)
project(Operating_Systems)

set(CMAKE_CXX_STANDARD 17)

add_executable(Operating_Systems main.cpp)
add_executable(get_current_pid Process_Management/code/get_current_pid.cpp)
add_executable(create_new_process Process_Management/code/create_new_process.cpp)
add_executable(parent_child_process Process_Management/code/parent_child_process.cpp)
add_executable(example Process_Management/code/example.cpp)
