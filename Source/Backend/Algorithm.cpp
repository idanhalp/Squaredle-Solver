#include "Source/Backend/Algorithm.hpp"
#include "Source/Backend/InputOutputProcessor.hpp"
#include "Source/Backend/Trie.hpp"
#include "Source/Parameters.hpp"
#include <algorithm>

namespace Algorithm
{
	auto create_word_from_indices(const indices_t& indices, const std::vector<std::vector<char>>& grid) -> std::string;

	auto dfs(
		const size_t row,
		const size_t col,
		indices_t& indices,
		const TrieNode* const trie_node,
		std::vector<std::vector<bool>>& visited,
		std::vector<WordInfo>& words_and_indices,
		const std::vector<std::vector<char>>& grid) -> void;

	auto process_output(std::vector<WordInfo>& words_and_indices) -> void;
}

auto Algorithm::create_word_from_indices(const indices_t& indices, const std::vector<std::vector<char>>& grid) -> std::string
{
	std::string output;
	output.reserve(indices.size());

	for (const auto [row, col] : indices)
	{
		output += grid[row][col];
	}

	return output;
}

/**
 * @brief Traverses the grid and adds occurring words to found_words.
 *
 * @param row                Current row.
 * @param col                Current column.
 * @param indices            List of indices of the current path in the grid.
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
	indices_t& indices,
	const TrieNode* const trie_node,
	std::vector<std::vector<bool>>& visited,
	std::vector<WordInfo>& words_and_indices,
	const std::vector<std::vector<char>>& grid) -> void
{
	const bool prefix_is_in_dictionary = trie_node != nullptr;

	if (!prefix_is_in_dictionary)
	{
		return;
	}

	visited[row][col] = true;
	indices.push_back(std::make_pair(row, col));

	const bool complete_word_found = trie_node->is_complete_word;

	if (complete_word_found)
	{
		const std::string word = create_word_from_indices(indices, grid);
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

		const char next_letter = grid[next_row][next_col];
		const TrieNode* const next_trie_node = trie_node->children[TrieNode::letter_to_index(next_letter)];
		dfs(next_row, next_col, indices, next_trie_node, visited, words_and_indices, grid);
	}

	// Backtrack
	visited[row][col] = false;
	indices.pop_back();
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
	static const Trie trie(InputOutputProcessor::get_list_of_valid_words());
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
			indices_t indices;
			std::vector<std::vector<bool>> visited(grid.size(), std::vector<bool>(grid.size(), false));
			const TrieNode* const next_trie_node = trie.root->children[TrieNode::letter_to_index(grid[row][col])];
			dfs(row, col, indices, next_trie_node, visited, words_and_indices, grid);
		}
	}

	process_output(words_and_indices);

	return words_and_indices;
}

