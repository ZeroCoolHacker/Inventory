#ifndef SALESDIALOG_H
#define SALESDIALOG_H

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
class SalesDialog;
}

class SalesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SalesDialog(QSqlDatabase *database,QWidget *parent = 0);
    ~SalesDialog();

private slots:
    void on_itemcode_spinBox_editingFinished();

    void on_quantity_doubleSpinBox_valueChanged(double arg1);

    void on_rateperunit_doubleSpinBox_valueChanged(double arg1);

    void on_sell_pushButton_clicked();

    void on_buyername_lineEdit_editingFinished();

private:
    void setupModels();
    void loadInvoiceNumber();

    // for submission
    bool validateForm();
    bool processSale();

private:
    Ui::SalesDialog *ui;
    QSqlDatabase *db;
    QString vendor_code;
};

#endif // SALESDIALOG_H
