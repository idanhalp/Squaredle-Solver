#include "Source/Backend/Algorithm.hpp"
#include "Tests/Algorithm/Algorithm.hpp"
#include <algorithm>
#include <ranges>
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

	const std::vector solution = Algorithm::find_words(grid);
	const auto get_word = [] (const Algorithm::WordInfo word_info) { return word_info.word; };
	const std::vector found_words = solution | std::views::transform(get_word) | std::ranges::to<std::vector>();
	const auto word_was_found = [&] (const std::string& word) -> bool { return std::ranges::find(found_words, word) != found_words.end(); };
	const bool all_words_were_found = std::ranges::all_of(obligatory_words, word_was_found);

	QVERIFY(all_words_were_found);

	const size_t expected_num_of_words = 63;
	const bool num_of_words_is_correct = found_words.size() == expected_num_of_words;
	QVERIFY(num_of_words_is_correct);
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

	const std::vector solution = Algorithm::find_words(grid);
	const auto get_word = [] (const Algorithm::WordInfo word_info) { return word_info.word; };
	const std::vector found_words = solution | std::views::transform(get_word) | std::ranges::to<std::vector>();
	const auto word_was_found = [&] (const std::string& word) -> bool { return std::ranges::find(found_words, word) != found_words.end(); };
	const bool all_words_were_found = std::ranges::all_of(obligatory_words, word_was_found);

	QVERIFY(all_words_were_found);

	const size_t expected_num_of_words = 104;
	const bool num_of_words_is_correct = found_words.size() == expected_num_of_words;
	QVERIFY(num_of_words_is_correct);
}

auto AlgorithmTests::test_grid_3() const -> void
{
	const std::vector<std::vector<char>>grid
	{
		{'o','i','e'},
		{'s','n','o'},
		{'e','d','p'}
	};

	const std::vector<std::string> obligatory_words
	{
		"dens",
		"done",
		"dons",
		"ends",
		"eons",
		"ions",
		"node",
		"nods",
		"nose",
		"odes",
		"ones",
		"pods",
		"pond",
		"send",
		"sine",
		"nodes",
		"noise",
		"nosed",
		"poise",
		"ponds",
		"onesie",
		"poised",
		"poison",
		"poisoned",
	};

	const std::vector<std::string> bonus_words
	{
		"dene",
		"deni",
		"desi",
		"donsie",
		"esne",
		"noised",
		"onos",
		"poind",
		"poinds",
		"pois",
		"pone",
		"pons",
		"sene",
		"sned",
		"sonde",
		"sone"
	};

	const std::vector solution = Algorithm::find_words(grid);
	const auto get_word = [] (const Algorithm::WordInfo word_info) { return word_info.word; };
	const std::vector found_words = solution | std::views::transform(get_word) | std::ranges::to<std::vector>();
	const auto word_was_found = [&] (const std::string& word) -> bool { return std::ranges::find(found_words, word) != found_words.end(); };
	const bool all_obligatory_words_were_found = std::ranges::all_of(obligatory_words, word_was_found);
	const bool all_bonus_words_were_found = std::ranges::all_of(bonus_words, word_was_found);

	QVERIFY(all_obligatory_words_were_found);
	QVERIFY(all_bonus_words_were_found);

	const size_t expected_num_of_words = 41;
	const bool num_of_words_is_correct = found_words.size() == expected_num_of_words;
	QVERIFY(num_of_words_is_correct);
}
