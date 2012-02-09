#ifndef ENTRY_H
#define ENTRY_H

#include <QDialog>
#include <QtGui>
#include <QImageReader>
#include <QtSql>


namespace Ui {
    class Entry;
}

class Entry : public QDialog
{
    Q_OBJECT

public:
    explicit Entry(QWidget *parent = 0);
    ~Entry();

public slots:
    QList<QVariant> getAmts();
    void setAmts(QList<QVariant>);
    void setImg();
    void getImg();

private:
    Ui::Entry *ui;
    QCalendarWidget *startDateCal;
};

#endif // ENTRY_H
