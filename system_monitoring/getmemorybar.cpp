#include "getmemorybar.h"
#include "getmemoryusage.h"

Get_Memory_Bar::Get_Memory_Bar(QProgressBar *bar, QObject *parent) : GetMemoryUsage(parent), memBar(bar)
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Get_Memory_Bar::updateMemoryUsage);
    connect(this, &GetMemoryUsage::memoryUsageUpdated, memBar, &QProgressBar::setValue); // Sinyali yakala
    timer->start(100);
}

void Get_Memory_Bar::updateMemoryUsage()
{
    int usage = retrieveMemoryUsage();
    updateMemBar(usage);
}

void Get_Memory_Bar::updateMemBar(int usage) {
    // Renk değerlerini hesapla
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

    memBar->setStyleSheet(style);
    memBar->setValue(usage);
    // Zaten yapılandırıcıda zamanlayıcı başlatıldığı için burada başka bir QTimer kurulumuna gerek yok
}
