
#include <iostream>
#include <glm/vec3.hpp>
#include "octree/octree.h"
#include "primitives/Sphere.h"

int main() {
    auto sphere = std::make_shared<Sphere>(glm::vec3(0, 0, 0), 10);
    auto octree = octree::Octree(sphere, 10);
    std::cout << octree.parse() << std::endl;
    return 0;
}
