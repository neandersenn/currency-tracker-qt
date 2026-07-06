#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFrame>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    setupUI();
    setupConnections();
}

void MainWindow::setupUI() {
    setupLeftPanel();

    converterPage = new ConverterWidget(this);
    chartPage = new ChartWidget(this);

    stackedWidget = new QStackedWidget(this);
    stackedWidget->addWidget(converterPage);
    stackedWidget->addWidget(chartPage);

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(leftPanel);
    mainLayout->addWidget(stackedWidget);

    connect(menuList, &QListWidget::currentRowChanged,
            stackedWidget, &QStackedWidget::setCurrentIndex);
}

void MainWindow::setupLeftPanel() {
    leftPanel = new QWidget(this);
    leftPanel->setFixedWidth(320);
    leftPanel->setStyleSheet("background-color: #ffffff;");

    QVBoxLayout *leftLayout = new QVBoxLayout(leftPanel);
    leftLayout->setContentsMargins(0, 0, 0, 0);
    QLabel *taskLabel = new QLabel("Currency tracker", leftPanel);
    taskLabel->setStyleSheet("font-weight:bold; font-size:28px; color:#1a1a1a;");
    taskLabel->setAlignment(Qt::AlignCenter);

    menuList = new QListWidget(leftPanel);
    menuList->addItem("Converter");
    menuList->addItem("Chart");
    menuList->setCurrentRow(0);
    menuList->setStyleSheet(R"(
        QListWidget {
            background-color: #ffffff;
            border: none;
            font-size: 25px;
            font-weight: bold;
            color: #6b7280;
            padding: 25px;
            outline: none;
        }
        QListWidget::item {
            padding: 12px 16px;
            border-radius: 8px;
            margin: 2px 0px;
            color: #6b7280;
        }
        QListWidget::item:selected {
            background-color: #15803d;
            color: #ffffff;
        }
        QListWidget::item:hover:!selected {
            background-color: #e5e7eb;
            color: #111827;
        }
    )");

    QHBoxLayout *bottomLayout = new QHBoxLayout();
    QLabel *bottomQt = new QLabel("Qt", leftPanel);
    bottomQt->setStyleSheet("color:#6b7280; font-size:26px; font-weight:bold; padding-left:7px;");

    QPushButton *settingBtn = new QPushButton("⚙", leftPanel);
    settingBtn->setCursor(Qt::PointingHandCursor);
    settingBtn->setStyleSheet("font-size:40px; font-weight:bold;border:none;background: transparent;");
    settingBtn->setFixedSize(40, 40);

    bottomLayout->addWidget(bottomQt);
    bottomLayout->addWidget(settingBtn);
    bottomLayout->setContentsMargins(30, 0, 25, 0);

    QLabel *line = new QLabel("", leftPanel);
    line->setStyleSheet("border-bottom:2px solid #6b7280;");


    leftLayout->addSpacing(80);
    leftLayout->addWidget(taskLabel);
    leftLayout->addWidget(menuList);
    leftLayout->addStretch();
    leftLayout->addLayout(bottomLayout);
    leftLayout->addWidget(line);
}

void MainWindow::setupConnections(){
    connect(converterPage, &ConverterWidget::currencyConverted,
            chartPage, &ChartWidget::loadData);
}
