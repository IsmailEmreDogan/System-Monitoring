#include "getcpuusage.h"

Get_CPU_Usage::Get_CPU_Usage(QObject *parent)
    : QObject(parent)
{

}

int Get_CPU_Usage::retrieveCPUsage()
{
    QProcess process;
    process.start("bash", QStringList() << "-c" << "vmstat 1 2 | tail -n 1 | awk '{print 100 - $15}'");
    process.waitForFinished();
    QString output = process.readAllStandardOutput();
    int result = output.trimmed().toInt();
    emit cpuUsageUpdated(result);
    return result;
}
