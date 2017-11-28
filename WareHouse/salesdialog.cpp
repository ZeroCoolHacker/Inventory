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
    //set date
    ui->sales_dateEdit->setDate(QDate::currentDate());
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

void SalesDialog::on_itemcode_spinBox_editingFinished()
{
    /// Searches the database for that itemcode
    /// if it is present, load its description
    /// otherwise make this field red indicating a new item

    // get the itemcode
    qint64 item_code    = ui->itemcode_spinBox->value();

    //prepare the query
    QSqlQuery q(*db);
    q.prepare("select item_code,item_description from items where item_code=?");
    q.bindValue(0, item_code);

    //execute the query
    if(!q.exec()){//if the query has some error then return
        QMessageBox::critical(this, "Error", q.lastError().text()
                              + "\n" + q.lastQuery());
        return;
    }

    // if the query executes
    // check for the result
    if (q.next()){//if the result exists then load the description
        //set the right style sheet
        QString right_style = "font-size:16px;color:green;";
        ui->itemcode_spinBox->setStyleSheet(right_style);
        //get the description
        qint8 description_field = q.record().indexOf("item_description");
        QString description     = q.value(description_field).toString();
        //write the description into widget
        ui->itemdescription_plainTextEdit->setPlainText(description);
    } else {
        //if the code doesn't exist then change the color of widget,and focus on it
        QString wrong_style = "font-size:16px;color:red;";
        ui->itemcode_spinBox->setStyleSheet(wrong_style);
        ui->itemcode_spinBox->setFocus();
    }
}

void SalesDialog::on_quantity_doubleSpinBox_valueChanged(double value)
{
    qint64 total = value * ui->rateperunit_doubleSpinBox->value();
    ui->totalamounttobepaid_spinBox_2->setValue(total);
}

void SalesDialog::on_rateperunit_doubleSpinBox_valueChanged(double value)
{
    qint64 total = value * ui->quantity_doubleSpinBox->value();
    ui->totalamounttobepaid_spinBox_2->setValue(total);
}
