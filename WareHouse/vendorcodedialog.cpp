#include "vendorcodedialog.h"
#include "ui_vendorcodedialog.h"

VendorCodeDialog::VendorCodeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VendorCodeDialog)
{
    ui->setupUi(this);
}

VendorCodeDialog::~VendorCodeDialog()
{
    delete ui;
}
