// SPDX-FileCopyrightText: 2025 Anthony Loiseau <anthony.loiseau@allcircuits.com>
//
// SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

#pragma once

namespace act::foundation
{

/** @brief Deny copy and moves of classes inheriting it */
class NotCopiableNotMovable
{
  protected:
    /// @brief Nothing special for default constructor
    NotCopiableNotMovable() = default;

    /// @brief Nothing special for default destructor
    virtual ~NotCopiableNotMovable() = default;

  public:
    /// @brief Copy constructor (deleted)
    NotCopiableNotMovable(const NotCopiableNotMovable &) = delete;

    /// @brief Move constructor (deleted)
    NotCopiableNotMovable(NotCopiableNotMovable &&) = delete;

    /// @brief Copy assignment operator (deleted)
    NotCopiableNotMovable &operator=(const NotCopiableNotMovable &) = delete;

    /// @brief Move assignment operator (deleted)
    NotCopiableNotMovable &operator=(NotCopiableNotMovable &&) = delete;
};

} // namespace act::foundation
