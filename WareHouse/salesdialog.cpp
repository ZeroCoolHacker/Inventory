#include "salesdialog.h"
#include "ui_salesdialog.h"

SalesDialog::SalesDialog(QSqlDatabase *database, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SalesDialog)
{
    ui->setupUi(this);
    db = database;

    setupModels();
}

SalesDialog::~SalesDialog()
{
    delete ui;
}

void SalesDialog::initializeModels()
{

}

void SalesDialog::setupModels()
{
    /// setup the models
    /// load other things at startup

    loadInvoiceNumber();//display the most recent invoice
}


void SalesDialog::loadInvoiceNumber()
{
    /// loads a new invoice number based on the most recent invoice number
    ///will be implemented after the database is created

    //execute the query
    QSqlQuery q(*db);
    q.prepare("select MAX(invoice_no) from sales_invoice");
    if(!q.exec()){
        QMessageBox::critical(this, "Invoice", q.lastError().text()
                              + "\n" + q.lastQuery());
        // set 1 as the invoice number
        ui->invoiceno_spinBox_2->setValue(1);
        return;
    }

    //display next on the invoice field
    if(q.next()){
        qint64 invoice_number = q.value(0).toLongLong();//get the recent one
        ui->invoiceno_spinBox_2->setValue(invoice_number+1);//display incremented one
    }
}
