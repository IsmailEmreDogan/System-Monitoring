#include "get_cpu_usage_graph.h"
#include <QPainter>

CPU_Usage_Graph::CPU_Usage_Graph(QWidget *parent) : QWidget(parent) {}

void CPU_Usage_Graph::addValue(int value) {
    if(values.size() > maxValues) {
        values.pop_front();
    }
    values.push_back(value);
    update();
}

void CPU_Usage_Graph::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setBrush(Qt::NoBrush);
    painter.setPen(Qt::blue);

    if (values.empty()) return;

    float w = width() / (float)maxValues;
    for(int i = 1; i < values.size(); i++) {
        painter.drawLine(w * (i - 1), height() - values[i - 1] * height() / 100.0, w * i, height() - values[i] * height() / 100.0);
    }
}
