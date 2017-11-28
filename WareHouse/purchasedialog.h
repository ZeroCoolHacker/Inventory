#ifndef PURCHASEDIALOG_H
#define PURCHASEDIALOG_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QSqlError>
#include <QString>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QCompleter>

namespace Ui {
class PurchaseDialog;
}

class PurchaseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PurchaseDialog(QSqlDatabase *database,QWidget *parent = 0);
    ~PurchaseDialog();


private:
    void initializeModels();
    void setupModels();
    void setupVendorNameCompleter();

private slots:
    void on_itemcode_spinBox_editingFinished();

    void on_vendorname_lineEdit_editingFinished();

private:
    Ui::PurchaseDialog *ui;
    QSqlDatabase *db;

    QSqlQueryModel* vendor_name_model = new QSqlQueryModel(this);

    // query related
    QString vendor_code; // stores the vendor_code for the selected vendor
};

#endif // PURCHASEDIALOG_H
