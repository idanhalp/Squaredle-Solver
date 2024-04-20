#include "gridmodel.h"
#include "../../Backend/Algorithm.hpp"
#include "../../Backend/InputOutputProcessor.hpp"
#include "../../Backend/Parameters.hpp"
#include <QRegularExpression>

GridModel::GridModel(QObject *parent)
    : QAbstractListModel(parent),
    m_isNotValidInput(false)
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
    std::string regex = "[a-z";
    regex.append(&Parameters::EMPTY_CELL);
    regex.append("]");
    QRegularExpression re(QString::fromStdString(regex));
    if (re.match(c).hasMatch() || c == "")
    {
        m_grid[index] = c.toStdString()[0];
        m_isNotValidInput = false;
        emit isNotValidInputChanged();
    }
    else
    {
        m_isNotValidInput = true;
        emit isNotValidInputChanged();
    }
}

void GridModel::buildGrid(int rows, int columns)
{
    for (int i = 0; i < m_rows * m_columns; i++)
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
    std::vector<std::vector<char>> grid(m_rows, std::vector<char>(m_columns, ' '));
    int k = 0;

    for (int i = 0; i < m_rows; i++)
    {
        for (int j = 0; j < m_columns; j++)
        {
            grid[i][j] = m_grid[k];
            k++;
        }
    }

    std::vector<std::string> found_words = Algorithm::find_words(grid);
    InputOutputProcessor::process_output(found_words);
}

void GridModel::resizeGrid(int rows, int columns)
{
    m_isNotValidInput = false;
    emit isNotValidInputChanged();

    removeAllRows();
    setRows(rows);
    setColumns(columns);
    buildGrid(rows, columns);
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

bool GridModel::isNotValidInput() const
{
    return m_isNotValidInput;
}
