/**
 * SPDX-FileCopyrightText: 2025 Ghislain Mangé <ghislain.mange@allcircuits.com>
 *
 * SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1
 */

/* # Include of HPP file linked to the current CPP */
#include "act_misc/utilities/file_util.hpp"

/* # App includes (in alphabetical order) */
#include "act_logger/models/abs_logger.hpp"
#include "act_misc/models/ext_file.hpp"

/* # Internal includes library */

/* # Extern includes: Library */

/* # Extern includes: Global */
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

namespace FileUtil
{
    std::optional<std::string> ReadFile(const std::string &path,
                                        const AbsLogger &logger,
                                        std::ios::openmode mode)
    {
        std::ifstream file(path, mode);
        if (!file.is_open())
        {
            /**
             * use debug, not error:
             * full path should not be printed on embedded production run
             */
            logger.debugStream() << "Failed to open " << path;
            return std::nullopt;
        }
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }

    std::optional<int> ReadFileAsInt(const std::string &path,
                                     const AbsLogger &logger,
                                     std::ios::openmode mode)
    {
        auto optContent = ReadFile(path, logger, mode);
        if (!optContent.has_value())
        {
            return std::nullopt;
        }

        int value = 0;
        try
        {
            value = std::stoi(optContent.value());
        }
        catch (const std::exception &)
        {
            logger.errorStream() << "Failed to parse " << optContent.value() << " as int";
            return std::nullopt;
        }

        return value;
    }

    bool WriteFile(const std::string &path,
                   const std::string &content,
                   const AbsLogger &logger,
                   std::ios::openmode mode)
    {
        std::ofstream file(path, mode);
        if (!file.is_open())
        {
            /**
             * use debug, not error:
             * full path should not be printed on embedded production run
             */
            logger.debugStream() << "Failed to open " << path;
            return false;
        }

        file << content;
        file.close();

        if (!file.good())
        {
            /**
             * use debug, not error:
             * full path should not be printed on embedded production run
             */
            logger.debugStream() << "Failed to write to " << path;
            return false;
        }

        return true;
    }

    std::shared_ptr<ExtFile> CreateFile(const std::string &path,
                                        const AbsLogger &logger,
                                        std::ios::openmode mode,
                                        bool isTemp)
    {
        auto extFile = ExtFile::CreateFileAndTryToOpenIt(path, mode, logger, isTemp);
        if (extFile == nullptr)
        {
            return nullptr;
        }

        return std::shared_ptr<ExtFile>(extFile);
    }

    std::shared_ptr<ExtFile> CreateFile(const std::string &path,
                                        const AbsLogger &logger,
                                        bool isTemp)
    {
        auto extFile = new ExtFile(path, logger, isTemp);
        return std::shared_ptr<ExtFile>(extFile);
    }

    bool ArePathsEqual(const std::string &path1, const std::string &path2, const AbsLogger &logger)
    {
        if (path1 == path2)
        {
            // No need to check further if the strings are identical
            return true;
        }

        bool isEqual = false;
        try
        {
            auto path1Obj = std::filesystem::absolute(path1);
            auto path2Obj = std::filesystem::absolute(path2);
            isEqual = std::filesystem::equivalent(path1, path2);
        }
        catch (const std::exception &e)
        {
            logger.warningStream() << "IsPathEqual: Exception occurred while comparing paths '"
                                   << path1 << "' and '" << path2 << "': " << e.what();
        }

        return isEqual;
    }

    std::string GetFilename(const std::string &path)
    {
        if (path.empty())
        {
            return "";
        }

        std::filesystem::path fsPath(path);
        return fsPath.filename().string();
    }
} /* namespace FileUtil */
