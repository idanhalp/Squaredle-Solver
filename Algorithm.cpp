#include "Algorithm.hpp"
#include "InputOutputProcessor.hpp"
#include "Trie.hpp"
#include <iostream>
#include <algorithm>
#include <stdexcept>

namespace Algorithm
{
    // We can move down, up, left, right and in 4 diagonals.
    const std::vector<std::vector<int>> DIRECTIONS{{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

    /**
     * @brief Traverses the grid and adds occurring words to found_words.
     * 
     * @param row current row.
     * @param col current column.
     * @param current_word string representing the current path in the grid.
     * @param trie_node current position in the trie.
     * @param visited indicates wether some cell was already visited
     * @param found_words words that were found during the grid traversal.
     * @param letters input grid. 
     */
    void dfs(const size_t row, const size_t col, 
            std::string& current_word, 
            const TrieNode* const trie_node, 
            std::vector<std::vector<bool>>& visited, 
            std::vector<std::string>& found_words,
            const std::vector<std::vector<char>>& letters)
    {
        if (trie_node) // current_word is still a valid prefix
        {
            visited[row][col] = true;
            current_word.push_back(letters[row][col]);

            if (trie_node->is_full_word)
            {
                found_words.push_back(current_word);
            }

            // Try continuing in every direction.
            for (const std::vector<int>& direction : DIRECTIONS)
            {
                const size_t next_row = row + direction[0];
                const size_t next_col = col + direction[1];

                if (next_row < letters.size() && next_col < letters.size() && 
                    !visited[next_row][next_col] &&
                    letters[next_row][next_col] != InputOutputProcessor::EMPTY_CELL)
                {
                    dfs(next_row, next_col, current_word, trie_node->children[letters[next_row][next_col] - 'a'], visited, found_words, letters);
                }
            }

            // Backtrack
            visited[row][col] = false;
            current_word.pop_back();
        }
    }

    /**
     * @brief Finds the words that occur in the letters grid.
     * 
     * @param letters a 2d grid filled with letters.
     * @return a list with all the words in the grid (might contain duplicates).
     */
    std::vector<std::string> find_words(const std::vector<std::vector<char>>& letters)
    {
        if (std::any_of(letters.begin(), letters.end(), [&](const auto& row) { return row.size() != letters.size(); }))
        {
            throw std::invalid_argument("Grid must be square!\n");
        }
        
        const std::vector<std::string> dictionary = InputOutputProcessor::get_list_of_valid_words();
        const Trie trie(dictionary); // inserts every word in words to the trie
        std::vector<std::string> found_words;

        for (size_t i = 0; i < letters.size(); ++i)
        {
            for (size_t j = 0; j < letters.size(); ++j)
            {
                // Find all the words that start at the (i, j) cell.
                std::string current_word = "";
                std::vector<std::vector<bool>> visited(letters.size(), std::vector<bool>(letters.size(), false));
                dfs(i, j, current_word, trie.root->children[letters[i][j] - 'a'], visited, found_words, letters);
            }
        }

        return found_words;    
    }
}
