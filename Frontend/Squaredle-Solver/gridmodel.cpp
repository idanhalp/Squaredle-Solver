#include "gridmodel.h"
#include "../../Backend/Algorithm.hpp"
#include "../../Backend/InputOutputProcessor.hpp"

GridModel::GridModel(QObject *parent)
    : QAbstractListModel(parent),
    m_size(16)
{
    buildGrid(m_size);
}

int GridModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_grid.count();
}

bool GridModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(QModelIndex(), row, row + count - 1);
    m_grid.clear();
    endRemoveRows();
    return true;
}


QVariant GridModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}

void GridModel::updateGrid(QString c, int index)
{
    m_grid[index] = c.toStdString()[0];
}

void GridModel::buildGrid(int size)
{
    for (int i = 0; i < size; i++)
    {
        addCell();
    }
}

void GridModel::addCell()
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_grid << ' ';
    endInsertRows();
}

void GridModel::removeAllRows()
{
    removeRows(0, rowCount(), index(0,0));
}

void GridModel::solve()
{
    std::vector<std::vector<char>> grid(4, std::vector<char>(4, ' '));
    int k = 0;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            grid[i][j] = m_grid[k];
            k++;
        }
    }

    std::vector<std::string> found_words = Algorithm::find_words(grid);
    InputOutputProcessor::process_output(found_words);
}
