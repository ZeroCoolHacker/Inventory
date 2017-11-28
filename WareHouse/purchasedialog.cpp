#include "purchasedialog.h"
#include "ui_purchasedialog.h"

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
    q.prepare("select vendor_code, name from vendors where name=?");
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
