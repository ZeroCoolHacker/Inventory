#ifndef VENDORCODEDIALOG_H
#define VENDORCODEDIALOG_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class VendorCodeDialog;
}

class VendorCodeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VendorCodeDialog(QSqlDatabase *database, QWidget *parent = 0);
    ~VendorCodeDialog();

private:
    Ui::VendorCodeDialog *ui;
    QSqlDatabase *db;
};

#endif // VENDORCODEDIALOG_H
