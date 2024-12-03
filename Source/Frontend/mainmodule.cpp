#include "Source/Backend/Algorithm.hpp"
#include "Source/Frontend/mainmodule.h"

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
    if (!m_gridModel->isGridValid())
    {
        m_resultsModel->erasePreviousResults();
        return;
    }

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


    const auto& found_words = AlgorithmVersionWithIndices::find_words(grid);

    m_resultsModel->createResults(found_words);
}

void MainModule::showIndices(QString word)
{
    m_resultsModel->showWordIndices(word, m_gridModel->rows());
}
