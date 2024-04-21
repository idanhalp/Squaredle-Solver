#ifndef RESULTSMODEL_H
#define RESULTSMODEL_H

#include <QAbstractListModel>

class ResultsModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit ResultsModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section,
                        Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
};

#endif // RESULTSMODEL_H
