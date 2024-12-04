#ifndef MAINMODULE_H
#define MAINMODULE_H

#include "Source/Frontend/GridModel/gridmodel.h"
#include "Source/Frontend/ResultsModel/resultsmodel.h"
#include <QObject>
#include <QQmlEngine>

class MainModule : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(GridModel* gridModel READ gridModel WRITE setGridModel NOTIFY gridModelChanged FINAL)
    Q_PROPERTY(ResultsModel* resultsModel READ resultsModel WRITE setResultsModel NOTIFY resultsModelChanged FINAL)
public:
    explicit MainModule(QObject *parent = nullptr);

    GridModel *gridModel() const;
    void setGridModel(GridModel *newGridModel);

    ResultsModel *resultsModel() const;
    void setResultsModel(ResultsModel *newResultsModel);

public slots:
    void solve();

    void showIndices(QString word);

signals:
    void gridModelChanged();

    void resultsModelChanged();

private:
    GridModel *m_gridModel = nullptr;
    ResultsModel *m_resultsModel = nullptr;
};

#endif // MAINMODULE_H
