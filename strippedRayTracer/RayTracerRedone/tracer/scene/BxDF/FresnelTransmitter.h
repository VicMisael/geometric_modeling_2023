//
// Created by Misael on 16/06/2023.
//
#pragma once

#include "BTDF.h"

class FresnelTransmitter: public BTDF {
    float n_in;
    float n_out;
    [[nodiscard]] float fresnel(const Vector3 &wo, const intersectionRec& intersection) const;
public:
    FresnelTransmitter(float nIn, float nOut) : n_in(nIn), n_out(nOut) {}

    float internal_reflection(const Vector3 &wo, const intersectionRec &intersection) const override;

     [[nodiscard]] ColorVec rho(const Vector3 &wo) const override;

    [[nodiscard]] ColorVec f(const intersectionRec &intersection, const Vector3 &wo, const Vector3 &wi) const override;

    [[nodiscard]] sample_f_out sample_f(const intersectionRec &intersection, const Vector3 &wo) const override;

};

