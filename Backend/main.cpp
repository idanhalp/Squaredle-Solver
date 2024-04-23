#include "InputOutputProcessor.hpp"
#include "Algorithm.hpp"
#include <chrono>
#include <iostream>

int main()
{
	const bool should_print_indices = true;

	const auto start_time = std::chrono::high_resolution_clock::now();
	const std::vector<std::vector<char>> grid = InputOutputProcessor::process_input();
	
	if (should_print_indices)
	{
		auto found_words_indices = AlgorithmVersionWithIndices::find_words_indices(grid);
		InputOutputProcessor::process_output_with_indices(found_words_indices, grid);
	}
	else
	{
		auto found_words = AlgorithmVersionWithoutIndices::find_words(grid);
		InputOutputProcessor::process_output_withput_indices(found_words);
	}

	const auto end_time = std::chrono::high_resolution_clock::now();
	const auto runtime = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
	
	std::cout << "\nTotal runtime: " << runtime << " ms\n";
}
