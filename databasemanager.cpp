#include "databasemanager.h"
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QList>
#include <QVariant>
#include <QDebug>
#include <QSqlError>

databasemanager::databasemanager()
{
    void init();

    void saveRates(const QString &currency, double rates);

    QList<RateEntry> getHistory(const QString &currency);
}

bool databasemanager::init(){
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("history.db");

    if(!db.open()){
        return false;
    }
    QString createTableQuery = R"(
        CREATE TABLE IF NOT EXISTS rates (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            currency TEXT NOT NULL,
            input_amount REAL NOT NULL,
            rate REAL NOT NULL,
            date TEXT DEFAULT CURRENT_TIMESTAMP
        )
    )";

    if (getHistory("USD").isEmpty()) {
        saveRates("USD", 1, 2.85);
        saveRates("USD", 1, 2.82);
        saveRates("USD", 1, 2.88);
        saveRates("USD", 1, 2.79);
        saveRates("USD", 1, 2.91);
        saveRates("USD", 1, 2.86);
        saveRates("USD", 1, 2.90);
    }

    QSqlQuery query;
    if(!query.exec(createTableQuery)){
        return false;
    };

    return true;
}

bool databasemanager::saveRates(const QString &currency, double input_amount, double rate){
    QList<RateEntry> history;
    if(!db.open()){
        return false;
    };

    QSqlQuery query(db);
    query.prepare("INSERT INTO rates (currency, input_amount, rate) VALUES (?, ?, ?)");
    query.addBindValue(QVariant(currency));
    query.addBindValue(QVariant(input_amount));
    query.addBindValue(QVariant(rate));

    if(!query.exec()){
        return false;
    };

    return true;
}

QList<RateEntry> databasemanager::getHistory(const QString &currency, int limit){

    QList<RateEntry> history;
    if(!db.open()){
        return history;
    };
    QSqlQuery query(db);
    query.prepare("SELECT input_amount,rate, date FROM rates WHERE currency = ? ORDER BY id DESC LIMIT 30");
    query.addBindValue(QVariant(currency));

    if(!query.exec()){
        return history;
    };

    while(query.next()){
         RateEntry entry;
         entry.currency = currency;
         entry.input_amount = query.value(0).toDouble();
         entry.rate = query.value(1).toDouble();
         entry.date = query.value(2).toString();
         history.append(entry);
    };

    qDebug() << "Загружено записей:" << history.size();
    return history;
}

databasemanager& databasemanager::instance() {
    static databasemanager manager;
    return manager;
}
