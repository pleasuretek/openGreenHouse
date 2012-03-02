/********************************************************************************
** Form generated from reading UI file 'tracker.ui'
**
** Created: Fri Feb 17 17:52:42 2012
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRACKER_H
#define UI_TRACKER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QTableView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Tracker
{
public:
    QVBoxLayout *verticalLayout;
    QTableView *tableView;
    QHBoxLayout *horizontalLayout;
    QPushButton *addBtn;
    QPushButton *editBtn;
    QPushButton *removeBtn;

    void setupUi(QWidget *Tracker)
    {
        if (Tracker->objectName().isEmpty())
            Tracker->setObjectName(QString::fromUtf8("Tracker"));
        Tracker->resize(400, 300);
        verticalLayout = new QVBoxLayout(Tracker);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tableView = new QTableView(Tracker);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        verticalLayout->addWidget(tableView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        addBtn = new QPushButton(Tracker);
        addBtn->setObjectName(QString::fromUtf8("addBtn"));

        horizontalLayout->addWidget(addBtn);

        editBtn = new QPushButton(Tracker);
        editBtn->setObjectName(QString::fromUtf8("editBtn"));

        horizontalLayout->addWidget(editBtn);

        removeBtn = new QPushButton(Tracker);
        removeBtn->setObjectName(QString::fromUtf8("removeBtn"));

        horizontalLayout->addWidget(removeBtn);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(Tracker);

        QMetaObject::connectSlotsByName(Tracker);
    } // setupUi

    void retranslateUi(QWidget *Tracker)
    {
        Tracker->setWindowTitle(QApplication::translate("Tracker", "Form", 0, QApplication::UnicodeUTF8));
        addBtn->setText(QApplication::translate("Tracker", "add", 0, QApplication::UnicodeUTF8));
        editBtn->setText(QApplication::translate("Tracker", "edit", 0, QApplication::UnicodeUTF8));
        removeBtn->setText(QApplication::translate("Tracker", "remove", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Tracker: public Ui_Tracker {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRACKER_H
