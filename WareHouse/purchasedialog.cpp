#include "purchasedialog.h"
#include "ui_purchasedialog.h"

PurchaseDialog::PurchaseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PurchaseDialog)
{
    ui->setupUi(this);
}

PurchaseDialog::~PurchaseDialog()
{
    delete ui;
}
