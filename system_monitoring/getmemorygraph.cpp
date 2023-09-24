#include "getmemorygraph.h"
#include "getmemoryusage.h"

GetMemoryGraph::GetMemoryGraph(QFrame *frame_2, QObject *parent)
    : QObject(parent), timeCounter(0), memUsageInstance(new GetMemoryUsage(this)),frame(frame_2)
{


    initializeChart();
    initializeAreaSeries();
    setupAxis();



    connect(memUsageInstance, &GetMemoryUsage::memoryUsageUpdated, this, &GetMemoryGraph::onMemoryUsageUpdated);
    startMonitoring();
}

void GetMemoryGraph::initializeChart() {
    series = new QLineSeries();
    chart = new QChart();
    chartView = new QChartView(chart);


    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    chartView->setAlignment(Qt::AlignLeft);

    QVBoxLayout *layout = new QVBoxLayout(frame);
    layout->addWidget(chartView);
    layout->setContentsMargins(0, 0, 0, 0);
    frame->setLayout(layout);

    chart->setTitle("Memory Usage Graph");
    chart->setTitleBrush(QColor(255, 255, 255));
    QFont titleFont = chart->titleFont();
    titleFont.setPointSize(15);
    chart->setTitleFont(titleFont);
    chart->legend()->setVisible(false);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->legend()->setLabelColor(QColor(255, 255, 255));
    chart->setMargins(QMargins(10, 10, 10, 10));  // Bu değerleri ihtiyacınıza göre ayarlayın.

    chart->setBackgroundBrush(QColor(31, 78, 47));
    chart->setPlotAreaBackgroundBrush(QColor(31, 78, 47));
    chart->setPlotAreaBackgroundVisible(true);
}


void GetMemoryGraph::initializeAreaSeries() {
    areaSeries = new QAreaSeries(series);
    series->setColor(QColor(0, 128, 0));
    series->setPen(QPen(series->color(), 2));
    series->setPointLabelsVisible(false);

    QLinearGradient gradient(QPointF(0, 0), QPointF(0, 1));
    gradient.setColorAt(0.0, series->color().lighter(120));
    gradient.setColorAt(1.0, series->color());
    gradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    areaSeries->setBrush(gradient);
    series->setPointsVisible(false); // Eğer bu QLineSeries için bir nokta varsa gizler.

    chart->addSeries(areaSeries);
}

void GetMemoryGraph::setupAxis() {
    axisX = new QValueAxis();
    axisY = new QValueAxis();

    axisX->setRange(0, 20);
    axisX->setTitleBrush(QColor(255, 255, 255));
    axisX->setLabelsColor(QColor(255, 255, 255));
    axisX->setLabelFormat("%d");

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

void GetMemoryGraph::startMonitoring() {
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, memUsageInstance, &GetMemoryUsage::retrieveMemoryUsage);
    timer->start(1000);
}

void GetMemoryGraph::onMemoryUsageUpdated(int usage) {
    series->append(timeCounter++, usage);
    if (timeCounter > 10) {
        axisX->setRange(timeCounter - 10, timeCounter);
    } else {
        axisX->setRange(0, 10);
    }
}

