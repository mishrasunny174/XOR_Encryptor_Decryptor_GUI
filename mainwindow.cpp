#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusBar->addPermanentWidget(ui->label_status,2);
    ui->statusBar->addPermanentWidget(ui->progressBar_status,1);
    ui->label_status->setText("Status: Select File");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Browse_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,"Select File","/","All files(*.*)"); //getting filename
    ui->lineEdit_filename->setText(filename);
    if(filename.contains(".crypted"))
        ui->pushButton_EncryptDecrypt->setText("Decrypt");
    else
        ui->pushButton_EncryptDecrypt->setText("Encrypt");
}


void MainWindow::on_pushButton_EncryptDecrypt_clicked()
{
    Encryptor Encrypt;
    std::string fileName = (ui->lineEdit_filename->text()).toStdString();
    std::string password = (ui->lineEdit_password->text()).toStdString();
    if(ui->lineEdit_password->text()=="")
        QMessageBox::warning(this,"WARNING","Please enter password.",QMessageBox::Ok);
    else
    {
        if(ui->pushButton_EncryptDecrypt->text()=="Encrypt")
        {
            ui->label_status->setText("Status: Encrypting");
            Encrypt.encrypt(ui->progressBar_status,fileName,password);
            ui->label_status->setText("Status: Done");
            ui->lineEdit_password->setText("");
        }
        else
        {
            ui->label_status->setText("Status: Decrypting");
            Encrypt.decrypt(ui->progressBar_status,fileName,password);
            ui->label_status->setText("Status: Done");
            ui->lineEdit_password->setText("");
        }
    }
}
