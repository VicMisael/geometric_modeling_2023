cmake_minimum_required(VERSION 3.22)
project(octree_model)


set(CMAKE_CXX_STANDARD 23)

add_subdirectory(octree)
add_executable(octree_model main.cpp)
target_link_libraries(${PROJECT_NAME} octree)