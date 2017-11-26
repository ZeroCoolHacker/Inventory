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
    q.prepare("select id,unit from units");
    if(!q.exec()){
        QSqlError err = q.lastError();
        QMessageBox::critical(this,"Error",err.text());
    }
    unitsComboBoxModel->setQuery(q);
    ui->unit_comboBox->setModel(unitsComboBoxModel);
    ui->unit_comboBox->setModelColumn(1);
    ui->unit_comboBox->setCurrentIndex(0);
    qDebug() << "unit_comboBox model setup";
}

bool ItemCodeDialog::validateForm()
{
    if (ui->itemcode_spinBox->text().isEmpty()
            || ui->itemdescription_plainTextEdit->toPlainText().isEmpty()
            || ui->unit_comboBox->currentText().isEmpty())
        return false;
    return true;
}

bool ItemCodeDialog::addItem()
{
    //validate form
    if(!validateForm())
        QMessageBox::warning(this,"Fill Form", "Please Fill the form completely.");

    //gather arguments
    qint64  item_code    = ui->itemcode_spinBox->value();
    QString description  = ui->itemdescription_plainTextEdit->toPlainText();
    qint8   unit         = ui->unit_comboBox->currentIndex()+1; // id start from 1 but index from 0

    //prepare the query
    QSqlQuery q(*db);
    q.prepare("insert into items (item_code, item_description, unit) values "
              "(:item_code, :description, :unit);");
    q.bindValue(":item_code", item_code);
    q.bindValue(":description", description);
    q.bindValue(":unit", unit);

    //execute the query
    if(!q.exec()){
        QMessageBox::critical(this, "Error", q.lastError().text());
        return false;
    }
    return true;
}

ItemCodeDialog::~ItemCodeDialog()
{
    delete ui;
}

void ItemCodeDialog::on_add_pushButton_clicked()
{
    //confirms from the user
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,"Are You Sure?",
                                  "You can not undo the entry."
                                  "Do you want to continue?",
                                  QMessageBox::Yes | QMessageBox::Cancel);
    //if the user accepts the dialog
    if (reply == QMessageBox::Yes){
        if(addItem())
            QMessageBox::information(this, "Succesfull", "Item Addd Successfully!");
    }
}
