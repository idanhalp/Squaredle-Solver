#include "Algorithm.hpp"
#include "InputOutputProcessor.hpp"
#include "Parameters.hpp"
#include "Trie.hpp"

namespace AlgorithmVersionWithoutIndices
{
	const std::array<std::pair<int, int>, 8> DIRECTIONS = {std::make_pair(-1, 0),  // Up
														   std::make_pair(1, 0),   // Down
														   std::make_pair(0, -1),  // Left
														   std::make_pair(0, 1),   // Right
														   std::make_pair(-1, -1), // Up and left
														   std::make_pair(-1, 1),  // Up and right
														   std::make_pair(1, -1),  // Down and left
														   std::make_pair(1, 1)};  // Down and right

	/**
	 * @brief Traverses the grid and adds occurring words to found_words.
	 *
	 * @param row 			Current row.
	 * @param col 			Current column.
	 * @param current_word 	String representing the current path in the grid.
	 * @param trie_node 	Current position in the trie.
	 * @param visited 		Indicates wether some cell was already visited
	 * @param found_words 	Words that were found during the grid traversal.
	 * @param grid 			Input grid.
	 */
	void dfs(const size_t row, const size_t col,
			 std::string& current_word,
			 const TrieNode* const trie_node,
			 std::vector<std::vector<bool>>& visited,
			 std::vector<std::string>& found_words,
			 const std::vector<std::vector<char>>& grid)
	{
		const bool prefix_not_in_dictionary = trie_node == nullptr;

		if (prefix_not_in_dictionary)
		{
			return;
		}

		visited[row][col] = true;
		current_word.push_back(grid[row][col]);

		if (trie_node->is_complete_word)
		{
			found_words.push_back(current_word);
		}

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
			dfs(next_row, next_col, current_word, next_trie_node, visited, found_words, grid);
		}

		// Backtrack
		visited[row][col] = false;
		current_word.pop_back();
	}

	/**
	 * @brief Finds the words that occur in the letters grid.
	 *
	 * @param grid 2d grid filled with letters.
	 * 
	 * @return List with all the words in the grid (might contain duplicates).
	 */
	std::vector<std::string> find_words(const std::vector<std::vector<char>>& grid)
	{
		static const Trie trie(InputOutputProcessor::get_list_of_valid_words());
		std::vector<std::string> found_words;

		for (size_t row = 0u; row < grid.size(); ++row)
		{
			for (size_t col = 0u; col < grid.size(); ++col)
			{
				if (grid[row][col] == Parameters::EMPTY_CELL)
				{
					continue;
				}

				// Find all the words that start at the (i, j) cell.
				std::string current_word = "";
				std::vector<std::vector<bool>> visited(grid.size(), std::vector<bool>(grid.size(), false));
				const TrieNode* const next_trie_node = trie.root->children[TrieNode::letter_to_index(grid[row][col])];
				dfs(row, col, current_word, next_trie_node, visited, found_words, grid);
			}
		}

		return found_words;
	}
}

namespace AlgorithmVersionWithIndices
{
	const std::array<std::pair<int, int>, 8> DIRECTIONS = {std::make_pair(-1, 0),  // Up
														   std::make_pair(1, 0),   // Down
														   std::make_pair(0, -1),  // Left
														   std::make_pair(0, 1),   // Right
														   std::make_pair(-1, -1), // Up and left
														   std::make_pair(-1, 1),  // Up and right
														   std::make_pair(1, -1),  // Down and left
														   std::make_pair(1, 1)};  // Down and right

	/**
	 * @brief Traverses the grid and adds occurring words to found_words.
	 *
	 * @param row 					Current row.
	 * @param col 					Current column.
	 * @param current_word_indices 	List of indices of the current path in the grid.
	 * @param trie_node 			Current position in the trie.
	 * @param visited 				Indicates wether some cell was already visited
	 * @param found_words_indices 	Lists of indices of words that were found during the grid traversal.
	 * @param grid 					Input grid.
	 * 
	 * @return Nothing. The ouput is inserted to `found_words_indices`.
	 */
	void dfs(const size_t row, const size_t col,
			 std::vector<std::pair<size_t, size_t>>& current_word_indices,
			 const TrieNode* const trie_node,
			 std::vector<std::vector<bool>>& visited,
			 std::vector<std::vector<std::pair<size_t, size_t>>>& found_words_indices,
			 const std::vector<std::vector<char>>& grid)
	{
		const bool prefix_not_in_dictionary = trie_node == nullptr;

		if (prefix_not_in_dictionary)
		{
			return;
		}

		visited[row][col] = true;
		current_word_indices.push_back(std::make_pair(row, col));

		if (trie_node->is_complete_word)
		{
			found_words_indices.push_back(current_word_indices);
		}

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
			dfs(next_row, next_col, current_word_indices, next_trie_node, visited, found_words_indices, grid);
		}

		// Backtrack
		visited[row][col] = false;
		current_word_indices.pop_back();
	}

	/**
	 * @brief Finds the indices of the words that occur in the letters grid.
	 *
	 * @param grid 2d grid filled with letters.
	 * 
	 * @return List with all the words in the grid (might contain duplicates).
	 */
	std::vector<std::vector<std::pair<size_t, size_t>>> find_words_indices(const std::vector<std::vector<char>>& grid)
	{
		static const Trie trie(InputOutputProcessor::get_list_of_valid_words());
		std::vector<std::vector<std::pair<size_t, size_t>>> found_words_indices;

		for (size_t row = 0u; row < grid.size(); ++row)
		{
			for (size_t col = 0u; col < grid.size(); ++col)
			{
				if (grid[row][col] == Parameters::EMPTY_CELL)
				{
					continue;
				}

				// Find all the words that start at the (i, j) cell.
				std::vector<std::pair<size_t, size_t>> current_word_indices;
				std::vector<std::vector<bool>> visited(grid.size(), std::vector<bool>(grid.size(), false));
				const TrieNode* const next_trie_node = trie.root->children[TrieNode::letter_to_index(grid[row][col])];
				dfs(row, col, current_word_indices, next_trie_node, visited, found_words_indices, grid);
			}
		}

		return found_words_indices;
	}
}