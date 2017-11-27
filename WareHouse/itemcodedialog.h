#ifndef ITEMCODEDIALOG_H
#define ITEMCODEDIALOG_H

#include <QDialog>
#include <QStringListModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QString>

namespace Ui {
class ItemCodeDialog;
}

class ItemCodeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ItemCodeDialog(QSqlDatabase* database, QWidget *parent = 0);

    ~ItemCodeDialog();

private:
    //models
    void initializeModels();
    void setupModels();
    void setupUnitsComboBoxModel();


    //helper
    bool validateForm();
    bool addItem();
    void resetForm();
private slots:
    void on_add_pushButton_clicked();

private:
    Ui::ItemCodeDialog *ui;
    QSqlDatabase* db;
    QSqlQueryModel *unitsComboBoxModel;
};

#endif // ITEMCODEDIALOG_H
