#ifndef GRIDMODEL_H
#define GRIDMODEL_H

#include <QAbstractListModel>

class GridModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(int rows READ rows WRITE setRows NOTIFY rowsChanged FINAL)
    Q_PROPERTY(int columns READ columns WRITE setColumns NOTIFY columnsChanged FINAL)
    Q_PROPERTY(QChar emptyCellChar READ emptyCellChar WRITE setEmptyCellChar NOTIFY emptyCellCharChanged FINAL)
    Q_PROPERTY(bool isNotValidInput READ isNotValidInput NOTIFY isNotValidInputChanged FINAL)

public:
    enum GridRoles{
        Role = Qt::UserRole + 1
    };
    explicit GridModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    bool removeRows(int row, int count, const QModelIndex &parent) override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    int rows() const;
    void setRows(int newRows);

    int columns() const;
    void setColumns(int newColumns);

    QChar emptyCellChar() const;
    void setEmptyCellChar(QChar newEmptyCellChar);

    bool isNotValidInput() const;

    QList<char> getGrid();

public slots:
    void updateGrid(QString c, int index);
    void resizeGrid(int rows, int columns);

signals:
    void rowsChanged();

    void columnsChanged();

    void emptyCellCharChanged();

    void isNotValidInputChanged();

private:
    QList<char> m_grid;

    void buildGrid(int rows, int columns);
    void addCell();
    void removeAllRows();

    int m_rows;
    int m_columns;
    QChar m_emptyCellChar;
    bool m_isNotValidInput;
};

#endif // GRIDMODEL_H
