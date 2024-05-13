#include "InputOutputProcessor.hpp"
#include "../Parameters.hpp"
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
	 */
	[[deprecated("The original text file was already processed.")]]
	void remove_definitions()
	{
		std::ifstream input_file(raw_input_file_name);

		if (!input_file.is_open())
		{
			throw std::invalid_argument("Cannot open " + raw_input_file_name + "!\n");
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
			throw std::invalid_argument("Cannot open " + processed_input_file_name + "!\n");
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
		// const std::vector<std::vector<char>> grid{{'f', 'a', 'z', 'e'},
		// 										  {'e', 'a', 'u', 'n'},
		// 										  {'d', 'l', 'e', 't'},
		// 										  {'y', 'm', 'i', 'a'}};

		// Giant Squaredle
		const std::vector<std::vector<char>> grid {{'r','g','e','r','i','r','e','w','a','t'},
													{'u','o','d','j','l','f','p','r','b','e'},
													{'a','n','g','o','k','e','o','o','m','r'},
													{'r','u','r','a','c','r','r','x','o','e'},
													{'b','d','n','c','f','i','r','e','b','w'},
													{'l','a','e','r','i','f','b','p','o','t'},
													{'e','m','r','b','d','r','y','a','l','u'},
													{'u','o','t','s','e','g','l','c','t','g'},
													{'z','s','h','g','i','f','a','l','e','s'},
													{'e','a','b','e','r','e','w','o','r','k'}};

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
	[[deprecated]]
	void process_output_without_indices(std::vector<std::string>& found_words)
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
		const int num_of_words_found = static_cast<int>(found_words.size());
		std::cout << "Found " << num_of_words_found << " words!\n";

		size_t previous_word_length = 0u;
		size_t word_index = 0u;

		for (const std::string& word : found_words)
		{
			if (word.length() != previous_word_length)
			{
				std::cout << "\nWords with " << word.length() << " letters:\n";
				previous_word_length = word.length();
				word_index = 1u;
			}

			std::cout << word_index++ << ") " << word << "\n";
		}
	}

	/** 
	 * Removes lists of indices whose representative word is already represented by 
	 * another list.
	 * Also sorts the lists by their length and the lexicographic order of the words
	 * they represent
	 *
	 * @param found_words_indices 	Lists of indices of words occurring in the input.
	 * @param grid 					The input grid.
	 * 
	 * @return Nothing.
	 * 
	 * @result Modifies `found_words_indices`.
	 */
	[[deprecated]]
	void process_output_with_indices(	std::vector<std::vector<std::pair<size_t, size_t>>>& found_words_indices, 
										const std::vector<std::vector<char>>& grid)
	{
		// Each list of indices represents a word. This lambda helps recreate it.
		const auto create_word_from_indices = [&grid] (const auto& indices)
		{
			std::string output;
			output.reserve(indices.size());

			for (const auto [row, col] : indices)
			{
				output += grid[row][col];
			}

			return output;
		};

		// Sort the indices lists by length, (tie break by lexicographic order of their representative words) 
		// and make sure no two lists represent the same word.
		std::sort(found_words_indices.begin(), found_words_indices.end(), [&] (const auto& indices1, const auto& indices2)
		{
			if (indices1.size() != indices2.size())
			{
				return indices1.size() < indices2.size();
			}
			else 
			{
				// Compare the words represents by the indices by lexicographic order.
				return create_word_from_indices(indices1) < create_word_from_indices(indices2);
			}
		});

		// Remove redundant lists of indices.

		const auto indices_represent_same_word = [&](const auto& indices1, const auto& indices2)
		{
			return create_word_from_indices(indices1) == create_word_from_indices(indices2);
		};
		
		const auto duplicate_indices = std::unique(found_words_indices.begin(), found_words_indices.end(), indices_represent_same_word);
		found_words_indices.erase(duplicate_indices, found_words_indices.end());

		// **FOR DEBUG**
		// Print the results.
		const int num_of_words_found = static_cast<int>(found_words_indices.size());
		std::cout << "Found " << num_of_words_found << " words!\n";

		const auto create_string_representing_indices = [](const auto& indices)
		{
			const std::string arrow = " ==> ";
			std::string output;

			for (const auto [row, col] : indices)
			{
				output += "(" + std::to_string(row) + ", " + std::to_string(col) + ")" + arrow;
			}

			output.erase(output.length() - arrow.length()); // Remove the last arrow.

			return output;			
		};

		size_t previous_word_length = 0u;
		size_t word_index = 0u;

		for (const auto indices : found_words_indices)
		{
			if (indices.size() != previous_word_length)
			{
				std::cout << "\nWords with " << indices.size() << " letters:\n";
				previous_word_length = indices.size();
				word_index = 1u;
			}

			const std::string representative_word = create_word_from_indices(indices);
			const std::string indices_as_string = create_string_representing_indices(indices);

			std::cout << word_index++ << ") " << representative_word << "\n";
			std::cout << "Indices: " << indices_as_string << "\n";
		}
	}

	void process_output(const std::map<	std::string,											// Key
										AlgorithmVersionWithIndices::indices_t, 				// Value
										decltype(AlgorithmVersionWithIndices::compare_words)>& 	// Comparator
										word_to_indices)
	{
		size_t previous_word_length = 0u;
		size_t word_index = 0u;

		const auto create_string_representing_indices = [](const auto& indices)
		{
			const std::string arrow = " ==> ";
			std::string output;

			for (const auto [row, col] : indices)
			{
				output += "(" + std::to_string(row) + ", " + std::to_string(col) + ")" + arrow;
			}

			output.erase(output.length() - arrow.length()); // Remove the last arrow.

			return output;			
		};

		for (const auto& [word, indices] : word_to_indices)
		{
			
			if (indices.size() != previous_word_length)
			{
				std::cout << "\nWords with " << indices.size() << " letters:\n";
				previous_word_length = indices.size();
				word_index = 1u;
			}

			std::cout << word_index++ << ") " << word << "\n";
			std::cout << "Indices: " << create_string_representing_indices(indices) << "\n";
		}
	}
}
