#include "Source/Backend/Algorithm.hpp"
#include "Source/Backend/InputOutputProcessor.hpp"
#include "Source/Backend/Trie.hpp"
#include "Source/Parameters.hpp"

namespace AlgorithmVersionWithIndices
{
	std::string create_word_from_indices(const indices_t& indices, const std::vector<std::vector<char>>& grid);

	void dfs(
		const size_t row,
		const size_t col,
		indices_t& indices,
		const TrieNode* const trie_node,
		std::vector<std::vector<bool>>& visited,
		std::map<std::string, indices_t, decltype(compare_words)>& word_to_indices,
		const std::vector<std::vector<char>>& grid);
}

std::string AlgorithmVersionWithIndices::create_word_from_indices(const indices_t& indices, const std::vector<std::vector<char>>& grid)
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
 * @param row              Current row.
 * @param col              Current column.
 * @param indices          List of indices of the current path in the grid.
 * @param trie_node        Current position in the trie.
 * @param visited          Indicates whether some cell was already visited
 * @param word_to_indices  Map of words to their indices.
 * @param grid             Input grid.
 *
 * @return Nothing. The output is inserted to `word_to_indices`.
*/
void AlgorithmVersionWithIndices::dfs(
	const size_t row,
	const size_t col,
	indices_t& indices,
	const TrieNode* const trie_node,
	std::vector<std::vector<bool>>& visited,
	std::map<std::string, indices_t, decltype(compare_words)>& word_to_indices,
	const std::vector<std::vector<char>>& grid)
{
	const bool prefix_not_in_dictionary = trie_node == nullptr;

	if (prefix_not_in_dictionary)
	{
		return;
	}

	visited[row][col] = true;
	indices.push_back(std::make_pair(row, col));

	if (trie_node->is_complete_word)
	{
		const std::string found_word = create_word_from_indices(indices, grid);
		word_to_indices[found_word] = indices;
	}

	static const std::array<std::pair<int, int>, 8> DIRECTIONS =
	{
		std::make_pair(-1, 0),  // Up
		std::make_pair(1, 0),   // Down
		std::make_pair(0, -1),  // Left
		std::make_pair(0, 1),   // Right
		std::make_pair(-1, -1), // Up and left
		std::make_pair(-1, 1),  // Up and right
		std::make_pair(1, -1),  // Down and left
		std::make_pair(1, 1),	// Down and right
	};

	// Try continuing in every direction.
	for (const auto [row_direction, col_direction] : DIRECTIONS)
	{
		const size_t next_row = row + row_direction;
		const size_t next_col = col + col_direction;
		const bool is_outside_grid = next_row >= grid.size() || next_col >= grid.size();

		if (is_outside_grid)
		{
			continue;
		}

		const bool is_empty_cell = grid[next_row][next_col] == Parameters::EMPTY_CELL;
		const bool is_already_visited = visited[next_row][next_col];

		if (is_empty_cell || is_already_visited)
		{
			continue;
		}

		const char next_letter = grid[next_row][next_col];
		const TrieNode* const next_trie_node = trie_node->children[TrieNode::letter_to_index(next_letter)];
		dfs(next_row, next_col, indices, next_trie_node, visited, word_to_indices, grid);
	}

	// Backtrack
	visited[row][col] = false;
	indices.pop_back();
}

/**
 * @brief  Finds the words that occur in the letters grid and their indices.
 * @param  grid 2d grid filled with letters.
 * @return A map whose keys are the words in the grid, and the values are their respective indices.
*/
auto AlgorithmVersionWithIndices::find_words(const std::vector<std::vector<char>>& grid) ->
	std::map<std::string, indices_t, decltype(compare_words)>
{
	static const Trie trie(InputOutputProcessor::get_list_of_valid_words());
	std::map<std::string, indices_t, decltype(compare_words)> word_to_indices(compare_words);

	for (size_t row = 0u; row < grid.size(); ++row)
	{
		for (size_t col = 0u; col < grid.size(); ++col)
		{
			if (grid[row][col] == Parameters::EMPTY_CELL)
			{
				continue;
			}

			// Find all the words that start at the (i, j) cell.
			indices_t indices;
			std::vector<std::vector<bool>> visited(grid.size(), std::vector<bool>(grid.size(), false));
			const TrieNode* const next_trie_node = trie.root->children[TrieNode::letter_to_index(grid[row][col])];
			dfs(row, col, indices, next_trie_node, visited, word_to_indices, grid);
		}
	}

	return word_to_indices;
}

