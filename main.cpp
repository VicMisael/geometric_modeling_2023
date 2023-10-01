#include <iostream>
#include "octree/octree.h"
#include "primitives/Sphere.h"
#include "primitives/Box.h"
#include "strippedRayTracer/RayTracerRedone/tracer/objects/VirtualObject.h"
#include "strippedRayTracer/RayTracerRedone/tracer/scene/materials/Phong.h"
#include "strippedRayTracer/RayTracerRedone/RayTracerRedone.cpp"
#include "rt_interface/InterceptableOctree.h"

void printOctreeInfos(const std::vector<std::shared_ptr<octree::Octree>>& octrees) {
    std::cout << "[";
    for (const auto &octree: octrees) {
        std::cout << octree->getName() << ", ";
    }
    std::cout << "]" << std::endl;
}

int main() {
    bool shouldQuit = false;
    std::vector<std::shared_ptr<octree::Octree>> octrees;
    while (!shouldQuit) {
        std::cout << "Modelador 1: Octree" << std::endl;
        std::cout << "Octrees Disponíveis" << std::endl;
        printOctreeInfos(octrees);
        std::cout << "Digite 1 para opções em octrees" << std::endl;
        std::cout << "Digite 2 para renderizar utilizando o Ray Tracer" << std::endl;
        std::cout << "Digite 3 para fazer o parse para string de alguma octree" << std::endl;
        std::cout << "Digite 4 para sair do modelador" << std::endl;
        int option;
        std::cin >> option;
        switch (option) {
            case 1: {
                break;
            }

            case 2: {
                break;
            };

            case 3: {
                break;
            }

            case 4: {
                shouldQuit = false;
                break;
            }

            default: {
                std::cout << "Opção Inválida" << std::endl;
            }
        }
        return 0;
    }
    auto sphere = std::make_shared<Sphere>();
    auto octree = std::make_shared<octree::Octree>(sphere, 9);

    //std::cout << octree->parse() << std::endl;
    std::cout << octree->volume() << std::endl;
    auto box = std::make_shared<Box>(glm::vec3(0, 0, 0), glm::vec3(30, 60, 20));
    auto boxOct = std::make_shared<octree::Octree>(box, 8);
    //std::cout << boxOct->parse() << std::endl;
    std::cout << boxOct->volume() << std::endl;

    const auto intersectionResult = octree->octreeUnion(boxOct);
    intersectionResult->scale(3);
    intersectionResult->translate(glm::vec3(0, 50, 0));

    std::cout << intersectionResult->parse() << std::endl;


    std::shared_ptr<VirtualObject> object = std::make_shared<InterceptableOctree>(intersectionResult,
                                                                                  std::make_shared<Phong>(
                                                                                          ColorVec(0.5, 0.5, 0.5), 1, 1,
                                                                                          25));

    //Raytracer::render1(object, "plane", 1600, 1600, 1);
    Raytracer::render2(object, "plane2", 600, 600, 20);
    //Raytracer::render3(object, "plane3", 1600, 1600, 1);
    return 0;
}
