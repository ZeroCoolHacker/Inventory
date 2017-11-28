#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //setupDatabase
    setupDatabase();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupDatabase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    QString path = qApp->applicationDirPath()+"/records/data.db";
    QFile dbFile(path);
    if(!dbFile.exists()){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this,"Database","No database Exists."
                                              "Do you want to open your own database?",
                              QMessageBox::Yes | QMessageBox::No);
        if(reply==QMessageBox::Yes)
            path = QFileDialog::getOpenFileName(this,"Database",QDir::currentPath());
        else{
            qApp->closeAllWindows();
            qApp->exit(0);
        }
    }
    db.setDatabaseName(path);
    qDebug() << path;
    if(db.open())
        ui->status->setText("Database Connected");
    else
        ui->status->setText("Database not connected");
}

void MainWindow::on_actionItem_Code_triggered()
{
    ItemCodeDialog* itemCodeDialog = new ItemCodeDialog(&db, this);
    itemCodeDialog->setAttribute(Qt::WA_DeleteOnClose);
    itemCodeDialog->setModal(true);
    itemCodeDialog->exec();
}

void MainWindow::on_actionVendor_Code_triggered()
{
    VendorCodeDialog* vendorCodeDialog  =   new VendorCodeDialog(&db, this);
    vendorCodeDialog->setAttribute(Qt::WA_DeleteOnClose);
    vendorCodeDialog->setModal(true);
    vendorCodeDialog->exec();
}

void MainWindow::on_actionPurchase_triggered()
{
    PurchaseDialog* purchaseDialog  =   new PurchaseDialog(&db, this);
    purchaseDialog->setAttribute(Qt::WA_DeleteOnClose);
    purchaseDialog->setModal(true);
    purchaseDialog->exec();
}
