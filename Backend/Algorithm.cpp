#include "Algorithm.hpp"
#include "InputOutputProcessor.hpp"
#include "Parameters.hpp"
#include "Trie.hpp"

namespace Algorithm
{
	const std::array<std::pair<int, int>, 8> DIRECTIONS = {std::make_pair(-1, 0),  // up
														   std::make_pair(1, 0),   // down
														   std::make_pair(0, -1),  // left
														   std::make_pair(0, 1),   // right
														   std::make_pair(-1, -1), // up and left
														   std::make_pair(-1, 1),  // up and right
														   std::make_pair(1, -1),  // down and left
														   std::make_pair(1, 1)};  // down and right

	/**
	 * @brief Traverses the grid and adds occurring words to found_words.
	 *
	 * @param row current row.
	 * @param col current column.
	 * @param current_word string representing the current path in the grid.
	 * @param trie_node current position in the trie.
	 * @param visited indicates wether some cell was already visited
	 * @param found_words words that were found during the grid traversal.
	 * @param grid input grid.
	 */
	void dfs(const size_t row, const size_t col,
			 std::string& current_word,
			 const TrieNode* const trie_node,
			 std::vector<std::vector<bool>>& visited,
			 std::vector<std::string>& found_words,
			 const std::vector<std::vector<char>>& grid)
	{
		// Make sure that current_word is a valid prefix of some word in the original dictionary.
		if (!trie_node)
		{
			return;
		}

		visited[row][col] = true;
		current_word.push_back(grid[row][col]);

		if (trie_node->is_full_word)
		{
			found_words.push_back(current_word);
		}

		// Try continuing in every direction.
		for (const auto& direction : DIRECTIONS)
		{
			const int row_direction = direction.first;
			const int col_direction = direction.second;
			const size_t next_row = row + row_direction;
			const size_t next_col = col + col_direction;

			const bool is_within_grid = next_row < grid.size() && next_col < grid.size();

			if (!is_within_grid)
			{
				continue;
			}

			const bool is_empty_cell = grid[next_row][next_col] == Parameters::EMPTY_CELL;
			const bool is_already_visited = visited[next_row][next_col];

			if (is_empty_cell || is_already_visited)
			{
				continue;
			}

			dfs(next_row, next_col, current_word, trie_node->children[grid[next_row][next_col] - 'a'], visited, found_words, grid);
		}

		// Backtrack
		visited[row][col] = false;
		current_word.pop_back();
	}

	/**
	 * @brief Finds the words that occur in the letters grid.
	 *
	 * @param grid a 2d grid filled with letters.
	 * @return a list with all the words in the grid (might contain duplicates).
	 */
	std::vector<std::string> find_words(const std::vector<std::vector<char>>& grid)
	{
		const std::vector<std::string> dictionary = InputOutputProcessor::get_list_of_valid_words();
		const Trie trie(dictionary); // inserts every word in words to the trie
		std::vector<std::string> found_words;

		for (size_t row = 0; row < grid.size(); ++row)
		{
			for (size_t col = 0; col < grid.size(); ++col)
			{
				if (grid[row][col] == Parameters::EMPTY_CELL)
				{
					continue;
				}

				// Find all the words that start at the (i, j) cell.
				std::string current_word = "";
				std::vector<std::vector<bool>> visited(grid.size(), std::vector<bool>(grid.size(), false));
				dfs(row, col, current_word, trie.root->children[grid[row][col] - 'a'], visited, found_words, grid);
			}
		}

		return found_words;
	}
}
