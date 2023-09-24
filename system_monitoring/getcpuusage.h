#ifndef GETCPUUSAGE_H
#define GETCPUUSAGE_H

#include <QObject>
#include <QProcess>

class Get_CPU_Usage : public QObject
{
    Q_OBJECT

public:
    explicit Get_CPU_Usage(QObject *parent = nullptr);
    int retrieveCPUsage();

signals:
    void cpuUsageUpdated(int usage);
};

#endif // GETCPUUSAGE_H
