#ifndef TRIE_HPP
#define TRIE_HPP

#include "Source/Backend/TrieNode.hpp"
#include <string>
#include <vector>

/**
* Trie is a data structure used for efficiently storing and finding words.
* Usually, it supports operations such as checking if a word (or a prefix)
* exists amongst the inserted words.
* Such operations are not included in this implementation.
* Instead, we enable direct access to the internal nodes of the structure	to obtain high efficiency.
*/
class Trie
{
public:
	TrieNode* const root;

	Trie(const std::vector<std::string> dictionary);
	~Trie();
	auto insert(const std::string& word) -> void;
};

#endif
