export module Domain.Auth;

import Utils.Randomizer;

import <string>;

namespace domain::auth {
export std::string GenerateRandomCode(const size_t length = 5);
} // namespace domain::auth

module : private;

namespace domain::auth {

std::string GenerateRandomCode(const size_t length)
{
	using namespace utils;

	constexpr int literals = Randomizer::UpperCaseLetters | Randomizer::Digits;

	return Randomizer{}.generateString(length, literals);
}

} // namespace domain::auth
