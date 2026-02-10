// SPDX-FileCopyrightText: 2025 Benoit Rolandeau <benoit.rolandeau@allcircuits.com>
//
// SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

/* # Include of HPP file linked to the current CPP */
#include "act_misc/utilities/csv_util.hpp"

/* # App includes (in alphabetical order) */
#include "act_logger/models/abs_logger.hpp"
#include "act_misc/models/ext_file.hpp"
#include "act_misc/utilities/string_util.hpp"
#include "act_misc/utilities/vector_string_util.hpp"

/* # Internal includes library */

/* # Extern includes: Library */

/* # Extern includes: Global */
#include <fstream>
#include <iostream>
#include <sstream>

std::string CsvUtil::CreateCsvLine(const std::vector<std::string> &values,
                                   const std::string &separator)
{
    std::stringstream stream;
    stream << VectorStringUtil::join(values, separator);
    stream << std::endl;
    return stream.str();
}

bool CsvUtil::AddCsvLine(const std::vector<std::string> &values,
                         const AbsLogger &logger,
                         ExtFile &file,
                         const std::string &separator)
{
    if (!file.isOpen())
    {
        logger.warningStream() << "CsvUtil::AddCsvLine: File is not open: " << file.getFilePath();
        return false;
    }

    std::fstream &fs = file.accessFilePtr();

    fs << VectorStringUtil::join(values, separator);
    fs << std::endl;
    auto errorCode = fs.sync();
    if (errorCode != 0)
    {
        logger.warningStream() << "CsvUtil::AddCsvLine: Failed to sync file: " << file.getFilePath()
                               << ", after writing CSV line, error code: " << errorCode;
        return false;
    }

    return true;
}

std::vector<std::string> CsvUtil::ParseCsvFile(const std::string &csvContent)
{
    std::vector<std::string> lines;
    std::stringstream streamContent(csvContent);
    std::string line;

    while (std::getline(streamContent, line))
    {
        lines.push_back(line);
    }

    return lines;
}

std::vector<std::string> CsvUtil::ParseCsvLine(const std::string &csvLine,
                                               const std::string &separator)
{
    auto values = VectorStringUtil::split(csvLine, separator);
    std::vector<std::string> trimmedValues;
    trimmedValues.reserve(values.size());
    for (auto &value : values)
    {
        /* Trim whitespace from value */
        trimmedValues.push_back(StringUtil::Trim(value));
    }

    return trimmedValues;
}
