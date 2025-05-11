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
    }
}
#endif