//
// Created by Misael on 04/07/2023.
//

#pragma once

#include "VectorialLight.h"
#include "../../objects/VirtualObject.h"

//DONT USE THIS
class AreaLight : public Light {
private:

    std::shared_ptr<VirtualObject> object;
    struct AreaLightState {
        Vector3 sample_point;
        Vector3 normal_at_point;
        Vector3 wi;
    };
public:

    AreaLight() = delete;

    AreaLight( const std::shared_ptr<VirtualObject> &object);
    //Do not store state in a class
    //May cause race condition when Multithreading

    AreaLightState generateState(Point3 hitpoint) const;

    float pdf() const;


    [[nodiscard]] const std::shared_ptr<VirtualObject> &getObject() const {
        return object;
    }

    virtual Vector3 getVectorNormalized(AreaLightState areaLightState) const;

    bool casts_shadow() {
        return true;
    }

    [[nodiscard]] ColorVec intensityAtPoint(const Point3 p, const AreaLightState& areaLightState) const;

    [[nodiscard]] float G(const Point3 hitpoint, const AreaLightState& areaLightState) const;

    [[nodiscard]] bool shadow_hit(const World &world, const Ray &outgoing, const AreaLightState&) const;


};
