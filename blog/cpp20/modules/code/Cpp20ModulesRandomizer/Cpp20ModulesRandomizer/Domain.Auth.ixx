export module Domain.Auth;

import Utils.Randomizer;

import <string>;

namespace domain::auth {

export std::string GenerateRandomCode(const size_t length = 5)
{
	using namespace utils;

	Randomizer randomizer;
	constexpr int literals = Randomizer::UpperCaseLetters | Randomizer::Digits;

	return randomizer.generateString(length, literals);
}

} // namespace domain::auth
