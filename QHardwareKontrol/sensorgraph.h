#ifndef SENSORGRAPH_H
#define SENSORGRAPH_H

#include <QWidget>
#include <QtSql>
#include "qwt-qt4/qwt.h"
#include "qwt-qt4/qwt_plot.h"
#include "qwt-qt4/qwt_plot_curve.h"

#define SAMPLES 200

namespace Ui {
    class SensorGraph;
}

class SensorGraph : public QWidget
{
    Q_OBJECT

public:
    explicit SensorGraph(QWidget *parent = 0);
    ~SensorGraph();


public slots:
    void drawPlot();

private:
    Ui::SensorGraph *ui;

};

#endif // SENSORGRAPH_H
