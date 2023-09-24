#include "getmemoryusage.h"

GetMemoryUsage::GetMemoryUsage( QObject *parent)
    : QObject(parent) // Yapıcıda QProgressBar'ı başlat
{

}

int GetMemoryUsage::retrieveMemoryUsage()
{
    QProcess process;
    process.start("bash", QStringList() << "-c" << "free | awk '/^Mem:/{print int(($2-$7)/$2 * 100)}'");
    process.waitForFinished();

    QByteArray output = process.readAllStandardOutput();
    int result = output.trimmed().toInt();
    emit memoryUsageUpdated(result);

    return result;
}
