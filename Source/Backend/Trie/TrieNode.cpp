#include "Source/Backend/Trie/TrieNode.hpp"

TrieNode::TrieNode() : is_complete_word(false)
{
	children.fill(nullptr);
}

TrieNode::~TrieNode()
{
	for (TrieNode* child : children)
	{
		const bool child_exists = child != nullptr;

		if (child_exists)
		{
			delete child; // Recursive destructor 😲
			child = nullptr;
		}
	}
}

auto TrieNode::get_is_complete_word() const -> bool
{
	return is_complete_word;
}

auto TrieNode::set_is_complete_word(const bool is_complete_word) -> void
{
	this->is_complete_word = is_complete_word;
}

auto TrieNode::add_child(char letter) -> void
{
	children[letter - 'a'] = new TrieNode;
}

auto TrieNode::get_child(const char letter) const -> TrieNode*
{
	return children[letter - 'a'];
}

auto TrieNode::check_if_child_exists(const char letter) const -> bool
{
	return get_child(letter) != nullptr;
}
