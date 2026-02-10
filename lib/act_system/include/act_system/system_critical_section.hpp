// SPDX-FileCopyrightText: 2025 Anthony Loiseau <anthony.loiseau@allcircuits.com>
//
// SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

#pragma once

/* # App includes (in alphabetical order) */

/* # Internal includes library */

/* # Extern includes: Library */

/* # Extern includes: Global */
#include <string>

/* # Forward declaration */
class AbsLogger;

/**
 * @brief Multi-process-wide critical section
 * @note Based on flock instead of a semaphore in order to have lock
 *       auto-released even in case of app crash.
 */
class SystemCriticalSection
{
  public:
    /**
     * @brief Create a system-wide critical section
     * @param slug Critical section identifier to reuse in other processes
     * @param logger Logger instance
     * @note Created critical section is not auto-entered, you must enter it.
     */
    explicit SystemCriticalSection(const std::string &slug, const AbsLogger &logger)
        : SystemCriticalSection(slug.c_str(), logger)
    {
    }

    /**
     * @brief Create a system-wide critical section
     * @param slug Critical section identifier to reuse in other processes
     * @param logger Logger instance
     * @note Created critical section is not auto-entered, you must enter it.
     */
    explicit SystemCriticalSection(const char *slug, const AbsLogger &logger);

    /** @brief Disconnect from created system-wide critical section
     * @note Critical section is left created on OS level
     */
    virtual ~SystemCriticalSection();

  public:
    /** @brief Enter critical section, that is take the lock */
    [[nodiscard]] bool enter() const;

    /*** @brief Leave critical section, that is release the lock */
    [[nodiscard]] bool leave() const;

  private:
    /** @brief Compute a lock file path given a slug
     * @param slug System-wide critical section slug/ / identifier
     * @return An absolute file path based on this slug
     */
    static std::string ComputeLockFilePath(const char *slug);

  private:
    /** @brief All processes can use the lock file */
    static const constexpr int LOCK_FILE_ACCESS_RIGHTS = 0666;

  private:
    /** @brief Logger instance */
    const AbsLogger &m_logger;

    /** @brief Lock file file descriptor */
    int m_fd;
};
