#ifndef INPUT_PROCESSOR_H
#define INPUT_PROCESSOR_H

#include <vector>
#include <string>

namespace InputOutputProcessor
{
	std::vector<std::vector<char>> process_input();
	std::vector<std::string> create_list_of_valid_words();
	const std::vector<std::string>& get_list_of_valid_words();
	void process_output(std::vector<std::string>& found_words);
}

#endif