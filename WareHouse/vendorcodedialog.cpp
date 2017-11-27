#include "vendorcodedialog.h"
#include "ui_vendorcodedialog.h"

VendorCodeDialog::VendorCodeDialog(QSqlDatabase *database, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VendorCodeDialog)
{
    ui->setupUi(this);
    db = database;
}

VendorCodeDialog::~VendorCodeDialog()
{
    delete ui;
}

bool VendorCodeDialog::validateForm()
{
    if (ui->vendorcode_spinBox->text().isEmpty()
            || ui->vendorname_lineEdit->text().isEmpty()
            || ui->vendoraddress_lineEdit_2->text().isEmpty())
        return false;
    return true;
}

bool VendorCodeDialog::addVendor()
{
    /// takes care of the query preperation and execution
    /// to add vendor to database vendors table

    //gather arguments
    qint64  vendor_code    = ui->vendorcode_spinBox->value();
    QString name           = ui->vendorname_lineEdit->text();
    QString address        = ui->vendoraddress_lineEdit_2->text();

    //prepare the query
    QSqlQuery q(*db);
    q.prepare("insert into vendors (vendor_code, name, address) values "
              "(:vendor_code, :name, :address);");
    q.bindValue(":vendor_code", vendor_code);
    q.bindValue(":name", name);
    q.bindValue(":address", address);

    //execute the query
    if(!q.exec()){
        QMessageBox::critical(this, "Error", q.lastError().text()
                              + "\n" + q.lastQuery());
        return false;
    }
    return true;
}

void VendorCodeDialog::resetForm()
{
    /// clears the form after successfull submission

    ui->vendorcode_spinBox->clear();
    ui->vendoraddress_lineEdit_2->clear();
    ui->vendorname_lineEdit->clear();
    ui->vendorcode_spinBox->setFocus();
}

void VendorCodeDialog::on_add_pushButton_clicked()
{
    //// Validates the form
    /// Adds the vendor to the database vendors table
    /// and resets the form
    //validate form
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
        if(addVendor()){ // if the query is successfull
            QMessageBox::information(this, "Succesfull", "Vendor Addd Successfully!");
            resetForm();
        }
    }
}
