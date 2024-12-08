#include "Source/Backend/Trie/Trie.hpp"

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

	for (const char letter : word)
	{
		if (!node->check_if_child_exists(letter)) // Prefix appears for the first time.
		{
			node->add_child(letter);
		}

		node = node->get_child(letter);
	}

	node->set_is_complete_word(true);
}

auto Trie::check_if_prefix_exists(const std::string_view prefix) const -> bool
{
	TrieNode* node = root;

	for (const char letter : prefix)
	{
		if (!node->check_if_child_exists(letter))
		{
			return false;
		}

		node = node->get_child(letter);
	}

	return true;
}

auto Trie::check_if_complete_word_exists(const std::string_view word) const -> bool
{
	TrieNode* node = root;

	for (const char letter : word)
	{
		if (!node->check_if_child_exists(letter))
		{
			return false;
		}

		node = node->get_child(letter);
	}

	return node->get_is_complete_word();
}
