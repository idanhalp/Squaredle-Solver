#ifndef TRIE_H
#define TRIE_H

#include <vector>
#include <string>

class TrieNode
{
public:
    bool is_full_word;
    std::vector<TrieNode*> children;

    TrieNode() : is_full_word(false)
    {
        const int num_of_letters = 'z' - 'a' + 1;
        children.resize(num_of_letters);
    }

    ~TrieNode()
    {
        for (auto* child : children)
        {
            if (child)
            {
                delete child;
                child = nullptr;
            }
        }
    }
};

class Trie
{
public:
    // Normally the nodes are inaccessible, but in this case 
    // having direct access to them is necessary to guarantee efficiency.
    TrieNode* const root;  

    Trie();
    Trie(const std::vector<std::string> words);
    ~Trie();
    void insert(const std::string& word);
    bool contains_word(const std::string& word) const;
    bool contains_prefix(const std::string& prefix) const;
};

#endif