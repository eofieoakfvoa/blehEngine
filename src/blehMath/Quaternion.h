#pragma once
#include "blehMath.h"

namespace bleh::blehMath
{
#ifdef CUSTOM_MATH

    class quaternion
    {
    };

#else

    using quaternion = glm::quat;

#endif
}