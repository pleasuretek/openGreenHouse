/********************************************************************************
** Form generated from reading UI file 'entry.ui'
**
** Created: Fri Feb 17 17:52:42 2012
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ENTRY_H
#define UI_ENTRY_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDateEdit>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QFormLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QTableView>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Entry
{
public:
    QVBoxLayout *verticalLayout_2;
    QFormLayout *formLayout;
    QLabel *label;
    QDateEdit *dateEdit_date;
    QLabel *label_2;
    QSpinBox *spinBox_ppm;
    QLabel *label_3;
    QDoubleSpinBox *doubleSpinBox_ph;
    QLabel *label_7;
    QPlainTextEdit *noteTextEdit;
    QGroupBox *imageGroup;
    QVBoxLayout *verticalLayout;
    QTableView *imageTable;
    QHBoxLayout *horizontalLayout;
    QPushButton *addImageBtn;
    QPushButton *pushButton_2;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Entry)
    {
        if (Entry->objectName().isEmpty())
            Entry->setObjectName(QString::fromUtf8("Entry"));
        Entry->resize(314, 502);
        verticalLayout_2 = new QVBoxLayout(Entry);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        label = new QLabel(Entry);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label);

        dateEdit_date = new QDateEdit(Entry);
        dateEdit_date->setObjectName(QString::fromUtf8("dateEdit_date"));

        formLayout->setWidget(1, QFormLayout::FieldRole, dateEdit_date);

        label_2 = new QLabel(Entry);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_2);

        spinBox_ppm = new QSpinBox(Entry);
        spinBox_ppm->setObjectName(QString::fromUtf8("spinBox_ppm"));
        spinBox_ppm->setMaximum(3000);
        spinBox_ppm->setSingleStep(100);

        formLayout->setWidget(2, QFormLayout::FieldRole, spinBox_ppm);

        label_3 = new QLabel(Entry);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_3);

        doubleSpinBox_ph = new QDoubleSpinBox(Entry);
        doubleSpinBox_ph->setObjectName(QString::fromUtf8("doubleSpinBox_ph"));
        doubleSpinBox_ph->setDecimals(1);
        doubleSpinBox_ph->setMaximum(14);
        doubleSpinBox_ph->setSingleStep(0.1);
        doubleSpinBox_ph->setValue(6);

        formLayout->setWidget(3, QFormLayout::FieldRole, doubleSpinBox_ph);

        label_7 = new QLabel(Entry);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_7);

        noteTextEdit = new QPlainTextEdit(Entry);
        noteTextEdit->setObjectName(QString::fromUtf8("noteTextEdit"));

        formLayout->setWidget(4, QFormLayout::FieldRole, noteTextEdit);


        verticalLayout_2->addLayout(formLayout);

        imageGroup = new QGroupBox(Entry);
        imageGroup->setObjectName(QString::fromUtf8("imageGroup"));
        verticalLayout = new QVBoxLayout(imageGroup);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        imageTable = new QTableView(imageGroup);
        imageTable->setObjectName(QString::fromUtf8("imageTable"));

        verticalLayout->addWidget(imageTable);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        addImageBtn = new QPushButton(imageGroup);
        addImageBtn->setObjectName(QString::fromUtf8("addImageBtn"));

        horizontalLayout->addWidget(addImageBtn);

        pushButton_2 = new QPushButton(imageGroup);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addWidget(imageGroup);

        buttonBox = new QDialogButtonBox(Entry);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_2->addWidget(buttonBox);


        retranslateUi(Entry);
        QObject::connect(buttonBox, SIGNAL(accepted()), Entry, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Entry, SLOT(reject()));

        QMetaObject::connectSlotsByName(Entry);
    } // setupUi

    void retranslateUi(QDialog *Entry)
    {
        Entry->setWindowTitle(QApplication::translate("Entry", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Entry", "Date", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Entry", "PPM", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Entry", "PH", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("Entry", "Notes", 0, QApplication::UnicodeUTF8));
        imageGroup->setTitle(QApplication::translate("Entry", "Images", 0, QApplication::UnicodeUTF8));
        addImageBtn->setText(QApplication::translate("Entry", "Add Image", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("Entry", "Remove Image", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Entry: public Ui_Entry {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ENTRY_H
