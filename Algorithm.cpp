#include "Algorithm.hpp"
#include "InputProcessor.hpp"
#include "Trie.hpp"
#include <iostream>
#include <algorithm>
#include <stdexcept>

// We can move down, up, left, right and in 4 diagonals
const std::vector<std::vector<int>> DIRECTIONS{{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

// Traverses the grid and adds occuring words to found_words.
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

            if (next_row < letters.size() && next_col < letters.size() && !visited[next_row][next_col])
            {
                dfs(next_row, next_col, current_word, trie_node->children[letters[next_row][next_col] - 'a'], visited, found_words, letters);
            }
        }

        // Backtrack
        visited[row][col] = false;
        current_word.pop_back();
    }
}

// Finds and prints all the words occuring in the letters grid.
void find_words(const std::vector<std::vector<char>>& letters)
{
    if (std::any_of(letters.begin(), letters.end(), [&](const auto& row) { return row.size() != letters.size(); }))
    {
        throw std::invalid_argument("Grid must be square!\n");
    }

    const std::vector<std::string> found_words = [&]()
    {
        const std::vector<std::string> words = get_list_of_words();
        const Trie trie(words); // inserts every word in words to the trie
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

        return found_words;
    }();   

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