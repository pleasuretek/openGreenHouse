#include "tincrement.h"
#include "ui_tincrement.h"

Tincrement::Tincrement(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tincrement)
{
    ui->setupUi(this);

    relayID=0;
}

Tincrement::Tincrement(QWidget *parent, int id) :
    QWidget(parent),
    ui(new Ui::Tincrement)
{
    ui->setupUi(this);

    relayID = id;
    this->on_revertBtn_clicked();

    cacheTimes();

    nextOn = QTime::currentTime();
    isOn   = false;  //init to false so it enters loop at first

    connect(ui->updateBtn, SIGNAL(clicked()), this, SIGNAL(update()));

}

Tincrement::~Tincrement()
{
    delete ui;
}

void Tincrement::cacheTimes() {
    QSqlQuery q;
    q.prepare("SELECT onTime, offTime FROM Timer WHERE relayID = :relayID");
    q.bindValue(":relayID", relayID.toInt());
    if(!q.exec()) {
        QMessageBox err;
        err.setText("DataBase error");
        err.setInformativeText(q.lastError().text());
        err.exec();
    }
    while(q.next()) {
        QString son = q.value(0).toString();
        QString soff = q.value(1).toString();
        onTime = son.split(':');
        offTime = soff.split(':');
    }
}

QString Tincrement::check(QTime now) {
    QString cmd;

    if(!isOn) { //if relay is off -> then check if should be turned on
        if(now >= nextOn) { //its after the nextTimeOn so do something
            cmd.append(relayID.toString());
            cmd.append(":on.");
            qDebug() << cmd << " -- " << now.toString();
            calNextOff(now);
            isOn=true;
            return cmd;
        } else { //do nothing
        }
    } else {  //relay is on, check when it needs to be turned off
        if(now >= nextOff) {
            cmd.append(relayID.toString());
            cmd.append(":off.");
            qDebug() << cmd << " -- " << now.toString();
            calNextOn(now);
            isOn=false;
            return cmd;
        } else {
        }
    }
    return cmd;   //catchall return empty string
}

void Tincrement::calNextOn(QTime now) {
    nextOn = now;
    switch (onTime.at(1).toInt()) {
    case 0:  //seconds
        nextOn = nextOn.addSecs(onTime.at(0).toInt());
        break;
    case 1: //minutes
        nextOn = nextOn.addSecs(60 * onTime.at(0).toInt());
        break;
    case 2: // hours
        nextOn = nextOn.addSecs(60 * 60 * onTime.at(0).toInt());
        break;
    default:
        //do nothing
        break;
    }
}

void Tincrement::calNextOff(QTime now) {
    nextOff = now;
    switch (offTime.at(1).toInt()) {
    case 0:  //seconds
        nextOff = nextOff.addSecs(offTime.at(0).toInt());
        break;
    case 1: //minutes
        nextOff = nextOff.addSecs(60 * offTime.at(0).toInt());
        break;
    case 2: // hours
        nextOff = nextOff.addSecs(60 * 60 * offTime.at(0).toInt());
        break;
    default:
        //do nothing
        break;
    }
}

void Tincrement::setTitle(QString label) {
    ui->timerLabel->setTitle(label);
}

bool Tincrement::confirmChange() {
    bool ret;
    QMessageBox msgBox;
    QString txt = "Relay " + relayID.toString();
    txt.append(" has been modified.");
    msgBox.setText(txt);
    msgBox.setInformativeText("Are you sure you want to change relay " + relayID.toString() + " ?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);
    if( msgBox.exec() == QMessageBox::Yes) {
        ret = true;
    } else {
        ret = false;
    }
    return ret;
}

void Tincrement::on_updateBtn_clicked()
{
    if(confirmChange()) {
        QSqlQuery q;
        q.prepare("SELECT * FROM Timer WHERE relayID = :relayID");
        q.bindValue(":relayID", relayID.toInt());
        q.exec();
        QVariant val = ui->spinBox->value();
        QString incOnTime = val.toString();
        incOnTime.append(":");  //delimiter
        incOnTime.append(ui->comboBox->currentIndex());
        val = ui->spinBox_2->value();
        QString incOffTime = val.toString();
        incOffTime.append(":");
        incOffTime.append(ui->comboBox_2->currentIndex());
        if(q.next()) { //relay with that ID exists... update
            q.clear();
            q.prepare("UPDATE Timer SET onTime = :onTime, offTime = :offTime WHERE relayID = :relayID");
            q.bindValue(":onTime",incOnTime);
            q.bindValue(":offTime",incOffTime);
            q.bindValue(":relayID",relayID.toInt());
            if(!q.exec()) {
                QMessageBox err;
                err.setText("Data Base Error");
                err.setInformativeText(q.lastError().text());
                err.exec();
            }
        } else {  //no relay ID so crete a new record
            q.clear();
            q.prepare("INSERT INTO Timer (onTime, offTime, relayID) VALUES(:onTime, :offTime, :relayID)");
            q.bindValue(":onTime",incOnTime);
            q.bindValue(":offTime", incOffTime);
            q.bindValue(":relayID",relayID.toInt());
            if(!q.exec()) {
                QMessageBox err;
                err.setText("Data Base Error");
                err.setInformativeText(q.lastError().text());
                err.exec();
            }
        }
        cacheTimes();
        emit update();
    } else {  //confirm() returned false

    }
}

void Tincrement::on_revertBtn_clicked()
{
    QSqlQuery q;
    q.prepare("SELECT onTime, offTime FROM Timer WHERE relayID = :relayID");
    q.bindValue(":relayID", relayID.toInt());
    if(!q.exec()) {
        QMessageBox err;
        err.setText("Data Base Error");
        err.setInformativeText(q.lastError().text());
        err.exec();
    }
    while(q.next()) {

        QString on  = q.value(0).toString();
        QString off = q.value(1).toString();

        QStringList list = on.split(":");
        ui->spinBox->setValue(list.at(0).toDouble());
        ui->comboBox->setCurrentIndex(list.at(1).toInt());

        list.clear();
        list = off.split(":");
        ui->spinBox_2->setValue(list.at(0).toDouble());
        ui->comboBox_2->setCurrentIndex(list.at(1).toInt());
    }
}
