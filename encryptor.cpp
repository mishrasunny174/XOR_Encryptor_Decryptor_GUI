#include "encryptor.h"
#include "mainwindow.h"

filePosition Encryptor::getFileSize(std::string fileName)
{
    std::ifstream file(fileName,std::ios::in|std::ios::ate|std::ios::binary);
    return file.tellg();
}

int Encryptor::getProgress(filePosition completed,filePosition total)
{
    float progress=static_cast<float>(completed)/total;
    return static_cast<int>(progress*100);
}
