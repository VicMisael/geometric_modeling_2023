#include "FresnelReflector.h"


ColorVec FresnelReflector::rho(const Vector3 &wo) const {
    return Constants::BLACK;;
}

ColorVec FresnelReflector::f(const intersectionRec &intersection, const Vector3 &wo, const Vector3 &wi) const {
    return Constants::BLACK;
}

sample_f_out FresnelReflector::sample_f(const intersectionRec &intersection, const Vector3 &wo) const {
    const float ndotwo = dot(intersection.normal, wo);
    const Vector3 wi = -wo + 2.0f * intersection.normal * ndotwo;
    const float pdf = fabs(dot(intersection.normal, wi));
    return {Constants::WHITE, wi, pdf};
}


