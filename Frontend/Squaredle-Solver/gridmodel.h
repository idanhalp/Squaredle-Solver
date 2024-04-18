#ifndef GRIDMODEL_H
#define GRIDMODEL_H

#include <QAbstractListModel>

class GridModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum GridRoles{
        Role = Qt::UserRole + 1
    };
    explicit GridModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    bool removeRows(int row, int count, const QModelIndex &parent) override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    QList<char> m_grid;
    int m_size;

    void buildGrid(int size);
    void addCell();
    void removeAllRows();

};

#endif // GRIDMODEL_H
