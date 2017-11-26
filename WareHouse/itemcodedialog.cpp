#include "itemcodedialog.h"
#include "ui_itemcodedialog.h"

ItemCodeDialog::ItemCodeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ItemCodeDialog)
{
    ui->setupUi(this);
}

ItemCodeDialog::~ItemCodeDialog()
{
    delete ui;
}
