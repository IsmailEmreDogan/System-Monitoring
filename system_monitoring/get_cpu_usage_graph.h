#ifndef GET_CPU_USAGE_GRAPH_H
#define GET_CPU_USAGE_GRAPH_H

#include <QWidget>
#include <QList>
#include <QMainWindow>

class CPU_Usage_Graph : public QWidget {
    Q_OBJECT
public:
    explicit CPU_Usage_Graph(QWidget *parent = nullptr);
    void addValue(int value);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QList<int> values;
    const int maxValues = 60; // Son 60 değeri tutalım
};

#endif // GET_CPU_USAGE_GRAPH_H
