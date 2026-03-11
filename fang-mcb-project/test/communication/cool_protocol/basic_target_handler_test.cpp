#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "communication/cool_protocol/basic_target_handler.hpp"
#include "communication/cool_protocol/ibasic_target_listener.hpp"


namespace fang::communication
{
MATCHER_P(basicTargetEq, target, "")
{
    return 
    {
        target.x == arg.x
        && target.y == arg.y
        && target.z == arg.z
    };
}
class IBasicTargetListenerMock : public IBasicTargetListener
{
public:
    MOCK_METHOD(void, basicTargetFound, (const BasicTargetT& basicTarget), (override));
};


TEST(BasicTargetHandler, deserialization)
{
    BasicTargetT expectedTarget
    {

        .x = -0.234234,
        .y = 234.2343,
        .z = 12.234234
    };
    flatbuffers::FlatBufferBuilder builder{};

    testing::NiceMock<IBasicTargetListenerMock> basicListener{};
    builder.Finish(BasicTarget::Pack(builder, &expectedTarget));
    EXPECT_CALL(basicListener, basicTargetFound(basicTargetEq(expectedTarget)));

    BasicTargetHandler handler{basicListener};

    coolSerial::Bytes data{builder.GetBufferSpan().begin(), builder.GetBufferSpan().end()};
    handler.handleData(data);
}
}