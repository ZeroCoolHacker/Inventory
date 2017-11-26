#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionItem_Code_triggered()
{
    ItemCodeDialog* itemCodeDialog = new ItemCodeDialog(this);
    itemCodeDialog->setAttribute(Qt::WA_DeleteOnClose);
    itemCodeDialog->setModal(true);
    itemCodeDialog->exec();
}
