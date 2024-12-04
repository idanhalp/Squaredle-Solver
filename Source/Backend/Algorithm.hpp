#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

#include <compare>
#include <string>
#include <vector>

namespace Algorithm
{
	typedef std::vector<std::pair<size_t, size_t>> indices_t;

	struct WordInfo
	{
		std::string word;
		indices_t indices;

		auto operator<=>(const WordInfo& other) const -> std::strong_ordering
		{
			return std::make_pair(word.length(), word) <=> std::make_pair(other.word.length(), other.word);
		}

		auto operator==(const WordInfo& other) const -> bool
		{
			return word == other.word;
		}
	};

	auto find_words(const std::vector<std::vector<char>>& grid) -> std::vector<WordInfo>;
}

#endif
