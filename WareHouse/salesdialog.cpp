#include "salesdialog.h"
#include "ui_salesdialog.h"

SalesDialog::SalesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SalesDialog)
{
    ui->setupUi(this);
}

SalesDialog::~SalesDialog()
{
    delete ui;
}
