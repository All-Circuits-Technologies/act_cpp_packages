// SPDX-FileCopyrightText: 2025 Anthony Loiseau <anthony.loiseau@allcircuits.com>
//
// SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

#pragma once

/* # App includes (in alphabetical order) */
#include "system_critical_section.hpp"

/* # Internal includes library */
#include "act_foundation/constants/def_soft.hpp"

/* # Extern includes: Library */

/* # Extern includes: Global */

/* # Forward declaration */

namespace act::system
{

/** @brief Lock a critical section during entire object life type */
class SystemCriticalSectionGuard
{
  public:
    /**  @brief Lock criticalSection until destructor
     * @param criticalSection Critical section to lock
     */
    explicit SystemCriticalSectionGuard(SystemCriticalSection &criticalSection)
        : m_criticalSection(criticalSection)
    {
        UNUSED(m_criticalSection.enter());
    }

    /** @brief Unlock critical section */
    virtual ~SystemCriticalSectionGuard()
    {
        UNUSED(m_criticalSection.leave());
    }

  private:
    /** @brief Critical section */
    SystemCriticalSection &m_criticalSection;
};

} // namespace act::system
