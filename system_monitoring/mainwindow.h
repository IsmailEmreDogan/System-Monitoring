#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "getcpuusage.h"
#include "getmemoryusage.h"
#include "getcpugraph.h"
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QProgressBar>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private:
    void updateBarColor(QProgressBar* specificBar, int usage);


};

#endif // MAINWINDOW_H
