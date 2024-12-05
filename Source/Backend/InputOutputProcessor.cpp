#include "Source/Backend/InputOutputProcessor.hpp"
#include <QFile>
#include <QDebug>
#include <stdexcept>

auto InputOutputProcessor::get_list_of_valid_words() -> std::vector<std::string>
{
	QFile words_file(":/words.txt");

	if (!words_file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		throw std::invalid_argument("Cannot open " + words_file.fileName().toStdString() + "!\n");
	}

	QTextStream input_stream(&words_file);
	std::vector<std::string> words;

	while (!input_stream.atEnd())
	{
		std::string word = input_stream.readLine().toStdString();
		words.push_back(std::move(word));
	}

	return words;
}
