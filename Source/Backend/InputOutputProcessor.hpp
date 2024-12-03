#ifndef INPUT_PROCESSOR_HPP
#define INPUT_PROCESSOR_HPP

#include "Source/Backend/Algorithm.hpp"
#include <string>
#include <vector>

namespace InputOutputProcessor
{
    std::vector<std::vector<char>> process_input();
    std::vector<std::string> get_list_of_valid_words();
    std::vector<std::string> process_output_without_indices(std::vector<std::string>& found_words);
    void process_output_with_indices(std::vector<std::vector<std::pair<size_t, size_t>>>& found_words_indices, const std::vector<std::vector<char>>& grid);
	
	void process_output(const std::map<	std::string,											// Key
										AlgorithmVersionWithIndices::indices_t, 				// Value
										decltype(AlgorithmVersionWithIndices::compare_words)>& 	// Comparator
										word_to_indices);
}

#endif
