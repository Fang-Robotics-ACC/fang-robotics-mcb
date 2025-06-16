#ifndef VECTOR_2D_H_DSLFKJESFLK_YEET
#define VECTOR_2D_H_DSLFKJESFLK_YEET
namespace data
{
    namespace math
    {
        template <typename Unit>
        struct Vector2D
        {
            using unit = Unit;
        public:
            Unit x;
            Unit y; 
        };


        template <typename ScaleUnit>
        Vector2D<ScaleUnit> operator*(const Vector2D<double>& vector, const ScaleUnit& scale)
        {
            return Vector2D<ScaleUnit>{vector.x * scale, vector.y * scale};
        }

        template <typename ScaleUnit>
        Vector2D<ScaleUnit> operator*(const ScaleUnit& scale, const Vector2D<double>& vector)
        {
            return vector * scale;
        }
    }
}
#endif