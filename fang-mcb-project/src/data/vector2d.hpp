#ifndef VECTOR_2D_H_DSLFKJESFLK_YEET
#define VECTOR_2D_H_DSLFKJESFLK_YEET
#include <cmath>
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

            /**
             * Provides the values free of units
             */
            Vector2D<double> getRawVector() const
            {
                const double rawX{static_cast<double>(x)};
                const double rawY{static_cast<double>(y)};
                return Vector2D<double>{rawX, rawY};
            }

            Unit getMagnitude() const
            {
                //Traditional euclidean distance formula
                //the magnitude of a vector is the square root
                //of the square sum of its components
                //Given the use of non-linear math functions
                //and the desire for general use beyond units.h
                //the stripped forms are used
                //since the inputs and outputs are wrapped in units
                //dimensional consistnency is ensured

                const Vector2D<double> raw{getRawVector()};

                const double xSquared{raw.x * raw.x};
                const double ySquared{raw.y * raw.y};
                const double squareSum{xSquared + ySquared};
                const double distance{std::sqrt(squareSum)};
                return Unit{distance};
            }

            /**
             * Does not work on zero vectors
             */
            Vector2D<double> getUnitVector() const
            {
                const double rawMagnitude{static_cast<double>(getMagnitude())};
                const Vector2D<double> raw{getRawVector()};

                //We cannotuse the operators due to template shenanigans :D
                return Vector2D<double>{raw.x / rawMagnitude, raw.y / rawMagnitude};
            }

            Vector2D<Unit> operator-()
            {
                return Vector2D{-x, -y};
            }

            Vector2D<Unit> operator+(const Vector2D& addend)
            {
                return Vector2D{x + addend.x, y + addend.y};
            }

            Vector2D<Unit> operator-(const Vector2D& subtrahend)
            {
                return *this + (-subtrahend);
            }

            Vector2D<Unit> operator*(double scalar)
            {
                return Vector2D{x * scalar, y * scalar};
            }
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

        template <typename Unit>
        Vector2D<Unit> operator*(const double& scale, const Vector2D<Unit>& vector)
        {
            return vector * scale;
        }
    }
}
#endif