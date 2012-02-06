#ifndef TINCREMENT_H
#define TINCREMENT_H

#include <QWidget>
#include <QtSql>
#include <QTime>
#include <QMessageBox>

namespace Ui {
    class Tincrement;
}

class Tincrement : public QWidget
{
    Q_OBJECT

public:
    explicit Tincrement(QWidget *parent = 0);
    explicit Tincrement(QWidget *parent, int id);
    ~Tincrement();

    QString check(QTime);
    void setTitle(QString);
    QStringList onTime;   //increment string is formated like: 5.0,3    5.0 is the double spin box ',' is the delim and 3 is the index for combo (switch)
    QStringList offTime;


signals:
    void update();

private slots:
    void on_updateBtn_clicked();
    void on_revertBtn_clicked();

private:
    Ui::Tincrement *ui;

    QVariant relayID;


    QTime nextOn;
    QTime nextOff;
    bool isOn;

    bool confirmChange();
    void cacheTimes();
    void calNextOn(QTime);
    void calNextOff(QTime);
};

#endif // TINCREMENT_H
