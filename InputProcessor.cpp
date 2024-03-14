#include "InputProcessor.hpp"
#include <fstream>
#include <iostream>

// The original list of words contained their definitions, which is redundant for our purposes.
// This function creates a new text file with a single word in every line.
// Has no use if the original list is already modified.
void remove_definitions()
{
    const std::string input_file_name = "wordsWithDefinitions.txt";
    std::ifstream input_file(input_file_name);

    if (!input_file.is_open())
    {
        std::cout << "Cannot open file!";
        return;
    }

    std::ofstream output_file("words.txt");
    std::string s;

    while (getline(input_file, s))
    {
        for (const char c : s)
        {
            if (c == ' ') // end of the word, start of the definition
            {
                break;
            }
            else
            {
                output_file << static_cast<char>(std::tolower(c));
            }
        }   

        output_file << "\n";
    }
}

std::vector<std::string> get_list_of_words()
{
    // remove_definitions(); // done beforehand

    std::ifstream input("words.txt");

    if (!input.is_open())
    {
        std::cout << "Cannot open words.txt!\n";
        return {};
    }

    const size_t MIN_WORD_LENGTH = 4;
    std::string s;
    std::vector<std::string> words;

    while (getline(input, s))
    {
        if (s.length() >= MIN_WORD_LENGTH)
        {
            words.push_back(s);
        }
    }

    return words;
}