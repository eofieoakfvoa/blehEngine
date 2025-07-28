namespace blehMath
{
    class vector2
    {
        float X,Y;
        template<typename xValue, typename yValue>
        vector2(xValue x,yValue y)
            :  X(static_cast<float>(x)), Y(static_cast<float>(y))
            {}
            
    };

}