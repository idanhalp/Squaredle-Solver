#include <array>

class TrieNode
{
private:
	static const size_t NUM_OF_LETTERS = 26;

public:
	bool is_full_word;
	std::array<TrieNode* , NUM_OF_LETTERS> children;

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