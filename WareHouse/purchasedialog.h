#ifndef PURCHASEDIALOG_H
#define PURCHASEDIALOG_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QString>
#include <QSqlQueryModel>
#include <QMessageBox>

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


private slots:
    void on_itemcode_spinBox_editingFinished();

private:
    Ui::PurchaseDialog *ui;
    QSqlDatabase *db;
};

#endif // PURCHASEDIALOG_H
