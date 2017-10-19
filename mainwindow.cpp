#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "encryptor.h"
#include "myexep.h"
#include <QDebug>
#include <iostream>
#include <fstream>
#include <string>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusBar->addPermanentWidget(ui->label_status,2);
    ui->statusBar->addPermanentWidget(ui->progressBar_status,1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Browse_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,"Select File","/","All files(*.*)"); //getting filename
    ui->lineEdit_filename->setText(filename);
    if(filename.contains(".xre"))
        ui->pushButton_EncryptDecrypt->setText("Decrypt");
    else
        ui->pushButton_EncryptDecrypt->setText("Encrypt");
}


void MainWindow::on_pushButton_EncryptDecrypt_clicked()
{
    if(ui->lineEdit_password->text()=="")
    {
        QMessageBox::warning(this,"ERROR","Enter Password First",QMessageBox::Ok);
    }
    else
    {
        if(ui->pushButton_EncryptDecrypt->text()=="Encrypt")
        {
            std::string fileName = (ui->lineEdit_filename->text()).toStdString();
            std::string key = (ui->lineEdit_password->text()).toStdString();
            std::ifstream iFile;
            std::ofstream oFile;
            std::string outFileName=fileName+".xre";
            int i=0;
            char temp;
            char *charptr=&temp;
            Encryptor Encrypt;
            filePosition fullFileSize=Encrypt.getFileSize(fileName);
            try
            {
                iFile.open(fileName,std::ios::binary|std::ios::in);
                oFile.open(outFileName,std::ios::binary|std::ios::out|std::ios::trunc);
                if(!(oFile.is_open()||iFile.is_open()))
                    throw excep;
                ui->label_status->setText("status: encrypting");
                while(iFile.read(charptr,1))
                {
                    temp=temp^key[(i++)%key.length()];
                    oFile.put(temp);
                    ui->progressBar_status->setValue(Encrypt.getProgress(iFile.tellg(),fullFileSize));
                }
                iFile.close();
                oFile.close();
            }
            catch(std::exception ex)
            {
                QMessageBox::warning(this,"ERROR",ex.what(),QMessageBox::Ok);
                QApplication::exit();
            }
            ui->label_status->setText("status: done");
            ui->lineEdit_password->setText("");
        }
        else
        {
            std::string fileName = (ui->lineEdit_filename->text()).toStdString();
            std::string key = (ui->lineEdit_password->text()).toStdString();
            std::ifstream iFile;
            std::ofstream oFile;
            std::string outFileName;
            outFileName=fileName.substr(0,fileName.length()-4);
            int i=0;
            char temp;
            char *charptr=&temp;
            Encryptor Encrypt;
            filePosition fullFileSize=Encrypt.getFileSize(fileName);
            try
            {
                iFile.open(fileName,std::ios::binary|std::ios::in);
                oFile.open(outFileName,std::ios::binary|std::ios::out|std::ios::trunc);
                if(!(oFile.is_open()||iFile.is_open()))
                    throw excep;
                ui->label_status->setText("status: decrypting");
                while(iFile.read(charptr,1))
                {
                    temp=temp^key[(i++)%key.length()];
                    oFile.put(temp);
                    ui->progressBar_status->setValue(Encrypt.getProgress(iFile.tellg(),fullFileSize));
                }
                iFile.close();
                oFile.close();
            }
            catch(std::exception ex)
            {
                QMessageBox::warning(this,"ERROR",ex.what(),QMessageBox::Ok);
                QApplication::exit(1);
            }
            ui->label_status->setText("status: done");
            ui->lineEdit_password->setText("");
        }
    }
}
