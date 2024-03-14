#include "Trie.hpp"

Trie::Trie() : root(new TrieNode)
{
}

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

bool Trie::contains_word(const std::string& word) const
{
    TrieNode* node = root;

    for (const char c : word)
    {
        if (!node->children[c - 'a']) // if the prefix does not appear
        {
            return false;
        }
        else
        {
            node = node->children[c - 'a'];
        }
    }

    return node->is_full_word; // make sure it is not just a prefix
}

bool Trie::contains_prefix(const std::string& prefix) const
{
    TrieNode* node = root;

    for (const char c : prefix)
    {
        if (!node->children[c - 'a']) // if the prefix does not appear
        {
            return false;
        }
        else
        {
            node = node->children[c - 'a'];
        }
    }

    return true;
}