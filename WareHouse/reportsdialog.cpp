#include "reportsdialog.h"
#include "ui_reportsdialog.h"

ReportsDialog::ReportsDialog(QSqlDatabase *database, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReportsDialog)
{
    ui->setupUi(this);
    db = database;

    setDates();
    setupModel();
}

void ReportsDialog::setDates()
{
    ui->from_dateEdit->setDate(QDate::currentDate().addMonths(-1));
    ui->to_dateEdit->setDate(QDate::currentDate());
}

void ReportsDialog::setupModel()
{
    QSqlQuery q(*db);
    q.prepare("select * from purchase_invoice where date>? and date<?");
    q.bindValue(0, ui->from_dateEdit->date().toString("yyyy-mm-dd"));
    q.bindValue(1, ui->to_dateEdit->date().toString("yyyy-mm-dd"));
    if(!q.exec()){
        QMessageBox::warning(this, "Error",
                             "Could not load reports due to error : "
                             + q.lastError().text());
        return;
    }
    //setup model
    reportModel->setQuery(q);
    ui->report_tableView->setModel(reportModel);
}


ReportsDialog::~ReportsDialog()
{
    delete ui;
}

void ReportsDialog::on_generate_report_pushbutton_clicked()
{
    setupModel();
}
