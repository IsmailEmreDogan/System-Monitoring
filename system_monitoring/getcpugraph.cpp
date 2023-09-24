#include "getcpugraph.h"


GetCPUGraph::GetCPUGraph(QFrame *frame, QObject *parent)
    : Get_CPU_Usage(parent), timeCounter(0),frame(frame) {
    if(!frame) {
        return;
    }

    initializeChart();
    initializeAreaSeries();
    setupAxis();
    startMonitoring();
}

void GetCPUGraph::initializeChart() {
    series = new QLineSeries();
    chart = new QChart();
    chartView = new QChartView(chart);
    chart->setTitle("CPU Usage Graph");
    chart->setTitleBrush(QColor(255, 255, 255));
    QFont titleFont = chart->titleFont();
    titleFont.setPointSize(15);
    chart->setTitleFont(titleFont);
    chart->legend()->setVisible(false);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->legend()->setLabelColor(QColor(255, 255, 255));
    chartView->setRenderHint(QPainter::Antialiasing);
    chart->setMargins(QMargins(10, 10, 10, 10));

    chartView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    chartView->setAlignment(Qt::AlignRight);

    chart->setBackgroundBrush(QColor(31, 78, 47));
    chart->setPlotAreaBackgroundBrush(QColor(31, 78, 47));
    chart->setPlotAreaBackgroundVisible(true);

    QVBoxLayout *layout = new QVBoxLayout(frame);
    layout->addWidget(chartView);
    layout->setContentsMargins(0, 0, 0, 0);
    frame->setLayout(layout);

    frame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}



void GetCPUGraph::initializeAreaSeries() {
    areaSeries = new QAreaSeries(series);
    series->setColor(QColor(0, 150, 0));
    series->setPen(QPen(series->color(), 2));
    series->setPointLabelsVisible(false);

    QLinearGradient gradient(QPointF(0, 0), QPointF(0, 1));
    gradient.setColorAt(0.0, series->color().lighter(120));
    gradient.setColorAt(1.0, series->color());
    gradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    areaSeries->setBrush(gradient);
    chart->addSeries(areaSeries);
}

void GetCPUGraph::setupAxis() {
    axisX = new QValueAxis();
    axisY = new QValueAxis();

    axisX->setRange(0, 20);
    axisX->setLabelFormat("%d");

    axisX->setTitleBrush(QColor(255, 255, 255));
    axisX->setLabelsColor(QColor(255, 255, 255));
    chart->addAxis(axisX, Qt::AlignBottom);

    axisY->setRange(0, 100);
    axisY->setTickCount(7);
    axisY->setLabelFormat("%d");
    QFont labelFont = axisY->titleFont();
    labelFont.setPointSize(labelFont.pointSize() + 5);
    axisY->setTitleFont(labelFont);
    axisY->setTitleBrush(QColor(255, 255, 255));
    axisY->setLabelsColor(QColor(255, 255, 255));
    chart->addAxis(axisY, Qt::AlignLeft);

    areaSeries->attachAxis(axisX);
    areaSeries->attachAxis(axisY);
}

void GetCPUGraph::startMonitoring() {
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GetCPUGraph::updateGraph);
    timer->start(1000); // 1 second intervals to refresh CPU usage data
}

void GetCPUGraph::updateGraph() {
    int cpuUsage = retrieveCPUsage();
    series->append(timeCounter++, cpuUsage);
    if (timeCounter > 10) {
        axisX->setRange(timeCounter - 10, timeCounter);
    } else {
        axisX->setRange(0, 10);
    }
}
