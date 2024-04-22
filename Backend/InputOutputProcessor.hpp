#ifndef INPUT_PROCESSOR_HPP
#define INPUT_PROCESSOR_HPP

#include <vector>
#include <string>

namespace InputOutputProcessor
{
	std::vector<std::vector<char>> process_input();
	std::vector<std::string> get_list_of_valid_words();
    std::vector<std::string> process_output(std::vector<std::string>& found_words);
}

#endif
