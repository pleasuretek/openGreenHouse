/********************************************************************************
** Form generated from reading UI file 'sensors.ui'
**
** Created: Fri Feb 17 17:52:42 2012
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SENSORS_H
#define UI_SENSORS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Sensors
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_temp;
    QVBoxLayout *verticalLayout_4;
    QGridLayout *gridLayout_2;
    QLabel *label_8;
    QLabel *label_7;
    QLabel *label_10;
    QLabel *tempLabel01;
    QLabel *tempLabel02;
    QLabel *tempLabel03;
    QLabel *label_9;
    QLabel *humidLabel;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *graphBtn;
    QPushButton *updateTempBtn;

    void setupUi(QWidget *Sensors)
    {
        if (Sensors->objectName().isEmpty())
            Sensors->setObjectName(QString::fromUtf8("Sensors"));
        Sensors->resize(360, 237);
        verticalLayout = new QVBoxLayout(Sensors);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox_temp = new QGroupBox(Sensors);
        groupBox_temp->setObjectName(QString::fromUtf8("groupBox_temp"));
        verticalLayout_4 = new QVBoxLayout(groupBox_temp);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_8 = new QLabel(groupBox_temp);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_2->addWidget(label_8, 0, 0, 1, 1);

        label_7 = new QLabel(groupBox_temp);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_2->addWidget(label_7, 1, 0, 1, 1);

        label_10 = new QLabel(groupBox_temp);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_2->addWidget(label_10, 2, 0, 1, 1);

        tempLabel01 = new QLabel(groupBox_temp);
        tempLabel01->setObjectName(QString::fromUtf8("tempLabel01"));

        gridLayout_2->addWidget(tempLabel01, 0, 1, 1, 1);

        tempLabel02 = new QLabel(groupBox_temp);
        tempLabel02->setObjectName(QString::fromUtf8("tempLabel02"));

        gridLayout_2->addWidget(tempLabel02, 1, 1, 1, 1);

        tempLabel03 = new QLabel(groupBox_temp);
        tempLabel03->setObjectName(QString::fromUtf8("tempLabel03"));

        gridLayout_2->addWidget(tempLabel03, 2, 1, 1, 1);

        label_9 = new QLabel(groupBox_temp);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_2->addWidget(label_9, 3, 0, 1, 1);

        humidLabel = new QLabel(groupBox_temp);
        humidLabel->setObjectName(QString::fromUtf8("humidLabel"));

        gridLayout_2->addWidget(humidLabel, 3, 1, 1, 1);


        verticalLayout_4->addLayout(gridLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        graphBtn = new QPushButton(groupBox_temp);
        graphBtn->setObjectName(QString::fromUtf8("graphBtn"));

        horizontalLayout_4->addWidget(graphBtn);

        updateTempBtn = new QPushButton(groupBox_temp);
        updateTempBtn->setObjectName(QString::fromUtf8("updateTempBtn"));

        horizontalLayout_4->addWidget(updateTempBtn);


        verticalLayout_4->addLayout(horizontalLayout_4);


        verticalLayout->addWidget(groupBox_temp);


        retranslateUi(Sensors);

        QMetaObject::connectSlotsByName(Sensors);
    } // setupUi

    void retranslateUi(QWidget *Sensors)
    {
        Sensors->setWindowTitle(QApplication::translate("Sensors", "Form", 0, QApplication::UnicodeUTF8));
        groupBox_temp->setTitle(QApplication::translate("Sensors", "Temps", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("Sensors", "Bloom Temp 01:", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("Sensors", "Bloom Temp 02:", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("Sensors", "Veg Temp:", 0, QApplication::UnicodeUTF8));
        tempLabel01->setText(QApplication::translate("Sensors", "tempLabel", 0, QApplication::UnicodeUTF8));
        tempLabel02->setText(QApplication::translate("Sensors", "tempLabel", 0, QApplication::UnicodeUTF8));
        tempLabel03->setText(QApplication::translate("Sensors", "tempLabel", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("Sensors", "Bloom Humidity", 0, QApplication::UnicodeUTF8));
        humidLabel->setText(QApplication::translate("Sensors", "TextLabel", 0, QApplication::UnicodeUTF8));
        graphBtn->setText(QApplication::translate("Sensors", "Show Graph", 0, QApplication::UnicodeUTF8));
        updateTempBtn->setText(QApplication::translate("Sensors", "updateTemps", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Sensors: public Ui_Sensors {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SENSORS_H
