#ifndef TRACKER_H
#define TRACKER_H

#include <QWidget>
#include <QtGui>
#include <QtSql>
#include "entry.h"

namespace Ui {
    class Tracker;
}

class Tracker : public QWidget
{
    Q_OBJECT

public:
    explicit Tracker(QWidget *parent = 0);
    ~Tracker();

public slots:
    void addEntry();
    void editEntry();
    void removeEntry();
    void selectEntry(QModelIndex);
    void updateView();

private:
    Ui::Tracker *ui;
    bool dbInsert(QList<QVariant>);
    bool dbUpdate(QList<QVariant>,QVariant);

};

#endif // TRACKER_H
