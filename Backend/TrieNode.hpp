#ifndef TRIE_NODE_HPP
#define TRIE_NODE_HPP

#include <array>

/*
	This implementation assumes the words inserted to the trie
	contain only lowercase letters.

	The letters are assigned according to `letter_to_index` in Algorithm.cpp.
*/ 
class TrieNode
{
private:
	static const size_t NUM_OF_LETTERS = 26;

public:
	bool is_complete_word;
	std::array<TrieNode* , NUM_OF_LETTERS> children;

	TrieNode() : is_complete_word(false)
	{
		std::fill(children.begin(), children.end(), nullptr);
	}

	~TrieNode()
	{
		for (TrieNode* child : children)
		{
			if (child)
			{
				delete child; // Recursive destructor 😲
				child = nullptr;
			}
		}
	}
};

#endif
