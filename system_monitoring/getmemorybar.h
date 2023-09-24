#ifndef GET_MEMORY_BAR_H
#define GET_MEMORY_BAR_H

#include "getmemoryusage.h"
#include <QObject>
#include <QProgressBar>
#include <QTimer>

class Get_Memory_Bar : public GetMemoryUsage
{
    Q_OBJECT
public:
    explicit Get_Memory_Bar(QProgressBar *bar, QObject *parent = nullptr);

private slots:
    void updateMemoryUsage();
    void updateMemBar(int usage);  // Parametre ekleniyor
private:
    QProgressBar *memBar;
    QTimer *timer;
};

#endif // GET_MEMORY_BAR_H
