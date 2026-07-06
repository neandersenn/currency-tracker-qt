#include "databasemanager.h"
#include <QApplication>
#include <QStyleOption>
#include <QPainter>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QStackedWidget>
#include <QFrame>
#include <QDateTime>
#include <QProgressBar>
#include <QTimer>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    databasemanager::instance().init();

    MainWindow window;

    window.resize(1200, 700);
    window.show();

    return app.exec();
}
