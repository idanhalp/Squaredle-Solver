#include "InputProcessor.hpp"
#include "Algorithm.hpp"

int main()
{
    const std::vector<std::vector<char>> letters{   {'q','g','n','t'},
                                                    {'a','u','e','i'},
                                                    {'i','e','u','a'},
                                                    {'m','n','g','q'}};

    const std::vector<std::string> words = get_list_of_words();

    find_words(letters, words);
}