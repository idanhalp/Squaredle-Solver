#ifndef RESULTSMODEL_H
#define RESULTSMODEL_H

#include <QAbstractListModel>

class ResultsModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum {
        WordRole = Qt::UserRole + 1,
        LengthRole
    };
    explicit ResultsModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    bool removeRows(int row, int count, const QModelIndex &parent) override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QList<QString> results() const;
    void setResults(const QList<QString> &newResults);

    void createResults(std::vector<std::string>& found_words);

    QHash<int, QByteArray> roleNames() const override;

    //void

private:
    QList<QString> m_results;

    void addResultToList(std::string word);
    void erasePreviousResults();

};

#endif // RESULTSMODEL_H
