#ifndef TRIE_HPP
#define TRIE_HPP

#include "TrieNode.hpp" 
#include <vector>
#include <string>

class Trie
{
public:
	// Normally the nodes are inaccessible, but in this case
	// having direct access to them is necessary to guarantee efficiency.
	TrieNode* const root;

	Trie(const std::vector<std::string> words);
	~Trie();
	void insert(const std::string& word);
};

#endif