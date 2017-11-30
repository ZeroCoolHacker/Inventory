#include "reportsdialog.h"
#include "ui_reportsdialog.h"

ReportsDialog::ReportsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReportsDialog)
{
    ui->setupUi(this);
}

ReportsDialog::~ReportsDialog()
{
    delete ui;
}
