#include <iostream>
#include <fstream>
#include "octree/octree.h"
#include "primitives/Sphere.h"
#include "primitives/Box.h"
#include "strippedRayTracer/RayTracerRedone/tracer/objects/VirtualObject.h"
#include "strippedRayTracer/RayTracerRedone/tracer/scene/materials/Phong.h"
#include "strippedRayTracer/RayTracerRedone/RayTracerRedone.cpp"
#include "rt_interface/InterceptableOctree.h"

void printOctreeInfos(const std::vector<std::shared_ptr<octree::Octree>> &octrees) {
    std::cout << "[";
    int id = 0;
    for (const auto &octree: octrees) {
        std::cout << "id: " << id++ << " " << octree->getName() << ", ";
    }
    std::cout << "]" << std::endl;
}

std::shared_ptr<octree::Octree> octreeOfObject() {
    std::cout << "Digite 1 para criar uma esfera" << std::endl;
    std::cout << "Digite 2 para criar um cubo " << std::endl;
    int option = 0;
    std::cin >> option;
    std::shared_ptr<Primitive> primitive;
    bool opcaoInvalida = false;
    switch (option) {
        case 1: {
            primitive = std::make_shared<Sphere>();
            break;
        }

        case 2: {
            float height;
            float width;
            float depth;
            std::cout << "Digite as dimensões do cubo" << std::endl;
            std::cout << "Insira a altura" << std::endl;

            std::cin >> height;
            std::cout << "Insira a largura" << std::endl;
            std::cin >> width;
            std::cout << "Insira a profundidade" << std::endl;
            std::cin >> depth;
            primitive = std::make_shared<Box>(width, height, depth);
            break;
        }

        default: {
            opcaoInvalida = true;
            std::cout << "Opção Inválida" << std::endl;
        }
    }
    if (!opcaoInvalida) {
        std::cout << "Digite a profundidade desejada da octree" << std::endl;
        int depth = 0;
        std::cin >> depth;
        return std::make_shared<octree::Octree>(primitive, depth);
    }
    return nullptr;

}

void octreeOptions(std::vector<std::shared_ptr<octree::Octree>> &octrees) {
    std::cout << "Digite 1 para exibir a lista de octrees" << std::endl;
    std::cout << "Digite 2 para criar uma nova octree " << std::endl;
    std::cout << "Digite 3 para fazer uma operação booleana entre duas Octrees existentes" << std::endl;
    int option = 0;
    std::cin >> option;
    switch (option) {
        case 1: {
            printOctreeInfos(octrees);
            break;
        }

        case 2: {
            const auto object = octreeOfObject();
            if (object != nullptr) {
                octrees.push_back(object);
            }
            break;
        }

        case 3: {
            std::cout << "Digite o id da primeira primitiva" << std::endl;
            int idfirst = 0;
            std::cin >> idfirst;
            std::cout << "Digite o id da segunda primitiva" << std::endl;
            int idsecond = 0;
            std::cin >> idsecond;
            if (idfirst < octrees.size() && idsecond < octrees.size()) {
                std::cout << "Digite 1 para união " << std::endl;
                std::cout << "Digite 2 para interseção " << std::endl;
                int operation = 0;
                std::cin >> operation;
                switch (operation) {
                    case 1:
                        octrees.push_back(octrees[idfirst]->octreeUnion(octrees[idsecond]));
                        break;
                    case 2:
                        octrees.push_back(octrees[idfirst]->octreeIntersection(octrees[idsecond]));
                        break;
                    default:
                        std::cout << "Operação inválida";
                }
            }
            break;
        }
        default: {
            std::cout << "Opção Inválida" << std::endl;
        }

    }

};

void render(std::vector<std::shared_ptr<octree::Octree>> &octrees) {
    std::cout << "Digite o id da Octree à ser renderizada" << std::endl;
    int option = 0;
    std::cin >> option;

    if (option < octrees.size()) {
        std::cout << "Digite o nome do arquivo" << std::endl;
        std::string name;
        std::cin >> name;
        const auto octree = octrees[option];
        const auto standardizedRoot = octree::Node::standardize(octree->rootNode);
        auto result = std::make_shared<octree::Octree>(standardizedRoot);
        result->scale(3);
        result->translate(glm::vec3(0, 60, 0));
        std::shared_ptr<VirtualObject> object = std::make_shared<InterceptableOctree>(result,
                                                                                      std::make_shared<Phong>(
                                                                                              ColorVec(0.5, 0.5, 0.5),
                                                                                              1, 1,
                                                                                              25));
        std::cout << "Cena 1" << std::endl;
        std::cout << "Cena 2" << std::endl;
        std::cout << "Cena 3" << std::endl;
        int scene = 0;
        std::cin >> scene;
        switch (scene) {
            default:
            case 1:
                Raytracer::render1(object, name, 1600, 1600, 10);
                break;
            case 2:
                Raytracer::render2(object, name, 600, 600, 20);
                break;
            case 3:
                Raytracer::render3(object, name, 1600, 1600, 10);
                break;
        }


    } else {
        std::cout << "Opção inválida" << std::endl;
    }


};

void parse(std::vector<std::shared_ptr<octree::Octree>> &octrees) {
    std::cout << "Digite o id da Octree à ser renderizada" << std::endl;
    int option = 0;
    std::cin >> option;
    std::cout << "Digite o nome do arquivo" << std::endl;
    std::string name;
    std::cin >> name;
    if (option < octrees.size()) {
        const auto octree = octrees[option];
        std::ofstream out(name + ".txt");
        out << octree->parse();
        out.close();
    }

};

void transformObject(std::vector<std::shared_ptr<octree::Octree>> &octrees) {
    std::cout << "Digite a transformação que deseja fazer" << std::endl;
    std::cout << "1 para escala" << std::endl;
    std::cout << "2 para translação" << std::endl;
    int transform = 0;
    std::cin >> transform;
    switch (transform) {
        case 1: {
            std::cout << "Digite o id da Octree à ser transformada" << std::endl;
            int option = 0;
            std::cin >> option;

            if (option < octrees.size()) {
                const auto octree = octrees[option];
                std::cout << "Digite o tamanho da escal" << std::endl;
                float scale = 0;
                std::cin >> scale;
                octree->scale(scale);
            }
        }
            break;
        case 2: {
            std::cout << "Digite o id da Octree à ser transformada" << std::endl;
            int option = 0;
            std::cin >> option;

            if (option < octrees.size()) {
                const auto octree = octrees[option];
                std::cout << "o valor do x" << std::endl;
                float x = 0;
                std::cin >> x;
                std::cout << "o valor do y" << std::endl;
                float y = 0;
                std::cin >> y;
                std::cout << "o valor do z" << std::endl;
                float z = 0;
                std::cin >> z;
                octree->translate(glm::vec3(x, y, z));
            }

        }
            break;
        default:
            std::cout << "Operação Inválida" << std::endl;
            break;
    }
}

int main() {
    std::vector<std::shared_ptr<octree::Octree>> octrees;
    std::cout << "Modelador 1: Octree" << std::endl;
    while (true) {
        std::cout << "Octrees Disponíveis" << std::endl;
        printOctreeInfos(octrees);
        std::cout << "Digite 1 para opções em octrees" << std::endl;
        std::cout << "Digite 2 para renderizar utilizando o Ray Tracer" << std::endl;
        std::cout << "Digite 3 para fazer o parse para string de alguma octree" << std::endl;
        std::cout << "Digite 4 para informações da Octree " << std::endl;
        std::cout << "Digite 5 para transformações na octree" << std::endl;
        std::cout << "Digite 7 para sair do modelador" << std::endl;
        int option;
        std::cin >> option;
        switch (option) {
            case 1: {
                octreeOptions(octrees);
                break;
            }

            case 2: {
                render(octrees);
                break;
            }

            case 3: {
                parse(octrees);
                break;
            }
            case 4: {
                std::cout << "digite o id da árvore na qual deseja consultar informações" << std::endl;
                int octree = 0;
                std::cin >> octree;
                if (octree < octrees.size()) {
                    const auto result = octrees[octree];
                    std::cout << "Profundidade: " << result->depth() << std::endl;
                    std::cout << "Volume: " << result->volume() << std::endl;
                }
            }
                break;
            case 5: {
                transformObject(octrees);

            }
                break;
            case 7: {
                return 0;
            }

            default: {
                std::cout << "Opção Inválida" << std::endl;
            }
        }

    }

//    auto sphere = std::make_shared<Sphere>();
//    auto octree = std::make_shared<octree::Octree>(sphere, 9);
//
//    //std::cout << octree->parse() << std::endl;
//    std::cout << octree->volume() << std::endl;
//    auto box = std::make_shared<Box>(30, 60, 20);
//    auto boxOct = std::make_shared<octree::Octree>(box, 8);
//    //std::cout << boxOct->parse() << std::endl;
//    std::cout << boxOct->volume() << std::endl;
//
//    const auto intersectionResult = octree->octreeUnion(boxOct);
//    intersectionResult->scale(3);
//    intersectionResult->translate(glm::vec3(0, 50, 0));
//
//    std::cout << intersectionResult->parse() << std::endl;
//
//
//    std::shared_ptr<VirtualObject> object = std::make_shared<InterceptableOctree>(intersectionResult,
//                                                                                  std::make_shared<Phong>(
//                                                                                          ColorVec(0.5, 0.5, 0.5), 1, 1,
//                                                                                          25));
//
//    //Raytracer::render1(object, "plane", 1600, 1600, 1);
//    Raytracer::render2(object, "plane2", 600, 600, 20);
//    //Raytracer::render3(object, "plane3", 1600, 1600, 1);
    return 0;
}
