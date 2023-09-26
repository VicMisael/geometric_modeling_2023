
#include <iostream>
#include "octree/octree.h"
#include "primitives/Sphere.h"
#include "primitives/Box.h"

int main() {
    auto sphere = std::make_shared<Sphere>(glm::vec3(0, 0, 0), 1);
    auto octree = octree::Octree(sphere, 6);
    //std::cout << octree.parse() << std::endl;
    std::cout << octree.volume() << std::endl;
    auto box = std::make_shared<Box>(glm::vec3(0, 1, 0), glm::vec3(9, 10, 10));
    auto boxOct = octree::Octree(box,8);
    //std::cout << boxOct.parse() << std::endl;
    std::cout << boxOct.volume() << std::endl;
    return 0;
}
