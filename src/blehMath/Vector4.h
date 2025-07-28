#pragma once
#include "blehMath.h"
namespace blehMath
{
    class vector4 //skulle highkey ba kunna vara en struct eftersom ända skillnaden är att det är public by default
    {
        public:
        float X, Y, Z, A;
        
        template <typename xValue, typename yValue, typename zValue, typename aValue>
        vector4(xValue x, yValue y,zValue z, aValue a)
            : X(static_cast<float>(x)), Y(static_cast<float>(y)), Z(static_cast<float>(z)), A(static_cast<float>(A))
            {}
        template<typename zValue>
        void Add(vector4 otherVector4)
        {
            X += otherVector4.X, Y += otherVector4.Y, Z += otherVector4.Z, A += otherVector4.A;
        }
        static vector4 Zero()
        {
            return vector4(0,0,0,0);
        }
    };

}