#include "Trie.hpp"

Trie::Trie(const std::vector<std::string> words) : root(new TrieNode)
{
	for (const std::string& word : words)
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
		if (!node->children[TrieNode::letter_to_index(c)]) // if the prefix appears for the first time
		{
			node->children[TrieNode::letter_to_index(c)] = new TrieNode();
		}

		node = node->children[TrieNode::letter_to_index(c)];
	}

	node->is_complete_word = true;
}
