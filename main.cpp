
#include <iostream>
#include "octree/octree.h"
#include "primitives/Sphere.h"
#include "primitives/Box.h"
#include "strippedRayTracer/RayTracerRedone/tracer/objects/VirtualObject.h"
#include "strippedRayTracer/RayTracerRedone/tracer/scene/materials/Phong.h"
#include "strippedRayTracer/RayTracerRedone/RayTracerRedone.cpp"
#include "rt_interface/InterceptableOctree.h"

int main() {
    auto sphere = std::make_shared<Sphere>(glm::vec3(0, 30, 0), 20);
    auto octree = std::make_shared<octree::Octree>(sphere, 4);
    std::cout << octree->parse() << std::endl;
    std::cout << octree->volume() << std::endl;
    auto box = std::make_shared<Box>(glm::vec3(-50, 0, -50), glm::vec3(50, 50, 50));
    auto boxOct = std::make_shared<octree::Octree>(box, 3);
    std::cout << boxOct->parse() << std::endl;
    std::cout << boxOct->volume() << std::endl;

    std::shared_ptr<VirtualObject> object = std::make_shared<InterceptableOctree>(octree,
                                                                                  std::make_shared<Phong>(
                                                                                          ColorVec(0.5, 0.5, 0.5), 1,
                                                                                          1, 25));
    Raytracer::render(object, 1300, 1300);
    return 0;
}
