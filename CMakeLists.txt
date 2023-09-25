cmake_minimum_required(VERSION 3.22)
project(octree_model)

set(CMAKE_CXX_STANDARD 23)

find_package(glm REQUIRED) 
add_executable(octree_model main.cpp
primitives/Primitive.cpp 
primitives/Primitive.h 
primitives/Primitive.h 
primitives/Sphere.cpp 
primitives/Sphere.h 
primitives/Sphere.h 
primitives/Cylinder.cpp 
primitives/Cylinder.h 
primitives/Box.cpp 
primitives/Box.h
octree/octree.h
octree/octree.cpp utils/BoundingBox.cpp utils/BoundingBox.h)

target_link_libraries(${PROJECT_NAME} glm::glm)
set_property(TARGET ${PROJECT_NAME} PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
set(CMAKE_CXX_FLAGS_RELEASE "-O2")