#ifndef TRIE_NODE_HPP
#define TRIE_NODE_HPP

#include <array>

/*
	This implementation assumes the words inserted to the trie
	contain only lowercase letters.

	The letter 'a' is assigned to the child node at index 0,
	the letter 'b' is assigned to the child node at index 1,
	.
	.
	.
	the letter 'z' is assigned to the child node at index 25.
*/ 
class TrieNode
{
private:
	static const size_t NUM_OF_LETTERS = 26;

public:
	bool is_full_word;
	std::array<TrieNode* , NUM_OF_LETTERS> children;

	TrieNode() : is_full_word(false)
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
