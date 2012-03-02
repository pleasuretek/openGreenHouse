/********************************************************************************
** Form generated from reading UI file 'target.ui'
**
** Created: Fri Feb 17 17:52:42 2012
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TARGET_H
#define UI_TARGET_H

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
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Target
{
public:
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QSpinBox *spinBox;
    QHBoxLayout *horizontalLayout;
    QPushButton *updateBtn;
    QPushButton *revertBtn;

    void setupUi(QWidget *Target)
    {
        if (Target->objectName().isEmpty())
            Target->setObjectName(QString::fromUtf8("Target"));
        Target->resize(274, 140);
        verticalLayout_2 = new QVBoxLayout(Target);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox = new QGroupBox(Target);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        spinBox = new QSpinBox(groupBox);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));

        formLayout->setWidget(0, QFormLayout::FieldRole, spinBox);


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


        retranslateUi(Target);

        QMetaObject::connectSlotsByName(Target);
    } // setupUi

    void retranslateUi(QWidget *Target)
    {
        Target->setWindowTitle(QApplication::translate("Target", "Form", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("Target", "Target", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Target", "TextLabel", 0, QApplication::UnicodeUTF8));
        updateBtn->setText(QApplication::translate("Target", "update target", 0, QApplication::UnicodeUTF8));
        revertBtn->setText(QApplication::translate("Target", "revert target", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Target: public Ui_Target {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TARGET_H
