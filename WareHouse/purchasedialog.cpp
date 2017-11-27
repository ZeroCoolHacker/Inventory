#include "purchasedialog.h"
#include "ui_purchasedialog.h"

PurchaseDialog::PurchaseDialog(QSqlDatabase *database, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PurchaseDialog)
{
    ui->setupUi(this);
    db = database;
}


PurchaseDialog::~PurchaseDialog()
{
    delete ui;
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
