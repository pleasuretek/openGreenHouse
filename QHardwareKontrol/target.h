/*
QHardwareKontrol is part of the openGreenHouse package of software sources

Written by: Travis McCann
Copywrite GPL 2010-2012

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef TARGET_H
#define TARGET_H

#include <QWidget>
#include <QtSql>
#include <QMessageBox>


namespace Ui {
    class Target;
}

class Target : public QWidget
{
    Q_OBJECT

public:
    explicit Target(QWidget *parent = 0);
    explicit Target(QWidget *parent, int id, int md);
    ~Target();

    void setTitle(QString);
    void setLabel(QString);
    QString check();

signals:
    void updateTargetSignal();

private slots:
    void on_updateBtn_clicked();
    void cacheTarget();

private:
    Ui::Target *ui;

    QVariant relayID;
    QVariant mode;

    float target, val, pval;

    bool confirmChange();

};

#endif // TARGET_H
