#include "chartwidget.h"
#include "databasemanager.h"
#include <QDebug>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts>
#include <QtCharts/QDateTimeAxis>
#include <QVBoxLayout>

ChartWidget::ChartWidget(QWidget *parent) : QWidget(parent)
{
    setupUI();
    loadData("USD");
}

void ChartWidget::setupUI(){

    series = new QLineSeries();

    series->setName("Курс валюты");

    chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Изменение курса за неделю");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    axisX = new QValueAxis();
    axisX->setTitleText("Дни");
    axisX->setRange(0, 10);
    axisX->setTickCount(6);
    axisX->setLabelFormat("%d");


    axisY = new QValueAxis();
    axisY->setTitleText("Курс BYN/USD");
    axisY->setRange(0, 10);
    axisY->setTickCount(6);

    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    axisY->setLabelFormat("%.2f");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QPen pen = series->pen();
    pen.setColor("#15803d");
    series->setPen(pen);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(chartView);

}

void ChartWidget::loadData(const QString &currency) {
    QList<RateEntry> history = databasemanager::instance().getHistory(currency);

    if (history.isEmpty()) {
        return;
    }

    series->clear();

    double minRate = 990.0, maxRate = 0.0;

    for (int i = 0; i < history.size(); ++i) {
        double rate = history[i].rate;
        series->append(i, rate);
        if (rate < minRate) minRate = rate;
        if (rate > maxRate) maxRate = rate;
    }

    if (axisY) {
        axisY->setRange(minRate - 0.1, maxRate + 0.1);
    }

    if (axisX) {
        axisX->setRange(0, history.size());
    }

    chart->update();
}
