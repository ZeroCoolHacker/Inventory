#ifndef VENDORCODEDIALOG_H
#define VENDORCODEDIALOG_H

#include <QDialog>

namespace Ui {
class VendorCodeDialog;
}

class VendorCodeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VendorCodeDialog(QWidget *parent = 0);
    ~VendorCodeDialog();

private:
    Ui::VendorCodeDialog *ui;
};

#endif // VENDORCODEDIALOG_H
