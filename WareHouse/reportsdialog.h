#ifndef REPORTSDIALOG_H
#define REPORTSDIALOG_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDate>

namespace Ui {
class ReportsDialog;
}

class ReportsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReportsDialog(qint8 reportType, QSqlDatabase* database, QWidget *parent = 0);

    //model functions
    void setupModel();  //decides which model to display
    void setupSalesVendorWiseModel();
    ~ReportsDialog();


    enum ReportType {
        SALES_VENDORWISE,
        SALES_ITEMWISE,
        PURCHASES_DATEWISE,
        PURCHASES_VENDORWISE,
        PURCHASES_ITEMWISE
    };
private:
    Ui::ReportsDialog *ui;
    QSqlQueryModel* reportModel = new QSqlQueryModel(this);
    qint8 report_type;
    QSqlDatabase* db;
};

#endif // REPORTSDIALOG_H
