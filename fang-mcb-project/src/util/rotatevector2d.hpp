#ifndef FANG_ROBOTICS_MCB_UTIL_ROTATE_VECTOR_2D
#define FANG_ROBOTICS_MCB_UTIL_ROTATE_VECTOR_2D
#include "unitaliases.hpp"
#include "mathaliases.hpp"
#include "data/vector2d.hpp"

namespace util
{
    namespace math
    {
        /**
         * This algorithm has an accuracy of within 1e-14; however, rotating the vector back will produce accuracy to only within
         * 1e-10
         */
        template<typename Unit>
        data::math::Vector2D<Unit> rotateVector2D(const data::math::Vector2D<Unit>& vector, const Radians& rotationAngle)
        {
            //Rotation matrix
            //https://www.youtube.com/watch?v=1oYEo7PNIBQ
            //I know it's Wikipedia but it's will help wwith the youtube video
            //In general, Wikipedia is pretty good as a math reference, too.
            //https://en.wikipedia.org/wiki/Rotation_matrix

            const double angle{rotationAngle.to<double>()};
            const double rotatedx{vector.x * (std::cos(angle)) - vector.y * (std::sin(angle))};
            const double rotatedy{vector.x * (std::sin(angle)) + vector.y * (std::cos(angle))};

            return data::math::Vector2D<Unit>{Unit{rotatedx}, Unit{rotatedy}};
        }
    }
}
#endif