#pragma once
#include "blehMath.h"
namespace blehMath
{
    class vector3 //skulle highkey ba kunna vara en struct eftersom ända skillnaden är att det är public by default
    {
        public:
        float X, Y, Z;
        
        template <typename xValue, typename yValue, typename zValue>
        vector3(xValue x, yValue y,zValue z)
            : X(static_cast<float>(x)), Y(static_cast<float>(y)), Z(static_cast<float>(z))
            {}
        template<typename zValue>
        vector3(vector2 Vector2, zValue z)
            : X(vector2.x), Y(vector2.y), Z(static_cast<float>(z))
            {}
        void Add(vector3 otherVector3)
        {
            X += otherVector3.X, Y += otherVector3.Y, Z += otherVector3.Z;
        }
        static vector3 Zero()
        {
            return vector3(0.0f,0.0f,0.0f);
        }
    };

}