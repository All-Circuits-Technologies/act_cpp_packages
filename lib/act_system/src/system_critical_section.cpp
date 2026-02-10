// SPDX-FileCopyrightText: 2025 Anthony Loiseau <anthony.loiseau@allcircuits.com>
//
// SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

/* # Include of HPP file linked to the current CPP */
#include "act_system/system_critical_section.hpp"

/* # App includes (in alphabetical order) */

/* # Internal includes library */
#include "act_misc/constants/def_soft.hpp"
#include "act_logger/models/abs_logger.hpp"

/* # Extern includes: Library */

/* # Extern includes: Global */
#include <cerrno>  // errno
#include <cstring> // std::strerror
#include <fcntl.h>
#include <sys/file.h> // flock
#include <unistd.h>   // close

namespace act::system
{

    SystemCriticalSection::SystemCriticalSection(const char *slug, const AbsLogger &logger)
        : m_logger(logger)
    {
        const std::string lockFilePath = ComputeLockFilePath(slug);
        m_fd = ::open(lockFilePath.c_str(), O_CREAT | O_RDWR, LOCK_FILE_ACCESS_RIGHTS);

        if (m_fd == -1)
        {
            m_logger.errorStream() << "Failed to create/open lock file " << lockFilePath << ": "
                                   << std::strerror(errno);
        }
    }

    SystemCriticalSection::~SystemCriticalSection()
    {
        UNUSED(leave());
    }

    bool SystemCriticalSection::enter() const
    {
        if (m_fd < 0)
        {
            m_logger.error("Invalid lock file descriptor");
            return false;
        }

        bool locked = (flock(m_fd, LOCK_EX) == 0);
        if (!locked)
        {
            m_logger.errorStream() << "Failed to lock critical section: " << std::strerror(errno);
            return false;
        }

        return true;
    }

    bool SystemCriticalSection::leave() const
    {
        if (m_fd < 0)
        {
            m_logger.error("Invalid lock file descriptor");
            return false;
        }

        bool unlocked = (flock(m_fd, LOCK_UN) == 0);
        if (!unlocked)
        {
            m_logger.errorStream() << "Failed to unlock critical section: " << std::strerror(errno);
            return false;
        }

        return true;
    }

    std::string SystemCriticalSection::ComputeLockFilePath(const char *slug)
    {
        return std::string("/tmp/") + slug + ".lock";
    }

} // namespace act::system
