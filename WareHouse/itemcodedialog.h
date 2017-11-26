#ifndef ITEMCODEDIALOG_H
#define ITEMCODEDIALOG_H

#include <QDialog>
#include <QStringListModel>
#include <QSqlQuery>
#include <QSqlError>

namespace Ui {
class ItemCodeDialog;
}

class ItemCodeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ItemCodeDialog(QWidget *parent = 0);
    void initializeModels();
    void setupModels();
    void setupUnitsComboBoxModel();
    ~ItemCodeDialog();

private:
    Ui::ItemCodeDialog *ui;
    QStringListModel *unitsComboBoxModel;
};

#endif // ITEMCODEDIALOG_H
