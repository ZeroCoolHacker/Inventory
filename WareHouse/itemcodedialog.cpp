#include "itemcodedialog.h"
#include "ui_itemcodedialog.h"
#include <QDebug>
ItemCodeDialog::ItemCodeDialog(QSqlDatabase *database, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ItemCodeDialog)
{
    ui->setupUi(this);
    db = database;

    //setup models
    setupModels();
}

void ItemCodeDialog::initializeModels()
{
    unitsComboBoxModel = new QSqlQueryModel(this);
}

void ItemCodeDialog::setupModels()
{
    initializeModels();
    setupUnitsComboBoxModel();
    qDebug() << "setupModels called";
}

void ItemCodeDialog::setupUnitsComboBoxModel()
{
    QSqlQuery q(*db);
    q.prepare("select unit from units");
    if(!q.exec()){
        QSqlError err = q.lastError();
        QMessageBox::critical(this,"Error",err.text());
    }
    unitsComboBoxModel->setQuery(q);
    ui->unit_comboBox->setModel(unitsComboBoxModel);
    ui->unit_comboBox->setCurrentIndex(0);
    qDebug() << "unit_comboBox model setup";
}

ItemCodeDialog::~ItemCodeDialog()
{
    delete ui;
}
