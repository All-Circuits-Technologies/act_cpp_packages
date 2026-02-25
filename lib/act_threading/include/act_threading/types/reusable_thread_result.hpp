// SPDX-FileCopyrightText: 2026 Benoit Rolandeau <benoit.rolandeau@allcircuits.com>
//
// SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

#pragma once

#include "act_foundation/not_copiable_not_movable.hpp"

namespace act::threading
{

class ReusableThreadResult : private act::foundation::NotCopiableNotMovable
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

} // namespace act::threading
