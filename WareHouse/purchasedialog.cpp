#include "purchasedialog.h"
#include "ui_purchasedialog.h"
#include <QDate>

PurchaseDialog::PurchaseDialog(QSqlDatabase *database, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PurchaseDialog)
{
    ui->setupUi(this);
    db = database;
    // setup the models
    setupModels();
}


PurchaseDialog::~PurchaseDialog()
{
    delete ui;
}

void PurchaseDialog::setupModels()
{
    loadInvoiceNumber();
    //get the current date
    ui->purchase_dateEdit->setDate(QDate::currentDate());
    /// setup model related things
    setupVendorNameCompleter();
}

void PurchaseDialog::setupVendorNameCompleter()
{
    /// implements the auto completion for itemcode_spinbox

    //prepare the model
    vendor_name_model->setQuery("select name from vendors");
    auto vendor_name_completer = new QCompleter(vendor_name_model, this);
    vendor_name_completer->setCompletionColumn(0);
    vendor_name_completer->setCaseSensitivity(Qt::CaseInsensitive);
    vendor_name_completer->setCompletionMode(QCompleter::PopupCompletion);

    // set the model onto the item_code_spinbox
    ui->vendorname_lineEdit->setCompleter(vendor_name_completer);
}

void PurchaseDialog::loadInvoiceNumber()
{
    /// loads a new invoice number based on the most recent invoice number
    ///will be implemented after the database is created

    //execute the query
    QSqlQuery q(*db);
    q.prepare("select MAX(invoice_no) from purchase_invoice");
    if(!q.exec()){
        QMessageBox::critical(this, "Invoice", q.lastError().text()
                              + "\n" + q.lastQuery());
        //set 1 as the invoice number
        ui->invoiceno_spinBox_2->setValue(1);
        return;
    }

    //display next on the invoice field
    if(q.next()){
        qint64 invoice_number = q.value(0).toLongLong();//get the recent one
        ui->invoiceno_spinBox_2->setValue(invoice_number+1);//display incremented one
    }
}

bool PurchaseDialog::validateForm()
{
    /// validates the form before submission
    /// checks for empty fields
    /// doesn't check the database because these checks are made while editing fields

    if (ui->itemcode_spinBox->text().isEmpty()
            || ui->vendorname_lineEdit->text().isEmpty()
            || ui->itemcode_spinBox->text().isEmpty()
            || ui->quantity_doubleSpinBox->text().isEmpty()
            || ui->rateperunit_doubleSpinBox->text().isEmpty()
            || ui->amountpaid_spinBox_3->text().isEmpty())
        return false;
    return true;
}

bool PurchaseDialog::processPurchase()
{
    /// save the invoice in purchase_invoice
    /// update the item stock

    // gat the resources
    QString invoice = ui->invoiceno_spinBox_2->text();
    QString date    = ui->purchase_dateEdit->date().toString("dd-mm-yyyy");
                        //vendor code is in the private variable
    qint64 item_code = ui->itemcode_spinBox->value();
    qreal quantity   = ui->quantity_doubleSpinBox->value();
    qreal rate_per_item = ui->rateperunit_doubleSpinBox->value();
    qint64 amount_paid = ui->amountpaid_spinBox_3->value();

    // prepare the query
    db->transaction(); // start the transaction
    QSqlQuery q(*db);

    q.prepare("INSERT INTO purchase_invoice"
              "(invoice_no,date,vendor_code,item_code,quantity,rate_per_unit,amount_paid)"
              " VALUES (:invoice, :date, :vendor, :item, :quantity, :rate, :amount);");

    q.bindValue(":invoice", invoice);
    q.bindValue(":date", date);
    q.bindValue(":vendor", vendor_code);
    q.bindValue(":item", item_code);
    q.bindValue(":quantity", quantity);
    q.bindValue(":rate", rate_per_item);
    q.bindValue(":amount", amount_paid);

    //execute the query
    if(!q.exec()){//if the query has some error then return
        QMessageBox::critical(this, "Error", q.lastError().text()
                              + "\n" + q.lastQuery());
        db->rollback();
        return false;
    }

    // successfully executed
    // update the stock of that item
    q.prepare("update items set quantity=quantity+? where item_code=?");
    q.bindValue(0, quantity);
    q.bindValue(1, item_code);
    if(!q.exec()){//if the query has some error then return
        QMessageBox::critical(this, "Error", q.lastError().text()
                              + "\n" + q.lastQuery());
        db->rollback();
        return false;
    }
    // updated the item successfully
    // so commit the database and return true
    db->commit();
    return true;
}


void PurchaseDialog::on_itemcode_spinBox_editingFinished()
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

void PurchaseDialog::on_vendorname_lineEdit_editingFinished()
{
    /// Searches the database for that vendor
    /// if it is present, load its description
    /// otherwise make this field red indicating a new item
    // get the itemcode
    QString vendor    = ui->vendorname_lineEdit->text();

    //prepare the query
    QSqlQuery q(*db);
    q.prepare("select vendor_code, name, address from vendors where name=?");
    q.bindValue(0, vendor);

    //execute the query
    if(!q.exec()){//if the query has some error then return
        QMessageBox::critical(this, "Error", q.lastError().text()
                              + "\n" + q.lastQuery());
        return;
    }

    // if the query executes
    // check for the result
    if (q.next()){//if the result exists then
        //set the right style sheet
        QString right_style = "font-size:16px;color:green;";
        ui->vendorname_lineEdit->setStyleSheet(right_style);
        // save the vendor_code
        qint8 index = q.record().indexOf("vendor_code");
        vendor_code = q.value(index).toString();
    } else {
        //if the name doesn't exist then change the color of widget,and focus on it
        QString wrong_style = "font-size:16px;color:red;";
        ui->vendorname_lineEdit->setStyleSheet(wrong_style);
        ui->vendorname_lineEdit->setFocus();
    }
}

void PurchaseDialog::on_quantity_doubleSpinBox_valueChanged(double value)
{
    qint64 total = value * ui->rateperunit_doubleSpinBox->value();
    ui->totalamounttobepaid_spinBox_2->setValue(total);
}

void PurchaseDialog::on_rateperunit_doubleSpinBox_valueChanged(double value)
{
    qint64 total = value * ui->quantity_doubleSpinBox->value();
    ui->totalamounttobepaid_spinBox_2->setValue(total);
}

void PurchaseDialog::on_purchase_pushButton_clicked()
{
    /// makes the purchase
    /// stores the invoice details in the purchase_invoice table
    /// updates the stock of the item
    if(!validateForm()){
        QMessageBox::warning(this,"Fill Form", "Please Fill the form completely.");
        return;
    }

    //confirms from the user
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,"Are You Sure?",
                                  "You can not undo the entry."
                                  "Do you want to continue?",
                                  QMessageBox::Yes | QMessageBox::Cancel);
    //if the user accepts the dialog
    if (reply == QMessageBox::Yes){
        if(processPurchase()){ // if the query is successfull
            QMessageBox::information(this, "Succesfull", "Congratulations on your purchase!");
            this->accept();
        }
    }
}

void PurchaseDialog::on_invoiceno_spinBox_2_editingFinished()
{
    /// validates the invoice number before leaving the widget
    // get the invoice_no
    QString invoice    = ui->invoiceno_spinBox_2->text();

    //prepare the query
    QSqlQuery q(*db);
    q.prepare("select invoice_no from purchase_invoice where invoice_no=?");
    q.bindValue(0, invoice);

    //execute the query
    if(!q.exec()){//if the query has some error then return
        QMessageBox::critical(this, "Error", q.lastError().text()
                              + "\n" + q.lastQuery());
        return;
    }

    // if the query executes
    // check for the result
    if (q.next()){//if the result exists then
        //set the wrong style sheet and focus
        QString wrong_style = "font-size:16px;color:red;";
        ui->invoiceno_spinBox_2->setStyleSheet(wrong_style);
        ui->invoiceno_spinBox_2->setFocus();
    } else {
        //if the invoice_no doesn't exist then change the color of widget
        QString right_style = "font-size:16px;color:green;";
        ui->invoiceno_spinBox_2->setStyleSheet(right_style);
    }
}
