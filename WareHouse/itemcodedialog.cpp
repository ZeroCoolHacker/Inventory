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
    /// initializes all models

    unitsComboBoxModel = new QSqlQueryModel(this);
}

void ItemCodeDialog::setupModels()
{
    /// sets up all models

    initializeModels();
    setupUnitsComboBoxModel();
    qDebug() << "setupModels called";
}

void ItemCodeDialog::setupUnitsComboBoxModel()
{
    /// sets up the model for combo box

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
    /// validates the form fields and checks if they are empty

    if (ui->itemcode_spinBox->text().isEmpty()
            || ui->itemdescription_plainTextEdit->toPlainText().isEmpty()
            || ui->unit_comboBox->currentText().isEmpty() ||
            ui->stock_doubleSpinBox->text().isEmpty())
        return false;
    return true;
}

bool ItemCodeDialog::addItem()
{
    /// takes care of the query preperation and execution
    /// to add item to database items table

    //gather arguments
    qint64  item_code    = ui->itemcode_spinBox->value();
    QString description  = ui->itemdescription_plainTextEdit->toPlainText();
    qreal   stock        = ui->stock_doubleSpinBox->value();
    qint8   unit         = ui->unit_comboBox->currentIndex()+1; // id start from 1 but index from 0

    //prepare the query
    QSqlQuery q(*db);
    q.prepare("insert into items (item_code, item_description, quantity, unit) values "
              "(:item_code, :description, :quantity, :unit);");
    q.bindValue(":item_code", item_code);
    q.bindValue(":description", description);
    q.bindValue(":quantity", stock);
    q.bindValue(":unit", unit);

    //execute the query
    if(!q.exec()){
        QMessageBox::critical(this, "Error", q.lastError().text()
                              + "\n" + q.lastQuery());
        return false;
    }
    return true;
}

void ItemCodeDialog::resetForm()
{
    /// resets the form fields

    ui->itemcode_spinBox->clear();
    ui->itemdescription_plainTextEdit->clear();
    ui->stock_doubleSpinBox->clear();
    ui->itemcode_spinBox->setFocus();//focus on it
}

ItemCodeDialog::~ItemCodeDialog()
{
    delete ui;
}

void ItemCodeDialog::on_add_pushButton_clicked()
{
    //// Validates the form
    /// Adds the item to the database items table
    /// and resets the form
    //validate form
    if(!validateForm()){
        QMessageBox::warning(this,"Fill Form", "Please Fill the form completely.");
        return;
    }

    //confirms from the user
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,"Are You Sure?",
                                  "You can not undo the entry."
                                  "Do you want to continue?",
                                  QMessageBox::Yes | QMessageBox::Cancel);
    //if the user accepts the dialog
    if (reply == QMessageBox::Yes){
        if(addItem()){
            QMessageBox::information(this, "Succesfull", "Item Addd Successfully!");
            resetForm();
        }
    }
}
