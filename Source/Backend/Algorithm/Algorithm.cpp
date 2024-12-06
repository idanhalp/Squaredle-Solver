#include "Source/Backend/Algorithm/Algorithm.hpp"
#include "Source/Backend/Trie/Trie.hpp"
#include "Source/Backend/WordProcessing/WordProcessing.hpp"
#include "Source/Parameters.hpp"
#include <algorithm>

namespace Algorithm
{
	auto dfs(
		size_t row,
		size_t col,
		std::string& word,
		indices_t& indices,
		std::vector<std::vector<bool>>& visited,
		std::vector<WordInfo>& words_and_indices,
		const std::vector<std::vector<char>>& grid) -> void;

	auto backtrack(
		size_t row,
		size_t col,
		std::string& word,
		indices_t& indices,
		std::vector<std::vector<bool>>& visited) -> void;

	auto process_output(std::vector<WordInfo>& words_and_indices) -> void;
}

/**
 * @brief Traverses the grid and adds occurring words to found_words.
 *
 * @param row                Current row.
 * @param col                Current column.
 * @param word               Word created by the current path.
 * @param indices            List of indices of the current path.
 * @param trie_node          Current position in the trie.
 * @param visited            Indicates whether some cell was already visited
 * @param words_and_indices  List of words and their indices.
 * @param grid               Input grid.
 *
 * @return Nothing. The output is inserted to `words_and_indices`.
*/
auto Algorithm::dfs(
	const size_t row,
	const size_t col,
	std::string& word,
	indices_t& indices,
	std::vector<std::vector<bool>>& visited,
	std::vector<WordInfo>& words_and_indices,
	const std::vector<std::vector<char>>& grid) -> void
{
	static const Trie trie(InputOutputProcessor::get_list_of_valid_words());

	visited[row][col] = true;
	word.push_back(grid[row][col]);
	indices.emplace_back(row, col);

	const bool prefix_is_in_dictionary = trie.check_if_prefix_exists(word);

	if (!prefix_is_in_dictionary)
	{
		backtrack(row, col, word, indices, visited);
		return;
	}

	const bool complete_word_found = trie.check_if_complete_word_exists(word);

	if (complete_word_found)
	{
		words_and_indices.emplace_back(word, indices);
	}

	static const std::array DIRECTIONS =
	{
		std::make_pair(-1, +0), // Up
		std::make_pair(+1, +0), // Down
		std::make_pair(+0, -1), // Left
		std::make_pair(+0, +1), // Right
		std::make_pair(-1, -1), // Up and left
		std::make_pair(-1, +1), // Up and right
		std::make_pair(+1, -1), // Down and left
		std::make_pair(+1, +1),	// Down and right
	};

	// Try continuing in every direction.
	for (const auto [row_direction, col_direction] : DIRECTIONS)
	{
		const size_t next_row = row + row_direction;
		const size_t next_col = col + col_direction;
		const bool cell_is_outside_grid = next_row >= grid.size() || next_col >= grid.size();

		if (cell_is_outside_grid)
		{
			continue;
		}

		const bool cell_is_empty = grid[next_row][next_col] == Parameters::EMPTY_CELL;
		const bool cell_was_already_visited = visited[next_row][next_col];

		if (cell_is_empty || cell_was_already_visited)
		{
			continue;
		}

		dfs(next_row, next_col, word, indices, visited, words_and_indices, grid);
	}

	backtrack(row, col, word, indices, visited);
}


auto Algorithm::backtrack(
	const size_t row,
	const size_t col,
	std::string& word,
	indices_t& indices,
	std::vector<std::vector<bool>>& visited) -> void
{
	word.pop_back();
	indices.pop_back();
	visited[row][col] = false;
}

auto Algorithm::process_output(std::vector<WordInfo>& words_and_indices) -> void
{
	std::ranges::sort(words_and_indices);

	// Remove duplicates
	const auto duplicates = std::ranges::unique(words_and_indices);
	words_and_indices.erase(duplicates.begin(), duplicates.end());
}

/**
 * @brief  Finds the words that occur in the letters grid and their indices.
 * @param  grid 2d grid filled with letters.
 * @return A map whose keys are the words in the grid, and the values are their respective indices.
*/
auto Algorithm::find_words(const std::vector<std::vector<char>>& grid) -> std::vector<WordInfo>
{
	std::vector<WordInfo> words_and_indices;

	for (size_t row = 0; row < grid.size(); ++row)
	{
		for (size_t col = 0; col < grid.size(); ++col)
		{
			if (grid[row][col] == Parameters::EMPTY_CELL)
			{
				continue;
			}

			// Find all the words that start at the (i, j) cell.
			std::string word;
			indices_t indices;
			std::vector<std::vector<bool>> visited(grid.size(), std::vector<bool>(grid.size(), false));

			dfs(row, col, word, indices, visited, words_and_indices, grid);
		}
	}

	process_output(words_and_indices);

	return words_and_indices;
}

