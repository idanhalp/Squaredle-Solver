#include "InputOutputProcessor.hpp"
#include "Parameters.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <stdexcept>

namespace InputOutputProcessor
{
	const std::string raw_input_file_name = "Backend/wordsWithDefinitions.txt";
	const std::string processed_input_file_name = "Backend/words.txt";
	
	/**
	 * The original list of words contained their definitions, which is redundant for our purposes.
	 * This function creates a new text file with a single word in every line.
	 * Has no use if the original list is already modified.
	 */
	void remove_definitions()
	{
		std::ifstream input_file(raw_input_file_name);

		if (!input_file.is_open())
		{
			std::cout << "Cannot open file!";
			return;
		}

		std::ofstream output_file(processed_input_file_name);
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

	std::vector<std::string> get_list_of_valid_words()
	{
		// remove_definitions(); // done beforehand

		std::ifstream input(processed_input_file_name);

		if (!input.is_open())
		{
			throw std::invalid_argument("Cannot open words file!\n");
		}

		std::string s;
		std::vector<std::string> words;

		while (getline(input, s))
		{
			if (s.length() >= Parameters::MIN_WORD_LENGTH)
			{
				words.push_back(s);
			}
		}

		return words;
	}

	/**
	 * Reads the input.
	 *
	 * Currently the input is hardcoded.
	 *
	 * @return a 2d grid filled with letters.
	 */
	std::vector<std::vector<char>> process_input()
	{
		/* Example of an input with empty cells:

		const char XXX = Parameters::EMPTY_CELL;
		const std::vector<std::vector<char>> grid{
													{XXX,'h','d','i',XXX},
													{'c','e',XXX,'e','c'},
													{'r',XXX,'s',XXX,'a'},
													{'m','a',XXX,'t','a'},
													{XXX,'w','e','b',XXX}};
		*/

		// Squaredle of 15.4.2024
		const std::vector<std::vector<char>> grid{{'n', 'm', 'a', 'b'},
												  {'i', 'b', 'n', 'g'},
												  {'a', 'u', 'e', 'n'},
												  {'n', 'q', 'a', 't'}};

		if (std::any_of(grid.begin(), grid.end(), [&](const auto& row) { return row.size() != grid.size(); }))
		{
			throw std::invalid_argument("Grid must be square!\n");
		}

		return grid;
	}

	/**
	 * Presents the output in the desired manner.
	 *
	 * Prints the words found in the grid, ordered by their length.
	 *
	 * @param found_words The words occurring in the input.
	 */
	void process_output(std::vector<std::string>& found_words)
	{
		// Sort the words by length (tie break by lexicographic order) and remove duplicates.
		std::sort(found_words.begin(), found_words.end(), [](const std::string& word1, const std::string& word2)
		{
            if (word1.length() != word2.length())
            {
                return word1.length() < word2.length();
            }
            else
            {
                return word1 < word2; // by lexicographic order
            } 
		});

		found_words.erase(std::unique(found_words.begin(), found_words.end()), found_words.end()); // remove duplicates

		// Print the results.
		std::cout << "Found " << found_words.size() << " words!\n";

		for (size_t i = 0, previous_word_length = 0, word_index = 0; i < found_words.size(); ++i, ++word_index)
		{
			if (found_words[i].length() != previous_word_length)
			{
				std::cout << "\nwords with " << found_words[i].length() << " letters:\n";
				previous_word_length = found_words[i].length();
				word_index = 1;
			}

			std::cout << word_index << ") " << found_words[i] << "\n";
		}
	}
}
