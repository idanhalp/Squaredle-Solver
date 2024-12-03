#include "Trie.hpp"

Trie::Trie(const std::vector<std::string> dictionary) : root(new TrieNode)
{
	for (const std::string& word : dictionary)
	{
		insert(word);
	}
}

Trie::~Trie()
{
	delete root;
}

void Trie::insert(const std::string& word)
{
	TrieNode* node = root;

	for (const char c : word)
	{
		if (!node->children[TrieNode::letter_to_index(c)]) // If the prefix appears for the first time
		{
			node->children[TrieNode::letter_to_index(c)] = new TrieNode();
		}

		node = node->children[TrieNode::letter_to_index(c)];
	}

	node->is_complete_word = true;
}
