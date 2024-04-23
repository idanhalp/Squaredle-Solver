#ifndef INPUT_PROCESSOR_HPP
#define INPUT_PROCESSOR_HPP

#include <vector>
#include <string>

namespace InputOutputProcessor
{
	std::vector<std::vector<char>> process_input();
	std::vector<std::string> get_list_of_valid_words();
	void process_output_without_indices(std::vector<std::string>& found_words);
	void process_output_with_indices(std::vector<std::vector<std::pair<size_t, size_t>>>& found_words_indices, const std::vector<std::vector<char>>& grid);
}

#endif