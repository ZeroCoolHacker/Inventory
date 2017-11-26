#ifndef ITEMCODEDIALOG_H
#define ITEMCODEDIALOG_H

#include <QDialog>
#include <QStringListModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQueryModel>
namespace Ui {
class ItemCodeDialog;
}

class ItemCodeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ItemCodeDialog(QSqlDatabase* database, QWidget *parent = 0);
    void initializeModels();
    void setupModels();
    void setupUnitsComboBoxModel();
    ~ItemCodeDialog();

private:
    Ui::ItemCodeDialog *ui;
    QSqlDatabase* db;
    QSqlQueryModel *unitsComboBoxModel;
};

#endif // ITEMCODEDIALOG_H
