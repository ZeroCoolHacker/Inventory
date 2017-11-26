#include "itemcodedialog.h"
#include "ui_itemcodedialog.h"

ItemCodeDialog::ItemCodeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ItemCodeDialog)
{
    ui->setupUi(this);

    //setup models
    setupModels();
}

void ItemCodeDialog::initializeModels()
{
    unitsComboBoxModel = new QStringListModel(this);
}

void ItemCodeDialog::setupModels()
{
    initializeModels();
    setupUnitsComboBoxModel();
}

void ItemCodeDialog::setupUnitsComboBoxModel()
{

}

ItemCodeDialog::~ItemCodeDialog()
{
    delete ui;
}
