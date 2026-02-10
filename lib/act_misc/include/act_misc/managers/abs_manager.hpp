// SPDX-FileCopyrightText: 2025 Anthony Loiseau <anthony.loiseau@allcircuits.com>
//
// SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

#pragma once

/* # App includes (in alphabetical order) */
#include "act_misc/not_copiable_not_movable.hpp"

/* # Internal includes library */

/* # Extern includes: Library */

/* # Extern includes: Global */

/* # Forward declaration */


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

