#ifndef TESTS_ALGORITHM_HPP
#define TESTS_ALGORITHM_HPP

#include <QObject>
#include <QtTest>

class AlgorithmTests : public QObject
{
	Q_OBJECT

private slots:
	auto test_grid_1() const -> void;
	auto test_grid_2() const -> void;
	auto test_grid_3() const -> void;
	auto test_grid_with_empty_cells() const -> void;
	auto test_grid_without_words() const -> void;
	auto test_large_grid() const -> void;
};

#endif // TESTS_ALGORITHM_HPP
