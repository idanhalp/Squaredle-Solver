#include "Source/Backend/InputOutputProcessor.hpp"
#include "Source/Parameters.hpp"
#include <QFile>
#include <QDebug>
#include <stdexcept>

auto InputOutputProcessor::get_list_of_valid_words() -> std::vector<std::string>
{
	QFile input(":/words.txt");

	if (!input.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		throw std::invalid_argument("Cannot open " + input.fileName().toStdString() + "!\n");
	}

	std::vector<std::string> words;
	QTextStream in(&input);

	while(!in.atEnd())
	{
		QString line = in.readLine();
		if (line.length() >= Parameters::MIN_WORD_LENGTH)
		{
			words.push_back(line.toStdString());
		}
	}

	return words;
}
