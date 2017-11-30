#ifndef REPORTSDIALOG_H
#define REPORTSDIALOG_H

#include <QDialog>

namespace Ui {
class ReportsDialog;
}

class ReportsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReportsDialog(QWidget *parent = 0);
    ~ReportsDialog();

private:
    Ui::ReportsDialog *ui;
};

#endif // REPORTSDIALOG_H
