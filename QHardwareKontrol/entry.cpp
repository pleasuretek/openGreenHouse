#include "entry.h"
#include "ui_entry.h"

Entry::Entry(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Entry)
{
    ui->setupUi(this);

    QDate *today = new QDate;
    today->currentDate();
    startDateCal = new QCalendarWidget;

    //ui->imageGroup->setVisible(false);

    ui->dateEdit_date->setDate(today->currentDate());
    ui->dateEdit_date->setCalendarWidget(startDateCal);
    ui->dateEdit_date->setCalendarPopup(true);

    //TODO: connect addImageBtn to slot that adds an image to database

    //TODO: query database for images with EntryID to populate ui->imageTable

}

Entry::~Entry()
{
    delete ui;
}

QList<QVariant> Entry::getAmts() {
    QList<QVariant> list;
    list.append(ui->dateEdit_date->date());
    list.append(ui->spinBox_ppm->value());
    list.append(ui->doubleSpinBox_ph->value());
    list.append(ui->noteTextEdit->toPlainText());


    return list;

}

void Entry::setAmts(QList<QVariant> list) {
    if(!list.isEmpty()) {

        ui->dateEdit_date->setDate(QDate::fromString(list.at(0).toString()));
        ui->spinBox_ppm->setValue(list.at(1).toInt());
        ui->doubleSpinBox_ph->setValue(list.at(2).toDouble());
        ui->noteTextEdit->setPlainText(list.at(3).toString());
    }
}

void Entry::setImg() {

}

void Entry::getImg() {


  //  QSqlQuery q;
  //  q.prepare("SELECT COUNT(*) FROM Image WHERE EntryID = :entryID");
  //  q.bindValue(":entryID", id);

}
