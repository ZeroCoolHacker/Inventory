#ifndef PURCHASEDIALOG_H
#define PURCHASEDIALOG_H

#include <QDialog>
#include <QSqlDatabase>

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
    Ui::PurchaseDialog *ui;
    QSqlDatabase *db;
};

#endif // PURCHASEDIALOG_H
