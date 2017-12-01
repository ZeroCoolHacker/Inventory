#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include "itemcodedialog.h"
#include "vendorcodedialog.h"
#include "purchasedialog.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:
    void setupDatabase();

private slots:
    void on_actionItem_Code_triggered();

    void on_actionVendor_Code_triggered();

    void on_actionPurchase_triggered();

    void on_actionSale_Invoice_triggered();

    void on_actionVendor_Wise_triggered();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
};

#endif // MAINWINDOW_H
