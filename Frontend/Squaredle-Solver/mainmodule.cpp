#include "mainmodule.h"

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
