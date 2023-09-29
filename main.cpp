#include <iostream>
#include "octree/octree.h"
#include "primitives/Sphere.h"
#include "primitives/Box.h"
#include "strippedRayTracer/RayTracerRedone/tracer/objects/VirtualObject.h"
#include "strippedRayTracer/RayTracerRedone/tracer/scene/materials/Phong.h"
#include "strippedRayTracer/RayTracerRedone/RayTracerRedone.cpp"
#include "rt_interface/InterceptableOctree.h"

int main() {
    auto sphere = std::make_shared<Sphere>(40 / 3.0f);
    auto octree = std::make_shared<octree::Octree>(sphere, 10);
    std::cout << octree->parse() << std::endl;
    std::cout << octree->volume() << std::endl;
    auto box = std::make_shared<Box>(glm::vec3(-50, 0, -50), glm::vec3(50, 50, 50));
    auto boxOct = std::make_shared<octree::Octree>(box, 3);
    std::cout << boxOct->parse() << std::endl;
    std::cout << boxOct->volume() << std::endl;

    octree->scale(5);
    //octree->translate(glm::vec3(43, 13, -52));


    std::shared_ptr<VirtualObject> object = std::make_shared<InterceptableOctree>(octree,
                                                                                  std::make_shared<Phong>(
                                                                                          ColorVec(0.5, 0.5, 0.5), 1,
                                                                                          1, 25));
    //Raytracer::render1(object, "plane", 600, 600);
    Raytracer::render2(object, "plane2", 600, 600);
    //Raytracer::render3(object, "plane3", 600, 600);
    return 0;
}
