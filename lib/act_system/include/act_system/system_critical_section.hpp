// SPDX-FileCopyrightText: 2025 Anthony Loiseau <anthony.loiseau@allcircuits.com>
//
// SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

#pragma once

#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

namespace act::logger
{
class AbsLogger;
} // namespace act::logger

namespace act::system
{

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
    explicit SystemCriticalSection(const std::string &slug, const act::logger::AbsLogger &logger)
        : SystemCriticalSection(slug.c_str(), logger)
    {
    }

    /**
     * @brief Create a system-wide critical section
     * @param slug Critical section identifier to reuse in other processes
     * @param logger Logger instance
     * @note Created critical section is not auto-entered, you must enter it.
     */
    explicit SystemCriticalSection(const char *slug, const act::logger::AbsLogger &logger);

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
    const act::logger::AbsLogger &m_logger;

#ifdef _WIN32
    /** @brief Windows mutex handle */
    void *m_handle{nullptr};
#else
    /** @brief Lock file file descriptor */
    int m_fd;
#endif
};

} // namespace act::system
