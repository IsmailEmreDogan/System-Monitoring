#ifndef GRAPH_H
#define GRAPH_H


class graph: public QWidget
{
    Q_OBJECT

public:
    explicit graph(QWidget *parent = nullptr);
    void addValue(float value);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QVector<float> data;
    const int maxDataSize = 100;
};

#endif // GRAPH_H
