
#include <iostream>
#include "octree/octree.h"
#include "primitives/Sphere.h"
#include "primitives/Box.h"

int main() {
    auto sphere = std::make_shared<Sphere>(glm::vec3(0, 0, 0), 2.9);
    auto octree = octree::Octree(sphere, 7);
    std::cout << octree.parse() << std::endl;
    auto box = std::make_shared<Box>(glm::vec3(-10, -10, -10), glm::vec3(10, 10, 10));
    auto boxOct = octree::Octree(box, 7);
    std::cout << boxOct.parse() << std::endl;
    return 0;
}
