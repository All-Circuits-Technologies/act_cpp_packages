// SPDX-FileCopyrightText: 2026 Benoit Rolandeau <benoit.rolandeau@allcircuits.com>
//
// SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

#pragma once

/* # App includes (in alphabetical order) */
#include "act_foundation/not_copiable_not_movable.hpp"

/* # Internal includes library */

/* # Extern includes: Library */

/* # Extern includes: Global */

/* # Forward declaration */

class ReusableThreadResult : private NotCopiableNotMovable
{
  public:
    /** @brief Enum representing the result of starting reusable thread */
    enum class Enum
    {
        OK = 0,
        ALREADY_RUNNING,
        INTERNAL_ERROR
    };
};
