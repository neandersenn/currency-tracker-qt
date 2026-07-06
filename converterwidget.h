#ifndef CONVERTERWIDGET_H
#define CONVERTERWIDGET_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QMap>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>

class ConverterWidget : public QWidget {
    Q_OBJECT
public:
    explicit ConverterWidget(QWidget *parent = nullptr);

signals:
    void currencyConverted(const QString &currency);


private:
    void setupConnections();
    void setupUI();
    void fetchRates();
    void convert();

    QLabel *title;
    QLineEdit *amount;
    QComboBox *fromCombo;
    QComboBox *toCombo;
    QPushButton *convertBtn;
    QPushButton *refreshBtn;
    QLabel *resultLabel;
    QPushButton *swapBtn;

    QNetworkAccessManager *manager;
    QMap<QString, double> rates;
};

#endif // CONVERTERWIDGET_H
