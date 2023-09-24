#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "getmemoryusage.h"
#include "getcpuusage.h"
#include <QtCharts/QLineSeries>
#include <QValueAxis>
#include <QtCharts/QChartView>
#include "getcpugraph.h"
#include "getmemorygraph.h"
#include "getmemorybar.h"
#include "getcpubar.h"
#include <QTimer> // Bu satırı ekleyin.
#include <QVBoxLayout>
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->gridFrame->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    ui->gridFrame_2->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    ui->cpuBar->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    ui->memBar->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);


//  Metodları elementlere ekleme
    new Get_Memory_Bar(ui->memBar, this);
    new Get_Cpu_Bar(ui->cpuBar,this);
    new GetCPUGraph(ui->gridFrame,this);
    new GetMemoryGraph(ui->gridFrame_2,this);

  // Layout ayarlamaları

    QWidget *centralWidget = new QWidget(this);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    QHBoxLayout *topLayout = new QHBoxLayout();

    topLayout->addWidget(ui->gridFrame);
    topLayout->addWidget(ui->gridFrame_2);


    QHBoxLayout *middleLayout = new QHBoxLayout();


    QHBoxLayout *bottomLayout = new QHBoxLayout();

    bottomLayout->addWidget(ui->cpuBar);
    bottomLayout->addWidget(ui->memBar);



    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(middleLayout);
    mainLayout->addLayout(bottomLayout);

    centralWidget->setLayout(mainLayout);

    setCentralWidget(centralWidget);



}

MainWindow::~MainWindow() {
    delete ui;
}














