#include "tracker.h"
#include "ui_tracker.h"

Tracker::Tracker(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tracker)
{
    ui->setupUi(this);

    ui->tableView->horizontalHeader()->setResizeMode(QHeaderView::Stretch);

    updateView();
    connect(ui->addBtn, SIGNAL(clicked()), this, SLOT(addEntry()));
    connect(ui->editBtn, SIGNAL(clicked()),this, SLOT(editEntry()));
    connect(ui->removeBtn, SIGNAL(clicked()), this, SLOT(removeEntry()));
    connect(ui->tableView, SIGNAL(clicked(QModelIndex)), this, SLOT(selectEntry(QModelIndex)));

}

Tracker::~Tracker()
{
    delete ui;
}

void Tracker::addEntry() {
    Entry *e = new Entry();

    if(e->exec() != QDialog::Accepted) {
        //cancel clicked
    } else {
        //ok clicked do stuff here
        dbInsert(e->getAmts());
        updateView();
    }
}

void Tracker::editEntry() {
    Entry *e = new Entry();
    //QString oldName ="";
    QList<QVariant> oldAmts;
    bool toggle = false;
   // bool reAdd = false;

    while(!toggle){
        if(!ui->tableView->selectionModel()->selectedIndexes().isEmpty()) {
            QList<QModelIndex> selectedItems = ui->tableView->selectionModel()->selectedIndexes();
            QVariant id = selectedItems.takeFirst().data().toInt();

            QSqlQuery q;
            q.prepare("SELECT * FROM Tracker WHERE entryID = :id");
            q.bindValue(":id",id);
            q.exec();
            if(!q.isActive()){
                //query failed
                QMessageBox::warning(this, tr("Entry Query"), tr("query failed to execute..."));
            } else {
                if(q.next()){ //populate with preExisting data
                    oldAmts.append(q.value(1).toString());
                    oldAmts.append(q.value(2).toInt());
                    oldAmts.append(q.value(3).toDouble());
                    oldAmts.append(q.value(4).toString());

                    e->setAmts(oldAmts);

                }

            }
            q.clear();
            if(e->exec() != QDialog::Accepted) {
                //cancel was clicked
                toggle = true;
            } else { //UPDATE data
                if(dbUpdate(e->getAmts(),id)) {
                    updateView();
                    toggle = true;
                }else{
                   //print last error from database
                }
            }
        }
        toggle = true;
    }
}

void Tracker::removeEntry() {
    QList<QModelIndex> selectedItems = ui->tableView->selectionModel()->selectedIndexes();
    QVariant id = selectedItems.takeFirst().data().toInt();

    QSqlQuery q;
    q.prepare("DELETE FROM Tracker WHERE entryID = :id");
    q.bindValue(":id", id.toInt());
    if(!q.exec()){
        //delete failed
        QMessageBox::warning(this, tr("delete failed"), tr("didn't remove data"));
    } else {
        updateView();
    }
}

void Tracker::selectEntry(QModelIndex model){
    ui->tableView->selectRow(model.row());
}

bool Tracker::dbInsert(QList<QVariant> l) {
    QSqlQuery q;
    q.prepare("INSERT INTO Tracker (date, ppm, ph, note) VALUES (:date, :ppm, :ph, :note)");
    q.bindValue(":date", l.at(0).toDate().toString());
    q.bindValue(":ppm", l.at(1).toInt());
    q.bindValue(":ph", l.at(2).toDouble());
    q.bindValue(":note", l.at(3).toString());

    if(!q.exec()){
        //update failed
        //TODO: have message box print error..
        QMessageBox::warning(this, tr("Insert error"), q.lastError().text());
        return false;
    } else {
        return true;
    }

}

bool Tracker::dbUpdate(QList<QVariant> l, QVariant id) {
    QSqlQuery q;
    q.prepare("UPDATE Tracker SET date = :date, ppm = :ppm, ph = :ph, note = :note WHERE entryID = :id");
    q.bindValue(":date", l.at(0).toDate().toString());
    q.bindValue(":ppm", l.at(1).toInt());
    q.bindValue(":ph", l.at(2).toDouble());
    q.bindValue(":note", l.at(3).toString());
    q.bindValue(":id", id);

    if(!q.exec()){
        //update failed
        QMessageBox::warning(this, tr("Update error"), q.lastError().text());
        return false;
    } else {
        return true;
    }
}

void Tracker::updateView() {
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT entryID, date, ppm, ph FROM Tracker");
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
}

