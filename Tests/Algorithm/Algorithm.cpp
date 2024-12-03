#include "Source/Backend/Algorithm.hpp"
#include "Tests/Algorithm/Algorithm.hpp"
#include <algorithm>
#include <string>
#include <vector>

auto AlgorithmTests::test_grid_1() const -> void
{
	const std::vector<std::vector<char>> grid
	{
		{'e', 'r', 'd', 'r'},
		{'n' ,'v', 'i', 'g'},
		{'a', 'd', 't', 'a'},
		{'y', 'n', 'o', 'i'}
	};

	const std::vector<std::string> obligatory_words
	{
		"anti",
		"avid",
		"dire",
		"diva",
		"dive",
		"gait",
		"gird",
		"give",
		"grid",
		"grit",
		"iota",
		"nerd",
		"rend",
		"tidy",
		"tire",
		"vane",
		"vend",
		"diver",
		"drive",
		"given",
		"giver",
		"river",
		"today",
		"driven",
		"driver",
		"aviation",
		"rendition",
		"navigation"
	};

	const auto solution = AlgorithmVersionWithIndices::find_words(grid);
	const auto word_was_found = [&] (const std::string& word) -> bool { return solution.contains(word); };
	const bool all_words_were_found = std::ranges::all_of(obligatory_words, word_was_found);

	QVERIFY(all_words_were_found);
}
