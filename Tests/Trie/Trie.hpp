#ifndef TESTS_TRIE_HPP
#define TESTS_TRIE_HPP

#include <QObject>
#include <QtTest>

class TrieTests : public QObject
{
	Q_OBJECT

private slots:
	auto test_trie() const -> void;
	auto test_empty_trie() const -> void;
};

#endif // TESTS_TRIE_HPP
