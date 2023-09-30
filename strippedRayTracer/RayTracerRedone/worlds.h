//
// Created by Misael on 05/06/2023.
//

#pragma once

#include <glm/ext.hpp>
#include <random>

#include "tracer/scene/World.h"
#include "tracer/scene/World.h"
#include "tracer/objects/Plane.h"
#include "tracer/objects/Ball.h"
#include "tracer/objects/Disk.h"


#include "tracer/scene/Scene.h"
#include "tracer/scene/light/DirectionalLight.h"
#include "tracer/scene/light/PointLight.h"

#include "tracer/scene/materials/WhiteMetal.h"

#include "tracer/scene/materials/PhongReflective.h"
#include "tracer/scene/materials/PhongMetal.h"
#include "tracer/scene/materials/Matte.h"
#include "tracer/scene/materials/Mirror.h"
#include "tracer/scene/materials/Phong.h"
#include "tracer/scene/materials/TexturedPhong.h"
#include "tracer/scene/materials/TexturedMatte.h"
#include "tracer/scene/materials/TexturedMaterial.h"
#include "tracer/scene/materials/TexturedPhongReflective.h"
#include "tracer/scene/materials/BumpMapping.h"
#include "tracer/scene/materials/Diffuse.h"
#include "tracer/scene/materials/DiffuseLight.h"
#include "tracer/scene/materials/NullMaterial.h"

#include "tracer/scene/textures/CheckerTexture.h"
#include "tracer/scene/textures/PointCheckerTexture.h"
#include "tracer/scene/textures/ImageTexture.h"
#include "tracer/scene/materials/SampleDielectric.h"
#include "tracer/scene/materials/Dielectric.h"
#include "tracer/scene/materials/Transparent.h"

namespace worlds {

    World simpleScene(const std::shared_ptr<VirtualObject> &input) {
        std::vector<std::shared_ptr<VirtualObject>> objects;
        objects.push_back(input);
        const auto black_white_texture = std::make_shared<CheckerTexture>(Constants::YELLOW, Constants::WHITE, 10);
        const auto mirror = std::make_shared<Mirror>();
        const auto bw_matte_textured = std::make_shared<TexturedPhong>(black_white_texture, 1, 25);
        const auto ground_texture = std::make_shared<ImageTexture>("assets/textures/ground.jpg");
        const auto textured = std::make_shared<TexturedPhong>(ground_texture, 1, 25);
        const auto ground_bm = std::make_shared<ImageTexture>("assets/normalmaps/ground_bm.png");

        const auto textured_bp = std::make_shared<BumpMapping>(textured, ground_bm);
        const auto phong_reflective_higher_exp = std::make_shared<PhongReflective>(ColorVec(Constants::BLACK), 1, 25,
                                                                                   1);
        const auto phong_metal = std::make_shared<PhongMetal>(1.24);
        const auto building_material = std::make_shared<Phong>(ColorVec(0.5, 0.5, 0.5), 1, 1, 25);
        auto mat = Matrix4x4(1.0f);


        const auto soccerball_texture = std::make_shared<ImageTexture>("assets/textures/football-diffuse-512.png");
        const auto soccerball = std::make_shared<TexturedPhong>(soccerball_texture, 1, 2);
        const auto socceball_bm = std::make_shared<BumpMapping>(soccerball, std::make_shared<ImageTexture>(
                "assets/normalmaps/football-normals-512.png"));


        const auto vp = std::make_shared<ViewPlane>(15, 15, 10, 1);



        std::vector<std::shared_ptr<VectorialLight>> lights;

        std::vector<std::shared_ptr<AreaLight>> arealights;

        //Light 1

        auto diffuse_light = std::make_shared<DiffuseLight>(ColorVec(1, 1, 0.4), 1);
        //light2
        auto col = ColorVec(1, 1, 0.6);
        diffuse_light = std::make_shared<DiffuseLight>(col, 0.05);
        //auto light2 = std::make_shared<Ball>(Point3(-5900, 1690, 10090), 400, diffuse_light);
        auto light3 = std::make_shared<Ball>(Point3(-5900, 1690, -10090), 400, diffuse_light);

        //objects.push_back(light2);
        objects.push_back(light3);
        //arealights.push_back(std::make_shared<AreaLight>(light2));
        arealights.push_back(std::make_shared<AreaLight>(light3));


        auto world = World(vp, objects, lights, AmbientLight(0, ColorVec(1, 1, 1)), ColorVec(0.1, 0.1, 0.4), true);
        auto cam = std::make_shared<Camera>(Point3(90, 90, -150), Point3(-30, 0, 105), Vector3(0, 1, 0));
        world.withCamera(cam);
        world.withAreaLights(arealights);
        return world;
    }

    World buildingsScene(std::shared_ptr<VirtualObject> input) {
        std::vector<std::shared_ptr<VirtualObject>> objects;
        objects.push_back(input);
        const auto black_white_texture = std::make_shared<CheckerTexture>(Constants::YELLOW, Constants::WHITE, 10);
        const auto mirror = std::make_shared<Mirror>();
        const auto bw_matte_textured = std::make_shared<TexturedPhong>(black_white_texture, 1, 25);
        const auto ground_texture = std::make_shared<ImageTexture>("assets/textures/ground.jpg");
        const auto textured = std::make_shared<TexturedPhong>(ground_texture, 1, 25);
        const auto ground_bm = std::make_shared<ImageTexture>("assets/normalmaps/ground_bm.png");

        const auto textured_bp = std::make_shared<BumpMapping>(textured, ground_bm);
        const auto phong_reflective_higher_exp = std::make_shared<PhongReflective>(ColorVec(Constants::BLACK), 1, 25,
                                                                                   1);
        const auto phong_metal = std::make_shared<PhongMetal>(1.24);
        const auto building_material = std::make_shared<Phong>(ColorVec(0.5, 0.5, 0.5), 1, 1, 25);
        auto mat = Matrix4x4(1.0f);


        const auto vp = std::make_shared<ViewPlane>(15, 15, 10, 1);

        objects.push_back(std::make_shared<Ball>(Point3(40, 30, 105), 25,
                                                 phong_reflective_higher_exp));
        constexpr float a = 100000;
        objects.push_back(std::make_shared<Ball>(Point3(0,-a,0), a, building_material));

        std::vector<std::shared_ptr<VectorialLight>> lights;

        std::vector<std::shared_ptr<AreaLight>> arealights;

        //Light 1

        auto diffuse_light = std::make_shared<DiffuseLight>(ColorVec(1, 1, 0.4), 1);
        //light2
        auto col = ColorVec(1, 1, 0.6);
        diffuse_light = std::make_shared<DiffuseLight>(col, 0.05);


        auto light3 = std::make_shared<Ball>(Point3(-5900, 1690, -10090), 400, diffuse_light);

        //objects.push_back(light2);
        objects.push_back(light3);
        //arealights.push_back(std::make_shared<AreaLight>(light2));
        arealights.push_back(std::make_shared<AreaLight>(light3));



        auto world = World(vp, objects, lights, AmbientLight(0, ColorVec(1, 1, 1)), ColorVec(0.1, 0.1, 0.4), true);
        auto cam = std::make_shared<Camera>(Point3(90, 90, -250), Point3(-30, 0, 105), Vector3(0, 1, 0));
        world.withCamera(cam);
        world.withAreaLights(arealights);
        return world;

    };

    World buildingsScene2(std::shared_ptr<VirtualObject> input) {
        std::vector<std::shared_ptr<VirtualObject>> objects;
        objects.push_back(input);
        const auto black_white_texture = std::make_shared<CheckerTexture>(Constants::YELLOW, Constants::WHITE, 10);
        const auto mirror = std::make_shared<Mirror>();
        const auto bw_matte_textured = std::make_shared<TexturedPhong>(black_white_texture, 1, 25);
        const auto ground_texture = std::make_shared<ImageTexture>("assets/textures/ground.jpg");
        const auto textured = std::make_shared<TexturedPhong>(ground_texture, 1, 25);
        const auto ground_bm = std::make_shared<ImageTexture>("assets/normalmaps/ground_bm.png");

        const auto textured_bp = std::make_shared<BumpMapping>(textured, ground_bm);
        const auto phong_reflective_higher_exp = std::make_shared<PhongReflective>(ColorVec(Constants::BLACK), 1, 25,
                                                                                   1);
        const auto phong_metal = std::make_shared<PhongMetal>(1.24);
        const auto building_material = std::make_shared<Phong>(ColorVec(0.5, 0.5, 0.5), 1, 1, 25);
        auto mat = Matrix4x4(1.0f);

        objects.push_back(std::make_shared<Plane>(Point3(0, 0, 0), Vector3(0, 1, 0), textured_bp));


        const auto soccerball_texture = std::make_shared<ImageTexture>("assets/textures/football-diffuse-512.png");
        const auto soccerball = std::make_shared<TexturedPhong>(soccerball_texture, 1, 2);
        const auto socceball_bm = std::make_shared<BumpMapping>(soccerball, std::make_shared<ImageTexture>(
                "assets/normalmaps/football-normals-512.png"));

        objects.push_back(std::make_shared<Ball>(Point3(-20, 25, 40), 10, socceball_bm));

        const auto vp = std::make_shared<ViewPlane>(15, 15, 10, 1);

        objects.push_back(std::make_shared<Ball>(Point3(40, 30, 105), 25,
                                                 phong_reflective_higher_exp));
        constexpr float a = 100000;
        //objects.push_back(std::make_shared<Ball>(Point3(0,-a,0), a, building_material));

        std::vector<std::shared_ptr<VectorialLight>> lights;

        std::vector<std::shared_ptr<AreaLight>> arealights;

        //Light 1

        auto diffuse_light = std::make_shared<DiffuseLight>(ColorVec(1, 1, 0.4), 1);
        //light2
        auto col = ColorVec(1, 1, 0.6);
        diffuse_light = std::make_shared<DiffuseLight>(col, 0.05);


        auto light3 = std::make_shared<Ball>(Point3(-5900, 1690, -10090), 400, diffuse_light);

        //objects.push_back(light2);
        objects.push_back(light3);
        //arealights.push_back(std::make_shared<AreaLight>(light2));
        arealights.push_back(std::make_shared<AreaLight>(light3));



        auto world = World(vp, objects, lights, AmbientLight(0, ColorVec(1, 1, 1)), ColorVec(0.1, 0.1, 0.4), true);
        auto cam = std::make_shared<Camera>(Point3(90, 90, -150), Point3(-30, 0, 105), Vector3(0, 1, 0));
        world.withCamera(cam);
        world.withAreaLights(arealights);
        return world;

    };
}