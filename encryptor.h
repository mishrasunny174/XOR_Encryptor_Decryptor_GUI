#ifndef ENCRYPTOR_H
#define ENCRYPTOR_H
#include <iostream>
#include <fstream>
#include <string>
#include "mainwindow.h"

typedef long long unsigned int filePosition;

class Encryptor
{
public:
    int getProgress(filePosition ,filePosition); //it will display progress bar
    filePosition getFileSize(std::string); //to get the complete file size to calculate progress
};

#endif // ENCRYPTOR_H
