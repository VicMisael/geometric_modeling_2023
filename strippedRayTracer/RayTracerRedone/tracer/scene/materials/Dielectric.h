//
// Created by Misael on 23/06/2023.
//

#pragma once

#include "Phong.h"
#include "../BxDF/FresnelReflector.h"
#include "../BxDF/FresnelTransmitter.h"

class Dielectric: public Phong {
    const FresnelReflector fresnel_brdf;
    const FresnelTransmitter fresnel_btdf;
    const ColorVec cf_in;
    const ColorVec cf_out;
public:
    ~Dielectric() override = default;
    Dielectric(ColorVec cf_in_,ColorVec cf_out_,float n_in,float n_out,float ks,float exp): Phong(Constants::WHITE,ks,exp),
                                                                                            fresnel_brdf(), fresnel_btdf(n_in,n_out),cf_in(cf_in_),cf_out(cf_out_){
    }
    Dielectric(ColorVec cf_in_,ColorVec cf_out_): Dielectric(cf_in_,cf_out_,1,1,0.2,25){}
    [[nodiscard]] ColorVec
    shade(const World &world, const Ray &ray, const intersectionRec &intersection, int32_t depth) const override;

};


