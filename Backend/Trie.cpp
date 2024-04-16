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
		if (!node->children[c - 'a']) // if the prefix appears for the first time
		{
			node->children[c - 'a'] = new TrieNode();
		}

		node = node->children[c - 'a'];
	}

	node->is_full_word = true;
}
