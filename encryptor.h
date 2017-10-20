#ifndef ENCRYPTOR_H
#define ENCRYPTOR_H
#include <iostream>
#include <fstream>
#include <string>
#include "myexep.h"
#include <QProgressBar>
#include <QMessageBox>

typedef long long unsigned int filePosition;

class Encryptor
{
    int getProgress(filePosition ,filePosition); //it will display progress bar
    filePosition getFileSize(std::string); //to get the complete file size to calculate progress
    myExep* excep = new myExep; //exception if file doesn't opens
public:
    void encrypt(QProgressBar*,std::string,std::string);
    void decrypt(QProgressBar*,std::string,std::string);
};

#endif // ENCRYPTOR_H
