// SPDX-FileCopyrightText: 2025 Anthony Loiseau <anthony.loiseau@allcircuits.com>
//
// SPDX-License-Identifier: LicenseRef-ALLCircuits-ACT-1.1

/* # Include of HPP file linked to the current CPP */
#include "act_text/string_util.hpp"

/* # App includes (in alphabetical order) */

/* # Internal includes library */
#include "act_foundation/constants/def_soft.hpp"

/* # Extern includes: Library */

/* # Extern includes: Global */
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <optional>
#include <regex>

void StringUtil::ToUpperInPlace(std::string &str)
{
    std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) {
        return std::toupper(c);
    });
}

std::string StringUtil::ToUpper(const std::string &str)
{
    std::string copy = str;
    ToUpperInPlace(copy);
    return copy;
}

void StringUtil::ToLowerInPlace(std::string &str)
{
    std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) {
        return std::tolower(c);
    });
}

std::string StringUtil::ToLower(const std::string &str)
{
    std::string copy = str;
    ToLowerInPlace(copy);
    return copy;
}

int StringUtil::CompareNoCase(const std::string &lhs, const std::string &rhs)
{
    const std::string lhsLowCase = ToLower(lhs);
    const std::string rhsLowCase = ToLower(rhs);
    return lhsLowCase.compare(rhsLowCase);
}

bool StringUtil::AreStringEqualNoCase(const std::string &lhs, const std::string &rhs)
{
    return std::ranges::equal(lhs, rhs, [](char a, char b) {
        return (std::tolower(a) == std::tolower(b));
    });
}

std::string StringUtil::BinToHex(const std::string &bin)
{
    std::ostringstream hex;

    /* configure hex output */
    hex << std::hex << std::setw(2) << std::setfill('0');
    for (unsigned char c : bin)
    {
        hex << (int)c;
    }
    return hex.str();
}

std::optional<std::string> StringUtil::HexToBin(const std::string &hex)
{
    if (!IsHexOnly(hex))
    {
        return std::nullopt;
    }

    std::string binaryString;

    for (size_t i{0}; i + 1 < hex.length(); i += HexConstants::HEX_CHARS_PER_BYTE)
    {
        std::string hexByte{hex.substr(i, HexConstants::HEX_CHARS_PER_BYTE)};
        char byte{static_cast<char>(std::stoul(hexByte, nullptr, HexConstants::HEXADECIMAL_BASE))};
        binaryString.push_back(byte);
    }

    return binaryString;
}

bool StringUtil::IsHexOnly(const std::string &data)
{
    return std::all_of(data.begin(), data.end(), [](char c) {
        return std::isxdigit(static_cast<unsigned char>(c));
    });
}

bool StringUtil::IsValidIpAddress(const std::string &ipAddress)
{
    /**
     * Simple IP address validation using regex
     * Matches IPv4 addresses (0-255.0-255.0-255.0-255)
     */
    std::regex ipPattern(
        R"(^((25[0-5]|2[0-4][0-9]|[01]?[0-9]?[0-9])\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9]?[0-9])$)");

    return std::regex_match(ipAddress, ipPattern);
}
