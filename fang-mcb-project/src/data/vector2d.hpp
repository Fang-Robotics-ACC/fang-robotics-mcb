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


        template <typename Unit>
        Vector2D<Unit> operator*(const Vector2D<Unit>& vector, double scale)
        {
            return Vector2D{vector.x, vector.y};
        }

        template <typename Unit>
        Vector2D<Unit> operator*(double scale, const Vector2D<Unit>& vector)
        {
            return vector * scale;
        }
    }
}
#endif