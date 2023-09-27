#pragma once

#include <iostream>
#include <utility>
#include <vector>
#include "Canvas.h"
#include "ViewPlane.h"
#include "light/AmbientLight.h"
#include "../utils/sampler/sampler.h"
#include "../objects/VirtualObject.h"
#include "light/VectorialLight.h"
#include "light/AreaLight.h"
#include "Camera.h"
#include "../utils/utility.h"


class World {
private:

    [[nodiscard]] ColorVec shade(const intersectionRec &, const Ray &, const int32_t depth) const;

    std::shared_ptr<ViewPlane> viewPlane;
    std::vector<std::shared_ptr<VirtualObject>> objects_;
    std::vector<std::shared_ptr<VectorialLight>> lights_;
    std::vector<std::shared_ptr<AreaLight>> areaLights_;
    ColorVec bgColor;
    AmbientLight ambient_light;
    std::shared_ptr<Camera> camera;
    //std::shared_ptr<BVH> bvh;
    bool perspective_{};
    static void printAreas(const std::vector<std::shared_ptr<VirtualObject>> &objects) {
        for (const auto &obj: objects) {

            std::cout << "The area of the object " << typeid(*obj).name() << " is:" << obj->getArea() << std::endl;
        }
    }
public:
    [[nodiscard]] ColorVec trace_ray(const Ray &ray, const int32_t depth) const;

    [[nodiscard]] ColorVec trace_ray(const Ray &ray, float &tmin, const int32_t depth) const;


    World(std::shared_ptr<ViewPlane> _viewPlane,
          std::vector<std::shared_ptr<VirtualObject>> _objects,
          std::vector<std::shared_ptr<VectorialLight>> lights,
          AmbientLight _ambient_light,
          ColorVec _bgColor,
          bool perspective) :
            viewPlane(std::move(_viewPlane)),
            objects_(std::move(_objects)),
            lights_(std::move(lights)),
            bgColor(_bgColor),
            ambient_light(std::move(_ambient_light)), perspective_(perspective) {
        //bvh = std::make_shared<BVH>(objects_);
        camera = std::make_shared<Camera>();
    }


    void withCamera(std::shared_ptr<Camera> camera) {
        this->camera=camera;
    }

    void withAreaLights(std::vector<std::shared_ptr<AreaLight>> _areaLights) {
        areaLights_ = std::move(_areaLights);
    }

    void render(Canvas *, int32_t, const std::shared_ptr<sampler> &);

    void render(Canvas *, int32_t, const std::shared_ptr<sampler> &, std::shared_ptr<Camera> &camera);


    [[nodiscard]] std::optional<intersectionRec> hit(const Ray &ray) const;

    [[nodiscard]] std::vector<std::shared_ptr<VectorialLight>> lights() const {
        return lights_;
    }

    [[nodiscard]] std::vector<std::shared_ptr<AreaLight>> areaLights() const {
        return areaLights_;
    }

    [[nodiscard]] AmbientLight getAmbientLight() const {
        return ambient_light;
    }

    void
    draw_pixel(Canvas *canvas, int32_t depth, const Matrix4x4 &inv, const float ystep, const float xstep,
               const float zw,
               const std::vector<std::tuple<float, float>> &points, const unsigned int &num_samples, uint16_t y,
               uint16_t x) const;
};
