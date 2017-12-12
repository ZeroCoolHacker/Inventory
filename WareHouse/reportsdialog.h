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
    explicit ReportsDialog(qint8 type,QSqlDatabase* database, QWidget *parent = 0);

    void setDates();
    //model functions
    void setupModel();
    void setupDateWiseSalesModel();
    void setupDateWisePurchaseModel();

    ~ReportsDialog();

    enum ReportType {
        SALES_VENDORWISE,
        SALES_ITEMWISE,
        SALES_DATEWISE,
        PURCHASE_VENDORWISE,
        PURCHASE_ITEMWISE,
        PURCHASE_DATEWISE
    };
private slots:
    void on_generate_report_pushbutton_clicked();

private:
    Ui::ReportsDialog *ui;
    qint8 reportType;
    QSqlQueryModel* reportModel = new QSqlQueryModel(this);
    QSqlDatabase* db;


};

#endif // REPORTSDIALOG_H
