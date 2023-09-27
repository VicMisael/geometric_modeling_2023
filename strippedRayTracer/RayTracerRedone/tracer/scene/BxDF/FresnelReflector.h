#pragma once
#include "BxDF.h"
class FresnelReflector :
    public BxDF
{

public:


    [[maybe_unused]] ColorVec rho(const Vector3& wo) const override;

    [[nodiscard]] ColorVec f(const intersectionRec& intersection, const Vector3& wo, const Vector3& wi) const override;

    [[nodiscard]] sample_f_out sample_f(const intersectionRec& intersection, const Vector3& wo) const override;
};

