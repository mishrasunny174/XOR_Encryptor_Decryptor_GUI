#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "encryptor.h"
#include <QDebug>
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

void MainWindow::on_pushButton_Browse_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,"Select File","C:/","All files(*.*)"); //getting filename
    Encryptor encrypt;
    if(filename.contains(".xre"))
        ui->pushButton_EncryptDecrypt->setText("Decrypt");
    else
        ui->pushButton_EncryptDecrypt->setText("Encrypt");
}


void MainWindow::on_pushButton_EncryptDecrypt_clicked()
{

}
