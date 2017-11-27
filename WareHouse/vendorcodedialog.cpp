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
