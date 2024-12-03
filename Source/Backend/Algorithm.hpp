#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

#include <vector>
#include <string>
#include <map>
#include <functional>

namespace AlgorithmVersionWithoutIndices
{
	std::vector<std::string> find_words(const std::vector<std::vector<char>>& grid);
}

namespace AlgorithmVersionWithIndicesDeprecated
{	
	std::vector<std::vector<std::pair<size_t, size_t>>> find_words_indices(const std::vector<std::vector<char>>& grid);
}

namespace AlgorithmVersionWithIndices
{
	typedef std::vector<std::pair<size_t, size_t>> indices_t;

    inline std::function<bool(const std::string&, const std::string&)> compare_words =
    [] (const std::string& word1, const std::string& word2)
	{
		if (word1.length() != word2.length())
		{
			return word1.length() < word2.length();
		}
		else
		{
			return word1 < word2; // By lexicographic order.
		}
	};

	std::map<std::string, indices_t, decltype(compare_words)> find_words(const std::vector<std::vector<char>>& grid);
}

#endif
