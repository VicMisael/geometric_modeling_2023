// RayTracerRedone.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//
#pragma once

#include <iostream>


#include <thread>
#include <utility>
#include "tracer/scene/Scene.h"
#include "imageoutputcanvas/imagecanvas.h"
#include "worlds.h"


#include "tracer/utils/sampler/mt19937_point_sampler.h"

static std::shared_ptr<sampler> generateSampler(const int numsamples) {
    return std::make_shared<mt19937_point_sampler>(numsamples);
}

namespace Raytracer {
    void render1(std::shared_ptr<VirtualObject> object, std::string filename, const uint32_t w, const uint32_t h,const uint32_t samples) {


        const auto sampler = generateSampler(samples);

//    std::shared_ptr<VirtualObject> object = std::make_shared<Ball>(Point3(0, 0, 0), 50,
//                                                                   std::make_shared<Phong>(ColorVec(0.5, 0.5, 0.5), 1,
//                                                                                           1, 25));
        auto selectedWorld = worlds::buildingsScene(object);


        auto *drawcanvas = new imagecanvas(w, h, std::move(filename));

        constexpr int32_t recursion_depth_limit = 4;

        Scene scene(selectedWorld, drawcanvas);
        //auto cam = std::make_shared<Camera>(Point3(690, 710, 180), Point3(40, 30, 105), Vector3(0, 1, 0));

        auto t1 = std::chrono::high_resolution_clock::now();
        scene.render(recursion_depth_limit, sampler);

        auto t2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> ms_double = t2 - t1;
        const auto seconds = ms_double.count() / 1000;

        scene.draw();

        std::cout << " Took";
        std::cout << seconds << "s" << std::endl;


    }

    void render2(std::shared_ptr<VirtualObject> object, std::string filename, const uint32_t w, const uint32_t h,const uint32_t samples) {


        const auto sampler = generateSampler(samples);

        auto selectedWorld = worlds::simpleScene(object);


        auto *drawcanvas = new imagecanvas(w, h, std::move(filename));

        constexpr int32_t recursion_depth_limit = 4;

        Scene scene(selectedWorld, drawcanvas);
        //auto cam = std::make_shared<Camera>(Point3(690, 710, 180), Point3(40, 30, 105), Vector3(0, 1, 0));

        auto t1 = std::chrono::high_resolution_clock::now();
        scene.render(recursion_depth_limit, sampler);

        auto t2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> ms_double = t2 - t1;
        const auto seconds = ms_double.count() / 1000;

        scene.draw();

        std::cout << " Took";
        std::cout << seconds << "s" << std::endl;


    }

    void render3(std::shared_ptr<VirtualObject> object, std::string filename, const uint32_t w, const uint32_t h,const uint32_t samples) {


        const auto sampler = generateSampler(samples);

        auto selectedWorld = worlds::buildingsScene2(object);


        auto *drawcanvas = new imagecanvas(w, h, std::move(filename));

        constexpr int32_t recursion_depth_limit = 2;

        Scene scene(selectedWorld, drawcanvas);
        //auto cam = std::make_shared<Camera>(Point3(690, 710, 180), Point3(40, 30, 105), Vector3(0, 1, 0));

        auto t1 = std::chrono::high_resolution_clock::now();
        scene.render(recursion_depth_limit, sampler);

        auto t2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> ms_double = t2 - t1;
        const auto seconds = ms_double.count() / 1000;

        scene.draw();

        std::cout << " Took";
        std::cout << seconds << "s" << std::endl;


    }
}


// Executar programa: Ctrl + F5 ou Menu Depurar > Iniciar Sem Depuração
// Depurar programa: F5 ou menu Depurar > Iniciar Depuração

// Dicas para Começar: 
//   1. Use a janela do Gerenciador de Soluções para adicionar/gerenciar arquivos
//   2. Use a janela do Team Explorer para conectar-se ao controle do código-fonte
//   3. Use a janela de Saída para ver mensagens de saída do build e outras mensagens
//   4. Use a janela Lista de Erros para exibir erros
//   5. Ir Para o Projeto > Adicionar Novo Item para criar novos arquivos de código, ou Projeto > Adicionar Item Existente para adicionar arquivos de código existentes ao projeto
//   6. No futuro, para abrir este projeto novamente, vá para Arquivo > Abrir > Projeto e selecione o arquivo. sln
