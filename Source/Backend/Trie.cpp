#include "Source/Backend/Trie.hpp"

Trie::Trie(const std::vector<std::string> dictionary) : root(new TrieNode)
{
	for (const std::string_view word : dictionary)
	{
		insert(word);
	}
}

Trie::~Trie()
{
	delete root;
}

auto Trie::insert(const std::string_view word) -> void
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

auto Trie::check_if_prefix_exists(const std::string_view prefix) const -> bool
{
	TrieNode* node = root;

	for (const char c : prefix)
	{
		const bool child_exists = node->children[TrieNode::letter_to_index(c)] != nullptr;

		if (!child_exists)
		{
			return false;
		}

		node = node->children[TrieNode::letter_to_index(c)];
	}

	return true;
}

auto Trie::check_if_complete_word_exists(const std::string_view word) const -> bool
{
	TrieNode* node = root;

	for (const char c : word)
	{
		const bool child_exists = node->children[TrieNode::letter_to_index(c)] != nullptr;

		if (!child_exists)
		{
			return false;
		}

		node = node->children[TrieNode::letter_to_index(c)];
	}

	return node->is_complete_word;
}
