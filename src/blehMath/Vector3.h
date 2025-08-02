#pragma once
#include "blehMath.h"

namespace blehMath
{
#ifdef CUSTOM_MATH

    class vector3
    {
    public:
        float X, Y, Z;

        template <typename xValue, typename yValue, typename zValue>
        vector3(xValue x, yValue y, zValue z)
            : X(static_cast<float>(x)), Y(static_cast<float>(y)), Z(static_cast<float>(z))
        {}

        template<typename zValue>
        vector3(vector2 Vector2, zValue z)
            : X(Vector2.X), Y(Vector2.Y), Z(static_cast<float>(z))
        {}

        void Add(const vector3& otherVector3)
        {
            X += otherVector3.X;
            Y += otherVector3.Y;
            Z += otherVector3.Z;
        }

        static vector3 Zero()
        {
            return vector3(0.0f, 0.0f, 0.0f);
        }
    };

#else

    using vector3 = glm::vec3;

#endif
}