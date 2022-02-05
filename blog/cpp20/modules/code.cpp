module;

#include <algorithm>

export module Utils.Randomizer;

import <random>;

namespace utils {

namespace detail {
std::string GetCharset(const int literals);
} // namespace detail

export class Randomizer
{
public:
  enum Literals
  {
    UpperCaseLetters = 0b0001,
    LowerCaseLetters = 0b0010,
    Digits = 0b0100,

    Letters = UpperCaseLetters | LowerCaseLetters,
    Alnum = Letters | Digits
  };

  std::string generateString(const size_t length, const int literals)
  {
    if (length == 0) return {};
