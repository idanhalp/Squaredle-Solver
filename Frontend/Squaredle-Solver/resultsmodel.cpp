#include "resultsmodel.h"

ResultsModel::ResultsModel(QObject *parent)
    : QAbstractListModel(parent)
{}

int ResultsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_results.count();
}

bool ResultsModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(QModelIndex(), row, row + count - 1);
    m_results.clear();
    endRemoveRows();
    return true;
}

QVariant ResultsModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_results.count())
    {
        return QVariant();
    }

    const QString word = m_results[index.row()];
    if (role == WordRole)
    {
        return word;
    }
    else if (role == LengthRole)
    {
        return word.length();
    }

    return QVariant();
}

QList<QString> ResultsModel::results() const
{
    return m_results;
}

void ResultsModel::setResults(const QList<QString> &newResults)
{
    m_results = newResults;
}

void ResultsModel::createResults(std::vector<std::string> &found_words)
{
    if (m_results.count() > 0)
    {
        erasePreviousResults();
    }

    for (int i = 0; i < found_words.size(); i++)
    {
        addResultToList(found_words[i]);
    }
}

QHash<int, QByteArray> ResultsModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[WordRole] = "word";
    roles[LengthRole] = "length";
    return roles;
}

void ResultsModel::addResultToList(std::string word)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_results << QString::fromStdString(word);
    endInsertRows();
}

void ResultsModel::erasePreviousResults()
{
    removeRows(0, rowCount(), index(0,0));
}
