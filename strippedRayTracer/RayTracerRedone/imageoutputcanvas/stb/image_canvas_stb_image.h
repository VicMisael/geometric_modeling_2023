//
// Created by misae on 03/06/2023.
//

#ifndef IMAGE_CANVAS_STB_IMAGE_H
#define IMAGE_CANVAS_STB_IMAGE_H
// Disable pedantic warnings for this external library.
#ifdef _MSC_VER
// Microsoft Visual C++ Compiler
#define __STDC_LIB_EXT1__
    #pragma warning (push, 0)
#endif


#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// Restore warning levels.
#ifdef _MSC_VER
// Microsoft Visual C++ Compiler
    #pragma warning (pop)
#endif

#endif //IMAGE_CANVAS_STB_IMAGE_H
