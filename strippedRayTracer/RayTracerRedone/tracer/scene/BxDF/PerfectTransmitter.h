//
// Created by Misael on 16/06/2023.
//

#pragma once


#include "BTDF.h"

class PerfectTransmitter : public BTDF {

    float ior = 1.0f;  // index of refraction
    float kt = 0.0f;    // transmission coefficient;
public:
    PerfectTransmitter(float kt, float ior) : ior(ior), kt(kt){

    }

    PerfectTransmitter() {

    }

public:
    [[nodiscard]] ColorVec rho(const Vector3 &wo) const override;

    [[nodiscard]] ColorVec f(const intersectionRec &intersection, const Vector3 &wo, const Vector3 &wi) const override;

    [[nodiscard]] sample_f_out sample_f(const intersectionRec &intersection, const Vector3 &wo) const override;

    float internal_reflection(const Vector3 &wo, const intersectionRec &intersection) const override;

};

