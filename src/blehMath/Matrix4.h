#pragma once
#include "blehMath.h"

namespace blehMath
{
    #ifdef CUSTOM_MATH
    class matrix4
    {
        public:
        float[x][y]
    };
    #else

    using glm::mat4;
    
    #endif

}