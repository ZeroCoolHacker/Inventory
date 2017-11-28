#ifndef SALESDIALOG_H
#define SALESDIALOG_H

#include <QDialog>

namespace Ui {
class SalesDialog;
}

class SalesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SalesDialog(QWidget *parent = 0);
    ~SalesDialog();

private:
    Ui::SalesDialog *ui;
};

#endif // SALESDIALOG_H
