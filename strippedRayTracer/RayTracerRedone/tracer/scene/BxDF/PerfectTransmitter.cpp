//
// Created by Misael on 16/06/2023.
//

#include "PerfectTransmitter.h"

ColorVec PerfectTransmitter::rho(const Vector3 &wo) const {
    return Constants::BLACK;
}

ColorVec PerfectTransmitter::f(const intersectionRec &intersection, const Vector3 &wo, const Vector3 &wi) const {
    return Constants::BLACK;
}

sample_f_out PerfectTransmitter::sample_f(const intersectionRec &intersection, const Vector3 &wo) const {
    Vector3 normal(intersection.normal);
    float cos_thetai = dot(normal, wo);
    float eta = ior;

    if (cos_thetai < 0.0f) {  // transmitted ray is outside
        cos_thetai = -cos_thetai;
        normal = -normal;            // reverse direction of normal
        eta = 1.0f / eta;  // invert ior
    }

    float temp = 1.0f - (1.0f - cos_thetai * cos_thetai) / (eta * eta);
    float cos_theta2 = sqrt(temp);
    Vector3 wt = -wo / eta - (cos_theta2 - cos_thetai / eta) * normal;

    float k = 1.0f / (fabs(dot(normal, wt)));
    return {(kt / (eta * eta)) * Constants::WHITE * k, wt, 0};
}

float PerfectTransmitter::internal_reflection(const Vector3 &wo, const intersectionRec &intersection) const {


    float cos_thetai = dot(intersection.normal, -wo);
    float eta = ior;

    if (cos_thetai < 0.0f) {
        eta = 1.0f / eta;
    }

    return 1.0f - (1.0f - cos_thetai * cos_thetai) / (eta * eta);
}


