#ifndef QUAD_DRIVE_INFO_H_SLDFJLSLDDJDJF_YEET_YEET
#define QUAD_DRIVE_INFO_H_SLDFJLSLDDJDJF_YEET_YEET
namespace data
{
    namespace chassis
    {
        /**
         * Generally, this class is meant to represent 4 wheels which are facing the same direction.
         * Although you can use different conventions, the recommended convention is that positive means
         * that the given wheel will rotate in a manner that would move the chassis forwawrd
         * (If it's a mecanum wheel, assume that it's a regular wheel - the convention is just
         * to establish the rotational direction.)
         */
        template <typename MotorUnit>
        struct QuadDriveData
        {
        public:
            QuadDriveData(const MotorUnit& frontLeftData, const MotorUnit& frontRightData,
                          const MotorUnit& rearLeftData,  const MotorUnit& rearRightData):
                          frontLeft{frontLeftData}, frontRight{frontRightData},
                          rearLeft{rearLeftData},   rearRight{rearRightData}
                          {}
            MotorUnit frontLeft{0};
            MotorUnit frontRight{0};
            MotorUnit rearLeft{0};
            MotorUnit rearRight{0};
        };
    }
}
#endif