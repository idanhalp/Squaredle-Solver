#include "Tests/Algorithm/Algorithm.hpp"
#include "Tests/Trie/Trie.hpp"
#include <QtTest>

auto main(const int num_of_arguments, char* arguments[]) -> int
{
	const auto run = [&] <typename TEST> (TEST test) -> int { return QTest::qExec(&test, num_of_arguments, arguments); };
	const int status = run(AlgorithmTests()) | run(TrieTests());
	const bool all_tests_passed = status == 0;

	if (all_tests_passed)
	{
		qDebug() << "All the tests passed!";
	}
	else
	{
		qDebug() << "Some of the tests failed!";
	}

	return status;
}
