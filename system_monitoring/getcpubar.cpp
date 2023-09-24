#include "getcpubar.h"
#include "getcpuusage.h"

Get_Cpu_Bar::Get_Cpu_Bar(QProgressBar *bar, QObject *parent) : Get_CPU_Usage(parent), cpuBar(bar)
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Get_Cpu_Bar::updateCPUUsage);
    connect(this, &Get_CPU_Usage::cpuUsageUpdated, cpuBar, &QProgressBar::setValue); // Connect signal to slot
    timer->start(100);
}

void Get_Cpu_Bar::updateCPUUsage()
{
    int usage = retrieveCPUsage();
    updateCPUBar(usage);
}

void Get_Cpu_Bar::updateCPUBar(int usage) {
    // Calculate color values
    int redValue, greenValue;
    if (usage < 10) {
        redValue = 0;
        greenValue = 255;
    } else if (usage < 25) {
        redValue = (usage - 10) * 17;
        greenValue = 255;
    } else if (usage < 45) {
        redValue = 255;
        greenValue = 255 - ((usage - 25) * 10.2);
    } else if (usage < 60) {
        redValue = 255;
        greenValue = 204 - ((usage - 45) * 13.6);
    } else if (usage < 75) {
        redValue = 255;
        greenValue = 102 - ((usage - 60) * 6.8);
    } else {
        redValue = 255;
        greenValue = 0;
    }

    QString style = QString("QProgressBar {"
                            "border: 2px solid grey;"
                            "border-radius: 5px;"
                            "background-color: #E0E0E0;"
                            "text-align: center;"
                            "}"
                            "QProgressBar::chunk {"
                            "background-color: rgb(%1, %2, 0);"
                            "width: 5px;"
                            "margin: 0.5px;"
                            "}").arg(redValue).arg(greenValue);

    cpuBar->setStyleSheet(style);
    cpuBar->setValue(usage);
}
