#ifndef TRIE_NODE_HPP
#define TRIE_NODE_HPP

#include <array>

/*
	This implementation assumes the words inserted to the trie
	contain only lowercase letters.
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

	/**
	 * @brief Given a lowercase alphabetic letter, return its index in the alphabet.
	 * 
	 * @param letter A lowercase alphabetic letter.
	 * 
	 * @return Its index in the alphabet (Starting from 0).
	 * 
	 * @example letter_to_index('a') == 0
	 * @example letter_to_index('b') == 1
	 * @example letter_to_index('z') == 25
	*/
	static inline size_t letter_to_index(char letter)
	{
		return letter - 'a';
	}
};

#endif
