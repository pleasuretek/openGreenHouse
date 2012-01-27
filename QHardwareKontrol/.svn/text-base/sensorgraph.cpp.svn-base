#include "sensorgraph.h"
#include "ui_sensorgraph.h"



SensorGraph::SensorGraph(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SensorGraph)
{
    ui->setupUi(this);

    this->setWindowTitle("Sensor Data");

    ui->qwtPlot->setAxisTitle(QwtPlot::yLeft, "Temperature");
    ui->qwtPlot->setAxisScale(QwtPlot::yLeft, 40, 140);

    drawPlot();
}

SensorGraph::~SensorGraph()
{
    delete ui;
}

void SensorGraph::drawPlot() {


    QStringList list;
    QSqlQuery q;
    q.prepare("SELECT DISTINCT address FROM Temps");      //get each adress
    q.exec();
    while (q.next()) {
        QString address = q.value(0).toString();
        list.append(address);               //add each address to the list
        qDebug() << "address : " << q.value(0).toString();
        q.clear();
        q.prepare("SELECT temp, time FROM Temps WEHRE address = :address ORDER BY time DESC LIMIT 200");
        q.bindValue(":address",address);
        q.exec();
        while (q.next()) {
            //add temps to array
            //add timestamps to qwt plot label
        }
    }

    if(!list.isEmpty()){

    }
}
