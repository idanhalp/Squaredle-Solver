#ifndef TESTS_ALGORITHM_HPP
#define TESTS_ALGORITHM_HPP

#include <QObject>
#include <QtTest>

class AlgorithmTests : public QObject
{
	Q_OBJECT

private slots:
	auto test_grid_1() const -> void;

private:

};

#endif // TESTS_ALGORITHM_HPP
