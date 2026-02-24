// SPDX-FileCopyrightText: 2026 Anthony Loiseau <anthony.loiseau@allcircuits.com>
//
// SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

#include "act_linux_io/led/trigger/simple_led_trigger_config.hpp"

namespace act::linux_io
{

/* # Constructors */

SimpleLedTriggerConfig::SimpleLedTriggerConfig(std::string name)
    : AbsLedTriggerConfig(std::move(name))
{
}

} // namespace act::linux_io
