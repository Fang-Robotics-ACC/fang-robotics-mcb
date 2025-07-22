#ifndef FANG_ROBOTICS_MCB_SYSTEM_ASSERT_MODM_ABANDON_HPP
#define FANG_ROBOTICS_MCB_SYSTEM_ASSERT_MODM_ABANDON_HPP
#include "modm/architecture/interface/assert.hpp"
/**
 * Overwriteable abandonment handler for all targets.
 *
 * You should overwrite this handler for custom failure behaviour like blinking
 * LEDs and logging the failure via a serial connection.
 *
 * @ingroup modm_architecture_assert
 */
modm_extern_c void
modm_abandon(const modm::AssertionInfo &info);
#endif