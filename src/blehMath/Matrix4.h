#pragma once
#include "blehMath.h"

namespace bleh::blehMath
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