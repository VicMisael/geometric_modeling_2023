cmake_minimum_required(VERSION 3.22)
project(octree_model)

find_package(glm REQUIRED)
set(CMAKE_CXX_STANDARD 23)

add_subdirectory(octree)
add_executable(octree_model main.cpp primitives/Primitive.cpp primitives/Primitive.h primitives/Primitive.h)

target_link_libraries(${PROJECT_NAME} glm::glm)
target_link_libraries(${PROJECT_NAME} octree)
