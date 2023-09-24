#ifndef GETMEMORYGRAPH_H
#define GETMEMORYGRAPH_H

#include <QObject>
#include <QTimer>
#include <QValueAxis>
#include <QChartView>
#include <QChart>
#include <QLineSeries>
#include <QAreaSeries>
#include <QFrame>
#include "getmemoryusage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

class GetMemoryGraph : public QObject
{
    Q_OBJECT

public:
    explicit GetMemoryGraph(QFrame *frame_2, QObject *parent = nullptr);

private slots:
    void onMemoryUsageUpdated(int usage);
    void startMonitoring();

private:
    void initializeChart();
    void initializeAreaSeries();
    void setupAxis();
    QFrame* frame;

    QTimer *timer;
    QValueAxis *axisX;
    QValueAxis *axisY;
    QChartView *chartView;
    QChart *chart;
    QLineSeries *series;
    QAreaSeries *areaSeries;
    int timeCounter;
    GetMemoryUsage *memUsageInstance;
};

#endif // GETMEMORYGRAPH_H
