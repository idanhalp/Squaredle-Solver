#ifndef TRIE_HPP
#define TRIE_HPP

#include "Source/Backend/TrieNode.hpp"
#include <string>
#include <string_view>
#include <vector>

/**
* Trie is a data structure used for efficiently storing and finding words.
* Usually, it supports operations such as checking if a word (or a prefix)
* exists amongst the inserted words.
*/
class Trie
{
public:
	Trie(const std::vector<std::string> dictionary);
	~Trie();

	auto insert(std::string_view word) -> void;
	auto check_if_prefix_exists(std::string_view prefix) const -> bool;
	auto check_if_complete_word_exists(std::string_view word) const -> bool;

private:
	TrieNode* const root;
};

#endif
