#pragma once
#include "blehMath.h"

namespace blehMath
{
#ifdef CUSTOM_MATH

    class quaternion
    {
    };

#else

    using quaternion = glm::quat;

#endif
}