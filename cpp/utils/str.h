#pragma once
#include <cstddef>
#include <string>
#include <string_view>
#include <vector>

namespace strutils {
/**
 * @brief Converts bytes in @p hex to hexadecimal string separated by @p sep.
 *
 * @param hex Bytes.
 * @param len Length of @p hex.
 * @param sep Separator between bytes in string.
 * @return String with all bytes in hexadecimal notation, separated by @p sep.
 */
std::string hex_string(const void* hex, std::size_t len, const std::string_view sep = "");

/**
 * @brief Converts bytes in @p ascii to ASCII string, where invalid characters
 * are replaced by @p invalid.
 *
 * @param ascii Bytes.
 * @param len Length of @p ascii.
 * @param invalid Character which will replace invalid characters.
 * @return String with all bytes converted to ASCII.
 */
std::string ascii_string(const void* ascii, std::size_t len, const char invalid = '.');

/**
 * @brief Splits @p string into vector of strings delimited by @p sep.
 *
 * @param string String to split.
 * @param sep Separator.
 * @return Vector of strings delimited by @p sep.
 */
std::vector<std::string> split(const std::string& string, const std::string_view sep = "\n");

/**
 * @brief Replaces all occurances of @p what in @p string with @p to.
 *
 * @param string String in which to replace @p what.
 * @param what What to replace.
 * @param to TO what to replace.
 */
void replace_all(std::string& string, const std::string_view what, const std::string_view to);
}