#ifndef RESULTSMODEL_H
#define RESULTSMODEL_H

#include <QAbstractListModel>
#include <QStringListModel>
#include <map>
#include "../../Backend/Algorithm.hpp"

struct Words {
    int length;
    QStringList words;
};

class ResultsModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(int totalWordsCount READ totalWordsCount NOTIFY totalWordsCountChanged FINAL)
    Q_PROPERTY(QList<int> wordIndices READ wordIndices NOTIFY wordIndicesChanged FINAL)

public:
    enum {
        WordsRole = Qt::UserRole + 1,
        LengthRole,
        SectionCountRole
    };
    explicit ResultsModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    bool removeRows(int row, int count, const QModelIndex &parent) override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;


    void setResults(const QList<Words> &newResults);

    void createResults(const std::map<std::string,
                        AlgorithmVersionWithIndices::indices_t,
                        decltype(AlgorithmVersionWithIndices::compare_words)>& word_to_indices);

    QHash<int, QByteArray> roleNames() const override;

    QList<Words> results() const;

    int totalWordsCount() const;

    QList<int> wordIndices() const;

public slots:
    void showWordIndices(QString word, int rows);
    void erasePreviousResults();

signals:
    void totalWordsCountChanged();

    void wordIndicesChanged();

private:
    QList<Words> m_results;
    std::map<std::string,
             AlgorithmVersionWithIndices::indices_t,
             decltype(AlgorithmVersionWithIndices::compare_words)> word_to_indices;


    int m_totalWordsCount;
    QList<int> m_wordIndices;
};

#endif // RESULTSMODEL_H
