// SPDX-FileCopyrightText: 2025 Anthony Loiseau <anthony.loiseau@allcircuits.com>
//
// SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

#pragma once

#include "act_foundation/not_copiable_not_movable.hpp"

namespace act::foundation
{

/** @brief Managers shared behavior */
class AbsManager : private NotCopiableNotMovable
{
  protected:
    /// @brief Nothing special for default constructor
    AbsManager() = default;

    /// @brief Nothing special for default destructor
    ~AbsManager() override = default;

  public:
    /**
     * @brief Start required internals
     */
    virtual bool init(void) = 0;
};

} // namespace act::foundation
