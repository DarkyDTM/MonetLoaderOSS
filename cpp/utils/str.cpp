#include "str.h"
#include "utils/str.h"
#include <algorithm>
#include <array>

std::string strutils::hex_string(const void* hex_void, std::size_t len, const std::string_view sep)
{
  if (len == 0)
    return "";
  const auto* hex = static_cast<const unsigned char*>(hex_void);

  std::string result;
  result.reserve(2 * len + sep.length() * (len - 1));
  std::array<char, 3> temp {};
  temp[2] = '\0';

  unsigned char digit;
  for (std::size_t i = 0; i < len; ++i) {
    digit = (hex[i] >> 4) & 0xF;
    temp[0] = digit >= 10 ? ('a' + digit - 10) : ('0' + digit);
    digit = hex[i] & 0xF;
    temp[1] = digit >= 10 ? ('a' + digit - 10) : ('0' + digit);

    result += temp.data();

    if (i != len - 1)
      result += sep;
  }

  return result;
}

std::string strutils::ascii_string(const void* ascii_void, std::size_t len, const char invalid)
{
  if (len == 0)
    return "";

  const auto* ascii = static_cast<const unsigned char*>(ascii_void);
  std::string result;
  result.reserve(len);

  for (std::size_t i = 0; i < len; ++i) {
    if (ascii[i] >= ' ' && ascii[i] <= '~') {
      result.push_back(ascii[i]);
    } else {
      result.push_back(invalid);
    }
  }

  return result;
}

std::vector<std::string> strutils::split(const std::string& string, const std::string_view sep)
{
  std::size_t pos_start = 0, pos_end, delim_len = sep.length();
  std::string token;
  std::vector<std::string> res;

  while ((pos_end = string.find(sep, pos_start)) != std::string::npos) {
    token = string.substr(pos_start, pos_end - pos_start);
    pos_start = pos_end + delim_len;
    res.push_back(token);
  }

  res.push_back(string.substr(pos_start));
  return res;
}

void strutils::replace_all(std::string& string, const std::string_view what, const std::string_view to) {
    std::size_t pos = 0;
    while ((pos = string.find(what, pos)) != std::string::npos) {
         string.replace(pos, what.length(), to);
         pos += to.length();
    }
}