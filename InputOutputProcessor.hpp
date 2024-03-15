#ifndef INPUTPROCESSOR_H
#define INPUTPROCESSOR_H

#include <vector>
#include <string>

namespace InputOutputProcessor
{
    const char EMPTY_CELL = '-';

    std::vector<std::vector<char>> process_input();
    std::vector<std::string> get_list_of_valid_words();
    void process_output(std::vector<std::string>& found_words);
}

#endif