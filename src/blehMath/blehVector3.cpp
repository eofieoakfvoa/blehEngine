#pragma once
#include "blehMath.h"
namespace blehMath
{
    class vector3
    {
        public:
        float x, y, z;
        
        template <typename xValue, typename yValue, typename zValue>
        vector3(xValue x, yValue y,zValue z)
            : x(static_cast<float>(x)), y(static_cast<float>(y)), z(static_cast<float>(z))
            {}
        template<typename zValue>
        vector3(vector2 Vector2, zValue z)
            : x(vector2.x), y(vector2.y), z(static_cast<float>(z))
            {}
    };

}