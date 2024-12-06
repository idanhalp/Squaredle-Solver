#ifndef GRIDMODEL_H
#define GRIDMODEL_H

#include <QAbstractListModel>

class GridModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(int rows READ rows WRITE setRows NOTIFY rowsChanged FINAL)
    Q_PROPERTY(int columns READ columns WRITE setColumns NOTIFY columnsChanged FINAL)
    Q_PROPERTY(QChar emptyCellChar READ emptyCellChar WRITE setEmptyCellChar NOTIFY emptyCellCharChanged FINAL)
    Q_PROPERTY(bool isValidInput READ isValidInput NOTIFY isValidInputChanged FINAL)
    Q_PROPERTY(QList<bool> validIndices READ validIndices NOTIFY validIndicesChanged FINAL)

public:
    enum GridRoles{
        LetterRole = Qt::UserRole + 1
    };
    explicit GridModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    bool removeRows(int row, int count, const QModelIndex &parent) override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    int rows() const;
    void setRows(int newRows);

    int columns() const;
    void setColumns(int newColumns);

    QChar emptyCellChar() const;
    void setEmptyCellChar(QChar newEmptyCellChar);

    bool isValidInput() const;

    QList<char> getGrid();

    bool isGridValid();

    QList<bool> validIndices() const;

public slots:
    void updateGrid(QString c, int index);
    void resizeGrid(int rows, int columns);
    void clearGrid();
    void fillGrid(const QList<QString>& tPuzzle);
    void resetAllErrors();

signals:
    void rowsChanged();

    void columnsChanged();

    void emptyCellCharChanged();

    void isValidInputChanged();

    void validIndicesChanged();

private:
    QList<char> m_grid;

    void buildGrid(int rows, int columns);
    void addCell();
    void removeAllRows();

    int m_rows;
    int m_columns;
    QChar m_emptyCellChar;
    bool m_isValidInput;

    QList<bool> m_validIndices;
};

#endif // GRIDMODEL_H
