#include <QGuiApplication>
#include <QQmlApplicationEngine>

// #include "../../Backend/Algorithm.hpp"
// #include "../../Backend/InputOutputProcessor.hpp"
// #include "gridmodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // const std::vector<std::vector<char>> grid = InputOutputProcessor::process_input();
    // std::vector<std::string> found_words = Algorithm::find_words(grid);
    // InputOutputProcessor::process_output(found_words);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("SquaredleSolver", "Main");

    return app.exec();
}
