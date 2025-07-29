#include "wrap/rail/chassis/quad_drive_data.hpp"
#include "expect_quad_drive_data_eq.hpp"

#include <gtest/gtest.h>

using AbstractQuadDriveData = fang::chassis::QuadDriveData<double>;

namespace fang::chassis
{
    struct ScalarTestParam
    {
        AbstractQuadDriveData inputQuad;
        AbstractQuadDriveData expectedQuad;
        double scale;
    };

    /**
     * If a quad drive data is {1,1,1,1} * 4
     * it should be {4,4,4,4} and so on.
     * 
     * This is useful in power mangement scaling operations
     */
    class QuadDriveScalarTest : public ::testing::TestWithParam<ScalarTestParam>
    {
    protected:
        ScalarTestParam param{GetParam()};
        AbstractQuadDriveData inputQuad{param.inputQuad};
        AbstractQuadDriveData expectedQuad{param.expectedQuad};
        double scale{param.scale};
    };

    TEST_P(QuadDriveScalarTest, uniformScalar)
    {
        AbstractQuadDriveData scaledQuad{inputQuad * scale};

        //Test commutative  scaling
        AbstractQuadDriveData communitativeQuad{scale * inputQuad};
        expectQuadDriveDataEq(communitativeQuad, scaledQuad);

        //Test proper scaling
        expectQuadDriveDataEq(scaledQuad, expectedQuad);
    }

    //Test if multiplying by zero yields zero and vise versa
    INSTANTIATE_TEST_CASE_P
    (
        zeroTest,
        QuadDriveScalarTest,
        ::testing::Values
        (
            ScalarTestParam
            {
                .inputQuad = {1,1,1,1},
                .expectedQuad = {0,0,0,0},
                .scale = 0
            },
            ScalarTestParam
            {
                .inputQuad = {0,0,0,0},
                .expectedQuad = {0,0,0,0},
                .scale = 10
            }
        )
    );

    //Test if multiplying by zero yields zero and vise versa
    INSTANTIATE_TEST_CASE_P
    (
        differentValueSclar,
        QuadDriveScalarTest,
        ::testing::Values
        (
            ScalarTestParam
            {
                .inputQuad = {1.5, 3.1, 100.3, 12},
                .expectedQuad = {4.5 ,9.3, 300.9, 36},
                .scale = 3
            },
            ScalarTestParam
            {
                .inputQuad = {1 , 2, 3, 4},
                .expectedQuad = {10, 20, 30, 40},
                .scale = 10
            }
        )
    );

    //Test if multiplying by zero yields zero and vise versa
    INSTANTIATE_TEST_CASE_P
    (
        negativeValues,
        QuadDriveScalarTest,
        ::testing::Values
        (
            ScalarTestParam
            {
                .inputQuad = {1.5, 3.1, 100.3, 12},
                .expectedQuad = {-4.5, -9.3, -300.9, -36},
                .scale = -3
            },
            ScalarTestParam
            {
                .inputQuad = {1 , 2, 3, 4},
                .expectedQuad = {-10, -20, -30, -40},
                .scale = -10
            }
        )
    );

    //Multiplication of random negative numbers
    INSTANTIATE_TEST_CASE_P
    (
        signMultiplication,
        QuadDriveScalarTest,
        ::testing::Values
        (
            ScalarTestParam
            {
                .inputQuad = {1, -1 , 1, -1},
                .expectedQuad = {0,0,0,0},
                .scale = 0
            },
            ScalarTestParam
            {
                .inputQuad = {123234, -345, 3.45, -2},
                .expectedQuad = {1232340, -3450, 34.5, -20},
                .scale = 10
            }
        )
    );
}