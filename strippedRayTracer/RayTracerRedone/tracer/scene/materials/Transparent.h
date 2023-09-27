//
// Created by Misael on 16/06/2023.
//

#pragma once

#include "../BxDF/PerfectSpecular.h"
#include "../BxDF/PerfectTransmitter.h"
#include "Phong.h"

class Transparent: public Phong{
    PerfectSpecular reflective_brdf;
    PerfectTransmitter specular_btdf;
public:
    Transparent():Phong(Constants::BLACK,1,1,25),reflective_brdf(1.0f){
    };
    Transparent(float ior,float kt):Phong(Constants::BLACK,1,1,25),reflective_brdf(1.0f), specular_btdf(kt,ior){
    };
    [[nodiscard]] ColorVec shade(const World &world, const Ray &ray, const intersectionRec &intersection, int32_t depth) const override;

};



