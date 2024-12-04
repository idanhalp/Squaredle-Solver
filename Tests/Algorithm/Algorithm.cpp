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

auto AlgorithmTests::test_grid_2() const -> void
{
	const std::vector<std::vector<char>>grid
	{
		{'v','i','n','e'},
		{'a','d','m','r'},
		{'l','e','f','u'},
		{'c','u','y','l'}
	};

	const std::vector<std::string> obligatory_words
	{
		"aide",
		"avid",
		"clad",
		"clef",
		"clue",
		"cued",
		"dale",
		"deal",
		"defy",
		"dial",
		"dime",
		"dine",
		"diva",
		"fuel",
		"fume",
		"idea",
		"idle",
		"laid",
		"lain",
		"lead",
		"lure",
		"mead",
		"meal",
		"meld",
		"mend",
		"mind",
		"mine",
		"rend",
		"vain",
		"vale",
		"vial",
		"vine",
		"admin",
		"aimed",
		"claim",
		"clued",
		"diner",
		"femur",
		"flume",
		"fremd",
		"fumed",
		"ideal",
		"lemur",
		"lumen",
		"medal",
		"media",
		"miner",
		"value",
		"demure",
		"menial",
		"remind",
		"vainer",
		"valued",
		"claimed",
		"mindful",
		"remedial"
	};

	const auto solution = AlgorithmVersionWithIndices::find_words(grid);
	const auto word_was_found = [&] (const std::string& word) -> bool { return solution.contains(word); };
	const bool all_words_were_found = std::ranges::all_of(obligatory_words, word_was_found);

	QVERIFY(all_words_were_found);
}
