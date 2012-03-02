/********************************************************************************
** Form generated from reading UI file 'timer.ui'
**
** Created: Fri Feb 17 17:52:42 2012
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TIMER_H
#define UI_TIMER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFormLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QTimeEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Timer
{
public:
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QTimeEdit *onTmeSpinBox;
    QLabel *label_2;
    QTimeEdit *offTmeSpinBox;
    QHBoxLayout *horizontalLayout;
    QPushButton *updateBtn;
    QPushButton *revertBtn;

    void setupUi(QWidget *Timer)
    {
        if (Timer->objectName().isEmpty())
            Timer->setObjectName(QString::fromUtf8("Timer"));
        Timer->resize(225, 157);
        Timer->setMinimumSize(QSize(150, 100));
        verticalLayout_2 = new QVBoxLayout(Timer);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox = new QGroupBox(Timer);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        onTmeSpinBox = new QTimeEdit(groupBox);
        onTmeSpinBox->setObjectName(QString::fromUtf8("onTmeSpinBox"));

        formLayout->setWidget(0, QFormLayout::FieldRole, onTmeSpinBox);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        offTmeSpinBox = new QTimeEdit(groupBox);
        offTmeSpinBox->setObjectName(QString::fromUtf8("offTmeSpinBox"));

        formLayout->setWidget(1, QFormLayout::FieldRole, offTmeSpinBox);


        verticalLayout->addLayout(formLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        updateBtn = new QPushButton(groupBox);
        updateBtn->setObjectName(QString::fromUtf8("updateBtn"));

        horizontalLayout->addWidget(updateBtn);

        revertBtn = new QPushButton(groupBox);
        revertBtn->setObjectName(QString::fromUtf8("revertBtn"));

        horizontalLayout->addWidget(revertBtn);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addWidget(groupBox);


        retranslateUi(Timer);

        QMetaObject::connectSlotsByName(Timer);
    } // setupUi

    void retranslateUi(QWidget *Timer)
    {
        Timer->setWindowTitle(QApplication::translate("Timer", "Form", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("Timer", "GroupBox", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Timer", "Time On", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Timer", "Time Off", 0, QApplication::UnicodeUTF8));
        updateBtn->setText(QApplication::translate("Timer", "update times", 0, QApplication::UnicodeUTF8));
        revertBtn->setText(QApplication::translate("Timer", "revert times", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Timer: public Ui_Timer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIMER_H
