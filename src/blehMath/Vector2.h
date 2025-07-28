namespace blehMath
{
    class vector2
    {
        float x,y;
        template<typename xValue, typename yValue>
        vector2(xValue x,yValue y)
            :  x(static_cast<float>(xValue)), y(static_cast<float>(xValue))
            {}
            
    };

}