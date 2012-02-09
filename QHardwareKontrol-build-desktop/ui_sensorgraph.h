/********************************************************************************
** Form generated from reading UI file 'sensorgraph.ui'
**
** Created: Fri Feb 3 01:33:10 2012
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SENSORGRAPH_H
#define UI_SENSORGRAPH_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>
#include "qwt/qwt_plot.h"

QT_BEGIN_NAMESPACE

class Ui_SensorGraph
{
public:
    QHBoxLayout *horizontalLayout;
    QwtPlot *qwtPlot;

    void setupUi(QWidget *SensorGraph)
    {
        if (SensorGraph->objectName().isEmpty())
            SensorGraph->setObjectName(QString::fromUtf8("SensorGraph"));
        SensorGraph->resize(444, 286);
        horizontalLayout = new QHBoxLayout(SensorGraph);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        qwtPlot = new QwtPlot(SensorGraph);
        qwtPlot->setObjectName(QString::fromUtf8("qwtPlot"));

        horizontalLayout->addWidget(qwtPlot);


        retranslateUi(SensorGraph);

        QMetaObject::connectSlotsByName(SensorGraph);
    } // setupUi

    void retranslateUi(QWidget *SensorGraph)
    {
        SensorGraph->setWindowTitle(QApplication::translate("SensorGraph", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SensorGraph: public Ui_SensorGraph {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SENSORGRAPH_H
