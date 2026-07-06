#ifndef CHARTWIDGET_H
#define CHARTWIDGET_H
#include <QtCharts>
#include <QWidget>
#include <QLabel>

class ChartWidget : public QWidget {
    Q_OBJECT
public:
    explicit ChartWidget(QWidget *parent = nullptr);

    void loadData(const QString &currency);

private:
    void setupUI();

    QChart *chart;
    QLineSeries *series;
    QValueAxis *axisX;
    QValueAxis *axisY;

};

#endif // CHARTWIDGET_H
