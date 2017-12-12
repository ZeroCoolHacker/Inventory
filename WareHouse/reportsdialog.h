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
    explicit ReportsDialog(QSqlDatabase* database, QWidget *parent = 0);

    void setDates();
    //model functions
    void setupModel();
    ~ReportsDialog();


private:
    Ui::ReportsDialog *ui;
    QSqlQueryModel* reportModel = new QSqlQueryModel(this);
    QSqlDatabase* db;
};

#endif // REPORTSDIALOG_H
