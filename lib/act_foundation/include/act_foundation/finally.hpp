// SPDX-FileCopyrightText: 2026 Anthony Loiseau <anthony.loiseau@allcircuits.com>
//
// SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

#pragma once

#include "act_logger/models/abs_logger.hpp"

#include <cassert>
#include <utility>

namespace act::logger
{
class AbsLogger;
} // namespace act::logger

namespace act::foundation
{

/**
 * @brief Object executing a function when going out of scope
 *
 * @note C++23 appears to have such thing named std::experimental::scope_exit
 */
template <typename F>
class Finally
{
    /* ## Types */
    /* ## Constructors */
  public:
    /**
     * @brief Constructor forwarding arguments to the value's constructor
     * @param func Function to execute upon destruction
     * @param logger Logger to log errors occurring during function execution
     * @note Throwing from inside a destructor is strictly forbidden in C++.
     *       As a safety measure, exceptions thrown by the function are all caught,
     *       and either logged (if logger provided) or asserted (if no logger).
     */
    explicit Finally(F &&func, act::logger::AbsLogger &logger)
        : m_enabled(true),
          m_func(std::forward<F>(func)),
          m_logger(logger)
    {
        // Empty
    }

    /**
     * @brief Default destructor
     */
    ~Finally()
    {
        if (m_enabled)
        {
            try
            {
                m_func();
            }
            catch (const std::exception &e)
            {
                // Catching all exception since throwing from a destructor is strictly denied

                m_logger.errorStream() << "Exception caught in Finally destructor: " << e.what();
            }
        }
    }

    /* ## Methods (members, then non-members) */
  public:
    /**
     * @brief Disable the execution of the function at destruction
     * @note Once disabled, cannot be re-enabled
     */
    void cancel()
    {
        m_enabled = false;
    }

    /* ## Constants */

    /* ## Data members */
  private:
    /**
     * @brief Should function be called upon destruction
     * @note True a start, false once cancelled
     */
    bool m_enabled;

    /**
     * @brief Function to execute
     * @note This function should better not throw exceptions
     */
    F m_func;

    /**
     * @brief Logger
     */
    act::logger::AbsLogger &m_logger;
};

} // namespace act::foundation
