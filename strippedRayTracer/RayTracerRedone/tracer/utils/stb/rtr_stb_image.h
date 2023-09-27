//
// Created by misae on 03/06/2023.
//

#ifndef RAYTRACER_REDONE_RTR_STB_IMAGE_H
#define RAYTRACER_REDONE_RTR_STB_IMAGE_H
// Disable pedantic warnings for this external library.
#ifdef _MSC_VER
// Microsoft Visual C++ Compiler
    #pragma warning (push, 0)
#endif

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Restore warning levels.
#ifdef _MSC_VER
// Microsoft Visual C++ Compiler
    #pragma warning (pop)
#endif

#endif //RAYTRACER_REDONE_RTR_STB_IMAGE_H
