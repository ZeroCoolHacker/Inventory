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


void SalesDialog::setupModels()
{
    /// setup the models
    /// load other things at startup

    loadInvoiceNumber();//display the most recent invoice
    setupVendorNameCompleter();
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

void SalesDialog::setupVendorNameCompleter()
{
    /// implements the auto completion for itemcode_spinbox

    //prepare the model
    vendor_name_model->setQuery("select name from vendors");
    auto vendor_name_completer = new QCompleter(vendor_name_model, this);
    vendor_name_completer->setCompletionColumn(0);
    vendor_name_completer->setCaseSensitivity(Qt::CaseInsensitive);
    vendor_name_completer->setCompletionMode(QCompleter::PopupCompletion);

    // set the model onto the item_code_spinbox
    ui->buyername_lineEdit->setCompleter(vendor_name_completer);
}

bool SalesDialog::validateForm()
{
    if (ui->itemcode_spinBox->text().isEmpty()
            || ui->sales_dateEdit->text().isEmpty()
            || ui->buyername_lineEdit->text().isEmpty()
            || ui->invoiceno_spinBox_2->text().isEmpty()
            || ui->quantity_doubleSpinBox->text().isEmpty()
            || ui->rateperunit_doubleSpinBox->text().isEmpty()
            || ui->amountpaid_spinBox_3->text().isEmpty()
            || ui->totalamounttobepaid_spinBox_2->text().isEmpty())
        return false;
    return true;
}

bool SalesDialog::processSale()
{
    /// save the invoice in sales_invoice
    /// update the item stock

    // gat the resources
    QString invoice = ui->invoiceno_spinBox_2->text();
    QString date    = ui->sales_dateEdit->date().toString("yyyy-MM-dd");
    QString vendor   = ui->buyername_lineEdit->text();
    qint64 item_code = ui->itemcode_spinBox->value();
    qreal quantity   = ui->quantity_doubleSpinBox->value();
    qreal rate_per_item = ui->rateperunit_doubleSpinBox->value();
    qint64 amount_paid = ui->amountpaid_spinBox_3->value();

    // prepare the query
    db->transaction(); /// start the transaction
    QSqlQuery q(*db);

    q.prepare("INSERT INTO sales_invoice"
              "(invoice_no,date,vendor_code,item_code,quantity,rate_per_unit,amount_paid)"
              " VALUES (:invoice, :date, :vendor, :item, :quantity, :rate, :amount);");

    q.bindValue(":invoice", invoice);
    q.bindValue(":date", date);
    q.bindValue(":vendor", vendor);
    q.bindValue(":item", item_code);
    q.bindValue(":quantity", quantity);
    q.bindValue(":rate", rate_per_item);
    q.bindValue(":amount", amount_paid);

    //execute the query
    if(!q.exec()){//if the query has some error then return
        QMessageBox::critical(this, "Error", q.lastError().text()
                              + "\n" + q.lastQuery());
        db->rollback();///rollback
        return false;
    }

    // successfully executed
    // update the stock of that item
    q.prepare("update items set quantity=quantity-? where item_code=?");
    q.bindValue(0, quantity);
    q.bindValue(1, item_code);
    if(!q.exec()){//if the query has some error then return
        QMessageBox::critical(this, "Error", q.lastError().text()
                              + "\n" + q.lastQuery());
        db->rollback();///rollback
        return false;
    }
    // updated the item successfully
    // so commit the database and return true
    db->commit();/// commit
    return true;
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
    q.prepare("select item_code,item_description,quantity from items where item_code=?");
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
        //get the description and quantity
        qint8 description_field = q.record().indexOf("item_description");
        qint8 quantity_field    = q.record().indexOf("quantity");
        qreal stock             = q.value(quantity_field).toReal();
        ui->quantity_doubleSpinBox->setMaximum(stock);
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

void SalesDialog::on_sell_pushButton_clicked()
{
    /// makes the sale
    /// stores the invoice details in the sales_invoice table
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
        if(processSale()){ // if the query is successfull
            QMessageBox::information(this, "Succesfull", "Congratulations on your Sale!");
            this->accept();
        }
    }
}

void SalesDialog::on_buyername_lineEdit_editingFinished()
{
    /// Searches the database for that vendor
    /// if it is present, load its description
    /// otherwise make this field red indicating a new item
    // get the itemcode
    QString vendor    = ui->buyername_lineEdit->text();

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
        ui->buyername_lineEdit->setStyleSheet(right_style);
        // save the vendor_code
        qint8 index = q.record().indexOf("vendor_code");
        vendor_code = q.value(index).toString();
    } else {
        //if the name doesn't exist then change the color of widget,and focus on it
        QString wrong_style = "font-size:16px;color:red;";
        ui->buyername_lineEdit->setStyleSheet(wrong_style);
        ui->buyername_lineEdit->setFocus();
    }
}
