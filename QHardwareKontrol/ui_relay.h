/********************************************************************************
** Form generated from reading UI file 'relay.ui'
**
** Created: Fri Feb 17 17:52:42 2012
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RELAY_H
#define UI_RELAY_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Relay
{
public:

    void setupUi(QWidget *Relay)
    {
        if (Relay->objectName().isEmpty())
            Relay->setObjectName(QString::fromUtf8("Relay"));
        Relay->resize(400, 300);

        retranslateUi(Relay);

        QMetaObject::connectSlotsByName(Relay);
    } // setupUi

    void retranslateUi(QWidget *Relay)
    {
        Relay->setWindowTitle(QApplication::translate("Relay", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Relay: public Ui_Relay {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RELAY_H
