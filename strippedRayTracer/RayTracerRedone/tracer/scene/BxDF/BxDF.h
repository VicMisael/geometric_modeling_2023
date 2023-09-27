#pragma once

#include <vector>

#include "../../utils/ColorVec.h"
#include "../../utils/Intersection.h"
#include "../../utils/Constants.h"

struct sample_f_out {
    ColorVec color;
    Vector3 wi;
    float pdf;
};

class BxDF {

public:
    virtual ~BxDF() = default;
    //Based of Physically based rendering
    /*
     *The hemispherical-hemispherical reflectance of a surface, denoted by phh, is a spectral
        value that gives the fraction of incident light reflected by a surface when the incident
        light is the same from all directions. It is
     */
    virtual ColorVec rho(const Vector3 &wo) const = 0;

    /*
    It returns the value of the distribution
        function for the given pair of directions.This interface implicitly assumes that light in
        different wavelengths is decoupled—energy at one wavelength will not be reflected at
        a different wavelength
    */
    virtual ColorVec f(const intersectionRec &intersection, const Vector3 &wo, const Vector3 &wi) const = 0;;/*
			 computes the direction of incident light ωi given an outgoing direction
		ωo and returns the value of the BxDF for the pair of directions. For delta distributions, it
		is necessary for the BxDF to choose the incident light direction in this way, since the caller
		has no chance of generating the appropriate wi direction.
	*/
    virtual sample_f_out sample_f(const intersectionRec &intersection, const Vector3 &wo) const = 0;

    virtual sample_f_out sample_f(const intersectionRec &intersection, const Vector3 &wo, const Vector3 &wi) const {
        return sample_f(intersection, wo);
    }

    //TODO implement for an arbitrary outgoing directly for true area lights
};

