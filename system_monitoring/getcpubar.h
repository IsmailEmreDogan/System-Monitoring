#ifndef GETCPUBAR_H
#define GETCPUBAR_H

#include "getcpuusage.h"
#include <QProgressBar>
#include <QTimer>

class Get_Cpu_Bar : public Get_CPU_Usage
{
    Q_OBJECT

public:
    Get_Cpu_Bar(QProgressBar *cpuBar, QObject *parent = nullptr);

private slots:
    void updateCPUUsage();  // Parametresiz olarak tanımlayalım
    void updateCPUBar(int usage);  // Bu fonksiyonu private slot yapalım
private:
    QProgressBar *cpuProgressBar;
    QTimer *timer;
    QProgressBar *cpuBar;
};

#endif // GETCPUBAR_H
