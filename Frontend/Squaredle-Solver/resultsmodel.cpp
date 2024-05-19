#include "resultsmodel.h"

ResultsModel::ResultsModel(QObject *parent)
    : QAbstractListModel(parent),
    m_totalWordsCount(0)
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

    Words result = m_results[index.row()];
    if (role == WordsRole)
    {
        return result.words;
    }
    else if (role == LengthRole)
    {
        return result.length;
    }
    else if (role == SectionCountRole)
    {
        return result.words.count();
    }
    return QVariant();
}

QList<Words> ResultsModel::results() const
{
    return m_results;
}

void ResultsModel::setResults(const QList<Words> &newResults)
{
    m_results = newResults;
}

void ResultsModel::createResults(const std::map<std::string,
                                AlgorithmVersionWithIndices::indices_t,
                                decltype(AlgorithmVersionWithIndices::compare_words)>& map)
{
    erasePreviousResults();

    word_to_indices = map;
    m_totalWordsCount = word_to_indices.size();
    emit totalWordsCountChanged();

    QStringList temp;
    size_t previous_word_length = word_to_indices.begin()->first.length();
    for (const auto& [word, indices] : word_to_indices)
    {
        if (word.length() != previous_word_length)
        {
            beginInsertRows(QModelIndex(), rowCount(), rowCount());
            m_results << Words{static_cast<int>(previous_word_length), temp};
            endInsertRows();
            temp.clear();
            previous_word_length = word.length();
        }
        temp << QString::fromStdString(word);
    }

    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_results << Words{static_cast<int>(previous_word_length), temp};
    endInsertRows();
    temp.clear();
}

QHash<int, QByteArray> ResultsModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[WordsRole] = "words";
    roles[LengthRole] = "length";
    roles[SectionCountRole] = "section_count";
    return roles;
}

void ResultsModel::erasePreviousResults()
{
    if (m_results.count() > 0)
    {
        m_totalWordsCount = 0;
        emit totalWordsCountChanged();

        removeRows(0, rowCount(), index(0,0));
    }
}

int ResultsModel::totalWordsCount() const
{
    return m_totalWordsCount;
}

QList<int> ResultsModel::wordIndices() const
{
    return m_wordIndices;
}

void ResultsModel::showWordIndices(QString word, int gridRows)
{
    m_wordIndices.clear();

    const auto& indices = word_to_indices[word.toStdString()];

    for (const auto [row, col] : indices)
    {
        m_wordIndices << (row * gridRows) + col;
    }

    emit wordIndicesChanged();
}
