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

