export module Utils.Randomizer;

import std.core;

namespace utils {

namespace {
std::string GetCharset(const int literals);
} // namespace

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

	std::string generateString(const size_t &length, const int literals);

private:
	std::random_device m_rd{};
	std::mt19937 m_rng{ m_rd() };
};

} // namespace utils

module : private;

namespace utils {

std::string Randomizer::generateString(const size_t& length, const int literals)
{
	const auto charset = GetCharset(literals);
	std::uniform_int_distribution<> distr{ 0, static_cast<int>(charset.size()) - 1 };

	std::string str(length, 0);
	std::generate_n(str.begin(), length, [&] { return charset.at(static_cast<size_t>(distr(m_rng))); });

	return str;
}

namespace {

std::string GetCharset(const int literals)
{
	std::string charset;

	if (literals & Randomizer::Digits) {
		charset += "0123456789";
	}
	if (literals & Randomizer::UpperCaseLetters) {
		charset += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	}
	if (literals & Randomizer::LowerCaseLetters) {
		charset += "abcdefghijklmnopqrstuvwxyz";
	}

	return charset;
}

} // namespace

} // namespace utils
