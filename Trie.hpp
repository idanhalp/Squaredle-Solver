#ifndef TRIE_H
#define TRIE_H

#include <array>
#include <vector>
#include <string>

class TrieNode
{
private:
    static const size_t NUM_OF_LETTERS = 26;

public:
    bool is_full_word;
    std::array<TrieNode*, NUM_OF_LETTERS> children;

    TrieNode() : is_full_word(false)
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
};

#endif