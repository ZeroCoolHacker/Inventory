#ifndef VENDORCODEDIALOG_H
#define VENDORCODEDIALOG_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QString>
#include <QDebug>
#include <QSqlError>

namespace Ui {
class VendorCodeDialog;
}

class VendorCodeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VendorCodeDialog(QSqlDatabase *database, QWidget *parent = 0);
    ~VendorCodeDialog();


private slots:
    void on_add_pushButton_clicked();

private:
    //helper
    //helper
    bool validateForm();
    bool addVendor();
    void resetForm();

private:
    Ui::VendorCodeDialog *ui;
    QSqlDatabase *db;
};

#endif // VENDORCODEDIALOG_H
