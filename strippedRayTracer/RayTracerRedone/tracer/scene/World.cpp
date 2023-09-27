
#include "World.h"

#include <thread>

#include "Camera.h"
#include <glm/common.hpp>
#include <glm/vector_relational.hpp>


static int i = 0;

ColorVec World::trace_ray(const Ray &ray, const int32_t depth) const {
    float t = 0;
    return World::trace_ray(ray, t, depth);
}

ColorVec World::shade(const intersectionRec &intersection, const Ray &ray, const int32_t depth) const {
    return intersection.material->shade(*this, ray, intersection, depth);
}


void World::render(Canvas *canvas, const int32_t depth, const std::shared_ptr<sampler> &_sampler) {
    this->render(canvas, depth, _sampler, this->camera);
}

std::optional<intersectionRec> World::hit(const Ray &ray) const {
    //return bvh->intersects(ray);
    float t_min = Constants::MAX_FLOAT;
    std::optional<intersectionRec> selintersection;
    for (const std::shared_ptr<VirtualObject> &object: objects_) {
        const auto intersectsoptional = object->intersects(ray);
        if (intersectsoptional.has_value()) {
            const auto &intersects = *intersectsoptional;
            if (intersects.tmin < t_min && intersects.tmin > 1) {
                t_min = intersects.tmin;
                selintersection.emplace(intersects);
            }
        }
    }
    return selintersection;
}

ColorVec World::trace_ray(const Ray &ray, float &tmin, const int32_t depth) const {
    if (depth >= 0) {
        const auto intersection = hit(ray);
        if (intersection.has_value()) {
            tmin = intersection->tmin;
            return shade(intersection.value(), ray, depth);
        }
        return bgColor;
    }
    return {0, 0, 0};
}

void
World::render(Canvas *canvas, int32_t depth, const std::shared_ptr<sampler> &_sampler, std::shared_ptr<Camera> &camera) {

    auto inv = camera->getLookAtInverse();
    const uint32_t height = canvas->getHeight();
    const uint32_t width = canvas->getWidth();
    const float ystep = canvas->step_size_y(viewPlane);
    const float xstep = canvas->step_size_x(viewPlane);
    const float zw = viewPlane->zw;
    const auto &points = _sampler->generate_points();
    const auto &num_samples = _sampler->num_samples;
    
//    auto drawblock1 = [&] {
//        for (uint16_t y = 0; y < height / 4; y++) {
//            for (uint16_t x = 0; x < width; x++) {
//                draw_pixel(canvas, depth, inv, ystep, xstep, zw, points, num_samples, y, x);
//            }
//        }
//    };
//
//    auto drawblock2 = [&] {
//        for (uint16_t y = height / 4; y < 2 * height / 4; y++) {
//            for (uint16_t x = 0; x < width; x++) {
//                draw_pixel(canvas, depth, inv, ystep, xstep, zw, points, num_samples, y, x);
//            }
//        }
//    };
//    auto drawblock3 = [&] {
//        for (uint16_t y = 2 * height / 4; y < 3 * height / 4; y++) {
//            for (uint16_t x = 0; x < width; x++) {
//                draw_pixel(canvas, depth, inv, ystep, xstep, zw, points, num_samples, y, x);
//            }
//        }
//    };
//    auto drawblock4 = [&] {
//        for (uint16_t y = 3 * height / 4; y < height; y++) {
//            for (uint16_t x = 0; x < width; x++) {
//                draw_pixel(canvas, depth, inv, ystep, xstep, zw, points, num_samples, y, x);
//            }
//        }
//    };
//    std::thread t1(drawblock1);
//    std::thread t2(drawblock2);
//    std::thread t3(drawblock3);
//    std::thread t4(drawblock4);
//    t1.join();
//    t2.join();
//    t3.join();
//    t4.join();

    for (uint16_t y = 0; y < height; y++) {
        for (uint16_t x = 0; x < width; x++) {
            draw_pixel(canvas, depth, inv, ystep, xstep, zw, points, num_samples, y, x);
        }
    }

    
}

inline void World::draw_pixel(Canvas *canvas, int32_t depth, const Matrix4x4 &inv, const float ystep, const float xstep,
                       const float zw, const std::vector<std::tuple<float, float>> &points,
                       const unsigned int &num_samples, uint16_t y, uint16_t x) const {
    ColorVec colorVec(0, 0, 0);
    for (const std::tuple<float, float> &sample_point: points) {
        auto [x_sample_point, y_sample_point] = sample_point;
        const auto vp_y = ystep * y;
        const auto vp_x = xstep * x;

        x_sample_point *= xstep;
        y_sample_point *= ystep;
        ColorVec actualColor;
        if (perspective_) {
            const float y_coord = viewPlane->pixelsize * (vp_y - 0.5f * (viewPlane->hsize - 1.0f));
            const float x_coord = viewPlane->pixelsize * (vp_x - 0.5f * (viewPlane->wsize - 1.0f));
            const Vector3 vp_r(x_coord + x_sample_point, y_coord + y_sample_point, zw);
            Point3 origin(0, 0, 0);
            Vector3 direction = origin - vp_r;

            origin = Vector3(inv * Vector4(origin, 1));
            direction = Vector3(inv * Vector4(direction, 0));

            const Ray r(origin, direction);
            actualColor = trace_ray(r, depth);
            //canvas->write_pixel(x, y, ColorRGBA(trace_ray(r, 0)));
        } else {
            const float y_coord = viewPlane->pixelsize * (vp_y - 0.5f * (viewPlane->hsize - 1.0f));
            const float x_coord = viewPlane->pixelsize * (vp_x - 0.5f * (viewPlane->wsize - 1.0f));
            Vector3 vp_r(x_coord + x_sample_point, -y_coord + y_sample_point, zw);
            vp_r = Vector3(inv * Vector4(vp_r, 1));
            auto dir = Vector3(inv * Vector4(Vector3(0, 0, -1), 0));
            const Ray r(vp_r, dir);
            actualColor = trace_ray(r, depth);
            //canvas->write_pixel(x, y, ColorRGBA(trace_ray(r, 0)));
        }
        actualColor.fixNans();
        colorVec += actualColor;
    }
    const ColorVec out = (colorVec * 1.0f / static_cast<float>(num_samples));
    canvas->write_pixel(x, y, ColorRGBA(out));
}
