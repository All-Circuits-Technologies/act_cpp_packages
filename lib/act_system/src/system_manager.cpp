// SPDX-FileCopyrightText: 2025 Benoit Rolandeau <benoit.rolandeau@allcircuits.com>
//
// SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

#include "act_system/system_manager.hpp"

#include "act_logger/models/abs_logger.hpp"
#include "act_text/vector_string_util.hpp"
#include "act_threading/reusable_thread.hpp"

#include <array>
#include <iostream>

#ifndef _WIN32
#include <sys/reboot.h>
#include <unistd.h>
#endif

namespace act::system
{

SystemManager::SystemManager(act::logger::AbsLogger &parentLogger)
    : AbsManager(),
      m_logger{parentLogger.createAbsSubLogger(LOGGER_CATEGORY, act::logger::LogsLevel::TRACE)},
      m_rebootThread{new act::threading::ReusableThread()}
{
}

SystemManager::~SystemManager()
{
    if (m_rebootThread != nullptr)
    {
        delete m_rebootThread;
        m_rebootThread = nullptr;
    }
}

bool SystemManager::init()
{
    return true;
}

act::threading::ReusableThreadResult::Enum SystemManager::askReboot(int delayInSec)
{
    return m_rebootThread->start(*m_logger, RebootThreadFunction, delayInSec, this);
}

int SystemManager::CallCommand(const std::string &cmd,
                               std::ostream &output,
                               const act::logger::AbsLogger &logger)
{
    FILE *pipe = nullptr;
    try
    {
#ifdef _WIN32
        pipe = _popen(cmd.c_str(), "r");
#else
        pipe = popen(cmd.c_str(), "r");
#endif
    }
    catch (const std::exception &e)
    {
        logger.errorStream() << "Exception caught: " << e.what();
    }

    if (pipe == nullptr)
    {
        logger.errorStream() << "Failed to open pipe for command: " << cmd;
        return -1;
    }

    std::array<char, CMD_OUTPUT_BUFFER_SIZE> buffer{};
    while (fgets(buffer.data(), CMD_OUTPUT_BUFFER_SIZE, pipe) != nullptr)
    {
        output << buffer.data();
    }

#ifdef _WIN32
    int returnCode = _pclose(pipe);
#else
    int returnCode = pclose(pipe);
#endif
    return returnCode;
}

int SystemManager::CallCommand(const std::vector<std::string> &cmdParts,
                               std::ostream &output,
                               const act::logger::AbsLogger &logger)
{
    auto cmd = act::text::VectorStringUtil::join(cmdParts, CMD_PART_SEPARATOR);
    return CallCommand(cmd, output, logger);
}

void SystemManager::RebootThreadFunction(int delayInSec, SystemManager *systemManager)
{
    auto logger = systemManager->m_logger;

#ifndef _WIN32
    sync();
#endif

    if (delayInSec > 0)
    {
        std::this_thread::sleep_for(std::chrono::seconds(delayInSec));
    }

    int cmdReturn = -1;
    {
        logger->infoStream() << "Executing reboot command...";
        auto traceStream = logger->traceStream();
        cmdReturn = CallCommand(REBOOT_CMD_NAME, traceStream.getStream(), *logger);
    }

    if (cmdReturn != 0)
    {
        // For now, we don't manage reboot failures further than logging an error, because we
        // expect the system to reboot properly when the command is called. If it appears that
        // some systems may fail to reboot properly, we may need to implement a more robust
        // mechanism to handle such failures, such as events notifications
        logger->errorStream() << "Reboot command failed with return code: " << cmdReturn;
        return;
    }

    systemManager->m_rebootAsked = true;
}

} // namespace act::system
