#ifndef ITEMCODEDIALOG_H
#define ITEMCODEDIALOG_H

#include <QDialog>

namespace Ui {
class ItemCodeDialog;
}

class ItemCodeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ItemCodeDialog(QWidget *parent = 0);
    ~ItemCodeDialog();

private:
    Ui::ItemCodeDialog *ui;
};

#endif // ITEMCODEDIALOG_H
