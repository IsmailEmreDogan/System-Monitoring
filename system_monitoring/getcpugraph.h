#ifndef GET_CPU_GRAPH_H
#define GET_CPU_GRAPH_H

#include <QObject>
#include <QTimer>
#include <QFrame>
#include <QtCharts/QChart>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChartView>
#include "getcpuusage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

    class GetCPUGraph : public Get_CPU_Usage
{
    Q_OBJECT

public:
    explicit GetCPUGraph(QFrame *frame, QObject *parent = nullptr);

private slots:
    void updateGraph();

private:
    QChart *chart;
    QChartView *chartView;
    QLineSeries *series;
    QAreaSeries *areaSeries;
    QValueAxis *axisX;
    QValueAxis *axisY;
    QTimer *timer;
    int timeCounter;
    QFrame* frame;
    void initializeChart();
    void initializeAreaSeries();
    void setupAxis();
    void startMonitoring();
};

#endif // GET_CPU_GRAPH_H
