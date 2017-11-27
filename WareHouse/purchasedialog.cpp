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
