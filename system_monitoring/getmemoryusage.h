#ifndef GETMEMORYUSAGE_H
#define GETMEMORYUSAGE_H

#include <QObject>
#include <QProcess>
#include <QProgressBar>

class GetMemoryUsage : public QObject
{
    Q_OBJECT
public:
    explicit GetMemoryUsage( QObject *parent = nullptr);  // Değişiklik burada
    int retrieveMemoryUsage();

signals:
    void memoryUsageUpdated(int usage);

private:
    QProcess process;
};

#endif // GETMEMORYUSAGE_H
