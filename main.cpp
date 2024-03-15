#include "InputOutputProcessor.hpp"
#include "Algorithm.hpp"

int main()
{
    const std::vector<std::vector<char>> letters = InputOutputProcessor::process_input();
    std::vector<std::string> found_words = Algorithm::find_words(letters);
    InputOutputProcessor::process_output(found_words);
}
