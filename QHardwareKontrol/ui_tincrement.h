/********************************************************************************
** Form generated from reading UI file 'tincrement.ui'
**
** Created: Fri Feb 17 17:52:42 2012
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TINCREMENT_H
#define UI_TINCREMENT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QFormLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Tincrement
{
public:
    QVBoxLayout *verticalLayout_2;
    QGroupBox *timerLabel;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_2;
    QSpinBox *spinBox;
    QComboBox *comboBox;
    QHBoxLayout *horizontalLayout_3;
    QSpinBox *spinBox_2;
    QComboBox *comboBox_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *updateBtn;
    QPushButton *revertBtn;

    void setupUi(QWidget *Tincrement)
    {
        if (Tincrement->objectName().isEmpty())
            Tincrement->setObjectName(QString::fromUtf8("Tincrement"));
        Tincrement->resize(271, 212);
        verticalLayout_2 = new QVBoxLayout(Tincrement);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        timerLabel = new QGroupBox(Tincrement);
        timerLabel->setObjectName(QString::fromUtf8("timerLabel"));
        verticalLayout = new QVBoxLayout(timerLabel);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(timerLabel);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        label_2 = new QLabel(timerLabel);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        spinBox = new QSpinBox(timerLabel);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));

        horizontalLayout_2->addWidget(spinBox);

        comboBox = new QComboBox(timerLabel);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        horizontalLayout_2->addWidget(comboBox);


        formLayout->setLayout(0, QFormLayout::FieldRole, horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        spinBox_2 = new QSpinBox(timerLabel);
        spinBox_2->setObjectName(QString::fromUtf8("spinBox_2"));

        horizontalLayout_3->addWidget(spinBox_2);

        comboBox_2 = new QComboBox(timerLabel);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));

        horizontalLayout_3->addWidget(comboBox_2);


        formLayout->setLayout(1, QFormLayout::FieldRole, horizontalLayout_3);


        verticalLayout->addLayout(formLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        updateBtn = new QPushButton(timerLabel);
        updateBtn->setObjectName(QString::fromUtf8("updateBtn"));

        horizontalLayout->addWidget(updateBtn);

        revertBtn = new QPushButton(timerLabel);
        revertBtn->setObjectName(QString::fromUtf8("revertBtn"));

        horizontalLayout->addWidget(revertBtn);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addWidget(timerLabel);


        retranslateUi(Tincrement);

        QMetaObject::connectSlotsByName(Tincrement);
    } // setupUi

    void retranslateUi(QWidget *Tincrement)
    {
        Tincrement->setWindowTitle(QApplication::translate("Tincrement", "Form", 0, QApplication::UnicodeUTF8));
        timerLabel->setTitle(QApplication::translate("Tincrement", "Tincrement", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Tincrement", "Time On", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Tincrement", "Time Off", 0, QApplication::UnicodeUTF8));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("Tincrement", "Seconds", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Tincrement", "Minutes", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Tincrement", "Hours", 0, QApplication::UnicodeUTF8)
        );
        comboBox_2->clear();
        comboBox_2->insertItems(0, QStringList()
         << QApplication::translate("Tincrement", "Seconds", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Tincrement", "Minutes", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Tincrement", "Hours", 0, QApplication::UnicodeUTF8)
        );
        updateBtn->setText(QApplication::translate("Tincrement", "update times", 0, QApplication::UnicodeUTF8));
        revertBtn->setText(QApplication::translate("Tincrement", "revert times", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Tincrement: public Ui_Tincrement {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TINCREMENT_H
