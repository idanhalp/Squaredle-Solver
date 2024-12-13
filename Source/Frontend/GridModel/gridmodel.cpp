#include "Source/Parameters.hpp"
#include "Source/Frontend/GridModel/gridmodel.h"

GridModel::GridModel(QObject *parent)
    : QAbstractListModel(parent),
    m_isValidInput(true)
{
    setRows(4);
    setColumns(4);
    buildGrid(m_rows, m_columns);
    setEmptyCellChar(Parameters::EMPTY_CELL);
}

int GridModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_grid.count();
}

bool GridModel::removeRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent);

    beginRemoveRows(QModelIndex(), row, row + count - 1);
    m_grid.clear();
    endRemoveRows();
    return true;
}


QVariant GridModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_grid.count())
    {
        return QVariant();
    }

    char letter = m_grid[index.row()];

    if (role == LetterRole)
    {
        return QChar(letter);
    }

    return QVariant();
}

QHash<int, QByteArray> GridModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[LetterRole] = "letter";
    return roles;
}

void GridModel::updateGrid(QString c, int index)
{
    m_grid[index] = c.toStdString()[0];
}

void GridModel::buildGrid(int rows, int columns)
{
    Q_UNUSED(rows);
    Q_UNUSED(columns);

    for (int i = 0; i < m_rows * m_columns; i++)
    {
        addCell();
        m_validIndices << true;
    }

    emit validIndicesChanged();
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

void GridModel::resizeGrid(int rows, int columns)
{
    setRows(rows);
    setColumns(columns);
    clearGrid();
}

void GridModel::clearGrid()
{
    m_isValidInput = true;
    emit isValidInputChanged();

    removeAllRows();
    m_validIndices.clear();
    buildGrid(m_rows, m_columns);
}

void GridModel::fillGrid(const QList<QString>& tPuzzle)
{
    if (tPuzzle.length() != m_rows)
    {
        resizeGrid(tPuzzle.length(), tPuzzle.length());
    }

    int k = 0;
    for (int i = 0; i < tPuzzle.length(); i++)
    {
        for (int j = 0; j < tPuzzle[i].length(); j++)
        {
            if (tPuzzle[i][j] == ' ')
            {
                updateGrid("-", k);
            }
            else
            {
                updateGrid(tPuzzle[i][j], k);
            }
            emit dataChanged(index(k, 0), index(k, 0), {LetterRole});
            k++;
        }
    }
}

void GridModel::resetAllErrors()
{
    m_isValidInput = true;
    emit isValidInputChanged();

    m_validIndices.clear();
    m_validIndices.fill(true, m_rows * m_columns);
    emit validIndicesChanged();
}

int GridModel::rows() const
{
    return m_rows;
}

void GridModel::setRows(int newRows)
{
    if (m_rows == newRows)
        return;
    m_rows = newRows;
    emit rowsChanged();
}

int GridModel::columns() const
{
    return m_columns;
}

void GridModel::setColumns(int newColumns)
{
    if (m_columns == newColumns)
        return;
    m_columns = newColumns;
    emit columnsChanged();
}

QChar GridModel::emptyCellChar() const
{
    return m_emptyCellChar;
}

void GridModel::setEmptyCellChar(QChar newEmptyCellChar)
{
    if (m_emptyCellChar == newEmptyCellChar)
        return;
    m_emptyCellChar = newEmptyCellChar;
    emit emptyCellCharChanged();
}

bool GridModel::isValidInput() const
{
    return m_isValidInput;
}

QList<char> GridModel::getGrid()
{
    return m_grid;
}

bool GridModel::isGridValid()
{
    for (int i = 0; i < m_grid.count(); i++)
    {
        if (m_grid[i] == ' ' || static_cast<int>(m_grid[i]) == 0)
        {
            m_isValidInput = false;
            emit isValidInputChanged();

            m_validIndices[i] = false;
            emit validIndicesChanged();
        }
        else
        {
            m_validIndices[i] = true;
            emit validIndicesChanged();
        }
    }

    if (!m_isValidInput)
    {
        return false;
    }

    m_isValidInput = true;
    emit isValidInputChanged();

    return true;
}

QList<bool> GridModel::validIndices() const
{
    return m_validIndices;
}
