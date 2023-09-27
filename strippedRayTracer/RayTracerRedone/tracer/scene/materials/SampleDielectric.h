//
// Created by Misael on 15/06/2023.
//

#pragma once
#include "Material.h"
class SampleDielectric: public Material{
    const float _reflectance;
    static double reflectance(double cosine, double ref_idx) {
        // Use Schlick's approximation for reflectance.
        auto r0 = (1-ref_idx) / (1+ref_idx);
        r0 = r0*r0;
        return r0 + (1-r0)*pow((1 - cosine),5);
    }

public:
    explicit SampleDielectric(float ref_):_reflectance(ref_){}
    ~SampleDielectric() override = default;

    [[nodiscard]] ColorVec shade(const World &world, const Ray &ray, const intersectionRec &intersection, int32_t depth) const override;

};
