#include "InputOutputProcessor.hpp"
#include "Algorithm.hpp"
#include <chrono>
#include <iostream>

int main()
{
	const auto start_time = std::chrono::high_resolution_clock::now();

	while (true)
	{
		const std::vector<std::vector<char>> grid = InputOutputProcessor::process_input();
		std::vector<std::string> found_words = Algorithm::find_words(grid);
		InputOutputProcessor::process_output(found_words);
		break; // TODO: Decide when to break and change runtime calculation.
	}

	const auto end_time = std::chrono::high_resolution_clock::now();
	const auto runtime = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
	std::cout << "\nTotal runtime: " << runtime << " ms\n";
}
