// SPDX-FileCopyrightText: 2025 Benoit Rolandeau <benoit.rolandeau@allcircuits.com>
//
// SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

/* # Include of HPP file linked to the current CPP */
#include "act_misc/utilities/vector_string_util.hpp"

/* # App includes (in alphabetical order) */

/* # Internal includes library */

/* # Extern includes: Library */

/* # Extern includes: Global */
#include <sstream>
#include <string>
#include <vector>

std::string VectorStringUtil::join(const std::vector<std::string> &vec,
                                   const std::string &separator)
{
    auto citer = vec.cbegin();
    if (citer == vec.cend())
    {
        return "";
    }

    std::stringstream resultStream;
    resultStream << *citer;
    ++citer;
    if (separator.empty())
    {
        for (; citer != vec.cend(); ++citer)
        {
            resultStream << *citer;
        }
    }
    else
    {
        for (; citer != vec.cend(); ++citer)
        {
            resultStream << separator << *citer;
        }
    }

    return resultStream.str();
}

std::vector<std::string> VectorStringUtil::split(const std::string &str,
                                                 const std::string &separator)
{
    std::stringstream stringStream(str);
    std::vector<std::string> tmpList;
    std::string element;

    if (!str.empty())
    {
        int start = 0;
        size_t idx = str.find(separator, start);
        while (idx != std::string::npos)
        {
            int length = idx - start;
            tmpList.push_back(str.substr(start, length));
            start += (length + separator.size());

            idx = str.find(separator, start);
        }

        tmpList.push_back(str.substr(start));
    }

    return tmpList;
}
