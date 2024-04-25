#ifndef RESULTSMODEL_H
#define RESULTSMODEL_H

#include <QAbstractListModel>
#include <QStringListModel>

struct Words {
    int length;
    QStringList words;
};

class ResultsModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(int totalWordsCount READ totalWordsCount NOTIFY totalWordsCountChanged FINAL)

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

    void createResults(std::vector<std::string>& found_words);

    QHash<int, QByteArray> roleNames() const override;

    QList<Words> results() const;

    int totalWordsCount() const;

signals:
    void totalWordsCountChanged();

private:
    QList<Words> m_results;

    void erasePreviousResults();

    int m_totalWordsCount;
};

#endif // RESULTSMODEL_H
