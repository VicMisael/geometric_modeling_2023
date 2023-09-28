cmake_minimum_required(VERSION 3.22)
project(octree_model)

set(CMAKE_CXX_STANDARD 23)

find_package(glm REQUIRED)
add_subdirectory(strippedRayTracer)
add_executable(octree_model main.cpp
        primitives/Primitive.cpp
        primitives/Primitive.h
        primitives/Primitive.h
        primitives/Sphere.cpp
        primitives/Sphere.h
        primitives/Sphere.h
        primitives/Box.cpp
        primitives/Box.h
        octree/octree.h
        octree/octree.cpp utils/BoundingBox.cpp utils/BoundingBox.h
        rt_interface/InterceptableOctree.h
        rt_interface/InterceptableOctree.cpp
        rt_interface/IntersectionTests.cpp
        rt_interface/IntersectionTests.h)
target_link_libraries(${PROJECT_NAME} glm::glm)
target_link_libraries(${PROJECT_NAME} RayTracer_redone)
set_property(TARGET ${PROJECT_NAME} PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
if(MSVC)
target_compile_options(${PROJECT_NAME} PUBLIC "/arch:AVX512F")
target_link_options(${PROJECT_NAME} PUBLIC "/INCREMENTAL")
set(CMAKE_CXX_FLAGS_RELEASE "/O2 ")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO  "/O2")
endif()
if(UNIX)

endif()
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -mavx2")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO  "-O2 -og -mavx2")
