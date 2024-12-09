#ifndef TRIE_NODE_HPP
#define TRIE_NODE_HPP

#include <array>

/**
* This implementation assumes the words inserted to the trie
* contain only lowercase letters.
*/
class TrieNode
{
public:
	TrieNode();
	~TrieNode();

	auto get_is_complete_word() const -> bool;
	auto set_is_complete_word(bool is_complete_word) -> void;

	auto add_child(char letter) -> void;
	auto get_child(char letter) const -> TrieNode*;
	auto check_if_child_exists(char letter) const -> bool;

private:
	static const size_t NUM_OF_LETTERS = 26;

	bool is_complete_word;
	std::array<TrieNode*, NUM_OF_LETTERS> children;
};

#endif
