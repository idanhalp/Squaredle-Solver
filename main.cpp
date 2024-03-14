#include "Algorithm.hpp"

int main()
{
    const std::vector<std::vector<char>> letters{   {'q','g','n','t'},
                                                    {'a','u','e','i'},
                                                    {'i','e','u','a'},
                                                    {'m','n','g','q'}};

    find_words(letters);
}