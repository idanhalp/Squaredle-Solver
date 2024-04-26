#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

#include <vector>
#include <string>

namespace AlgorithmVersionWithoutIndices
{
	std::vector<std::string> find_words(const std::vector<std::vector<char>>& grid);
}

namespace AlgorithmVersionWithIndices
{	
	std::vector<std::vector<std::pair<size_t, size_t>>> find_words_indices(const std::vector<std::vector<char>>& grid);
}

#endif