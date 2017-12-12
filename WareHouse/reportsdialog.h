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
    explicit ReportsDialog(ReportType reportType,QSqlDatabase* database, QWidget *parent = 0);

    void setDates();
    //model functions
    void setupModel();
    ~ReportsDialog();


private slots:
    void on_generate_report_pushbutton_clicked();

private:
    Ui::ReportsDialog *ui;
    ReportType reportType;
    QSqlQueryModel* reportModel = new QSqlQueryModel(this);
    QSqlDatabase* db;

    enum ReportType {
        SALES_VENDORWISE,
        SALES_ITEMWISE,
        PURCHASE_VENDORWISE,
        PURCHASE_ITEMWISE,
        PURCHASE_DATEWISE
    };
};

#endif // REPORTSDIALOG_H
