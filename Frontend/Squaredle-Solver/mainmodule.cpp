#include "mainmodule.h"
#include "../../Backend/Algorithm.hpp"
#include "../../Backend/InputOutputProcessor.hpp"

MainModule::MainModule(QObject *parent)
    : QObject{parent},
    m_gridModel(new GridModel(this)),
    m_resultsModel(new ResultsModel(this))
{}

GridModel *MainModule::gridModel() const
{
    return m_gridModel;
}

void MainModule::setGridModel(GridModel *newGridModel)
{
    m_gridModel = newGridModel;
}

ResultsModel *MainModule::resultsModel() const
{
    return m_resultsModel;
}

void MainModule::setResultsModel(ResultsModel *newResultsModel)
{
    m_resultsModel = newResultsModel;
}

void MainModule::solve()
{
    std::vector<std::vector<char>> grid(m_gridModel->rows(), std::vector<char>(m_gridModel->rows(), ' '));
    int k = 0;

    for (int i = 0; i < m_gridModel->rows(); i++)
    {
        for (int j = 0; j < m_gridModel->columns(); j++)
        {
            grid[i][j] = m_gridModel->getGrid()[k];
            k++;
        }
    }

    std::vector<std::string> found_words = Algorithm::find_words(grid);
    InputOutputProcessor::process_output(found_words);
}
