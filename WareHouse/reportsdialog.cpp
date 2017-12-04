#include "reportsdialog.h"
#include "ui_reportsdialog.h"

ReportsDialog::ReportsDialog(qint8 reportType, QSqlDatabase *database, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReportsDialog)
{
    ui->setupUi(this);
    report_type = reportType;
    db = database;

    setupModel();
}

void ReportsDialog::setupModel()
{
    if (report_type == SALES_VENDORWISE){
        setupSalesVendorWiseModel();
    }
}

void ReportsDialog::setupSalesVendorWiseModel()
{
    QSqlQuery q(*db);
    q.prepare()
}

ReportsDialog::~ReportsDialog()
{
    delete ui;
}
