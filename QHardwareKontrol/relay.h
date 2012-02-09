#ifndef RELAY_H
#define RELAY_H

#include <QWidget>
#include <QtGui>

//namespace Ui {
//    class Relay;
//}

class Relay : public QWidget
{
    Q_OBJECT

public:
    explicit Relay(QWidget *parent = 0);
    ~Relay();

    virtual QString check()        = 0;
    virtual QString check(QTime)   = 0;
    virtual void setTitle(QString) = 0;

signals:
    void update();

private:
  //  Ui::Relay *ui;

    QVariant relayID;
};

#endif // RELAY_H
