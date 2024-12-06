#include "Source/Backend/Trie/Trie.hpp"
#include "Tests/Trie/Trie.hpp"

auto TrieTests::test_trie() const -> void
{
	const Trie trie({"ab", "aaa", "ba", "b"});

	QVERIFY(trie.check_if_prefix_exists(""));
	QVERIFY(trie.check_if_prefix_exists("aaa"));
	QVERIFY(trie.check_if_prefix_exists("a"));
	QVERIFY(trie.check_if_prefix_exists("b"));
	QVERIFY(trie.check_if_prefix_exists("ba"));

	QVERIFY(trie.check_if_complete_word_exists("ab"));
	QVERIFY(trie.check_if_complete_word_exists("aaa"));
	QVERIFY(trie.check_if_complete_word_exists("ba"));
	QVERIFY(trie.check_if_complete_word_exists("b"));
	QVERIFY(!trie.check_if_complete_word_exists("a"));
	QVERIFY(!trie.check_if_complete_word_exists("aa"));
	QVERIFY(!trie.check_if_complete_word_exists("aaaa"));
	QVERIFY(!trie.check_if_complete_word_exists(""));
	QVERIFY(!trie.check_if_complete_word_exists("baz"));
}

auto TrieTests::test_empty_trie() const -> void
{
	const Trie trie({});

	QVERIFY(trie.check_if_prefix_exists(""));
	QVERIFY(!trie.check_if_complete_word_exists(""));
}
