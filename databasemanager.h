#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QList>

struct RateEntry {
    QString currency;
    double rate;
    double input_amount;
    QString date;
};

class databasemanager : QObject
{
    Q_OBJECT
public:
    static databasemanager &instance();

    databasemanager();

    bool init();

    bool saveRates(const QString &currency, double input_amount, double rate);

    QList<RateEntry> getHistory(const QString &currency, int limit = 30);

private:
    QSqlDatabase db;

};

#endif // DATABASEMANAGER_H
