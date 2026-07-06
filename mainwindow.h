#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QListWidget>
#include <QStackedWidget>

#include "converterwidget.h"
#include "chartwidget.h"

class MainWindow : public QWidget {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    void setupUI();
    void setupLeftPanel();
    void setupConnections();

    QWidget *leftPanel;
    QListWidget *menuList;
    QStackedWidget *stackedWidget;

    ConverterWidget *converterPage;
    ChartWidget *chartPage;
};

#endif // MAINWINDOW_H
