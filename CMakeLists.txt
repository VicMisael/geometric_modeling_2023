cmake_minimum_required(VERSION 3.22)
project(octree_model)

set(CMAKE_CXX_STANDARD 23)

find_package(glm REQUIRED)
find_package(glfw3 REQUIRED)
add_subdirectory(strippedRayTracer)
add_subdirectory(glad)

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
        rt_interface/IntersectionTests.h
        ogl/stb_image.h
        ogl/Game.h
        ogl/States/State.h
        ogl/Primitives/Vertex.h
        ogl/Primitives/Shader.h
        ogl/Primitives/primform.h
        ogl/Primitives/Model.h
        ogl/Primitives/Mesh.h
        ogl/Primitives/Camera.h)
target_link_libraries(${PROJECT_NAME} glm::glm)
target_link_libraries(${PROJECT_NAME} RayTracer_redone)
target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} glad)
set_property(TARGET ${PROJECT_NAME} PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
if (MSVC)
    target_link_options(${PROJECT_NAME} PUBLIC "/INCREMENTAL")
    set(CMAKE_CXX_FLAGS_RELEASE "/O2 ")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/O2")
endif (MSVC)
if (UNIX)
    set(CMAKE_CXX_FLAGS_RELEASE "-Ofast -ffast-math")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-Ofast -og -ffast-math")
endif (UNIX)
file(COPY ogl/shaders DESTINATION ${CMAKE_BINARY_DIR})
