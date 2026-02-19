// SPDX-FileCopyrightText: 2026 Anthony Loiseau <anthony.loiseau@allcircuits.com>
//
// SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

/* # Include of HPP file linked to the current CPP */
#include "act_linux_io/led/trigger/simple_led_trigger_config.hpp"

/* # App includes (in alphabetical order) */

/* # Internal includes library */

/* # Extern includes: Library */

/* # Extern includes: Global */

namespace act::linux_io
{

/* # Constructors */

SimpleLedTriggerConfig::SimpleLedTriggerConfig(std::string name)
    : AbsLedTriggerConfig(std::move(name))
{
}

} // namespace act::linux_io
