#include "rotatevector2d.hpp"

namespace util
{
    namespace math
    {
        mathAliases::AbstractVector2D rotateVector(const mathAliases::AbstractVector2D& vector, const Radians& rotationAngle)
        {
            //Rotation matrix
            //https://www.youtube.com/watch?v=1oYEo7PNIBQ
            //I know it's Wikipedia but it's will help wwith the youtube video
            //In general, Wikipedia is pretty good as a math reference, too.
            //https://en.wikipedia.org/wiki/Rotation_matrix

            const double angle{rotationAngle.to<double>()};
            const double rotatedx{vector.x * (std::cos(angle)) - vector.y * (std::sin(angle))};
            const double rotatedy{vector.x * (std::sin(angle)) + vector.y * (std::cos(angle))};

            return mathAliases::AbstractVector2D{rotatedx, rotatedy};
        }
    }
}