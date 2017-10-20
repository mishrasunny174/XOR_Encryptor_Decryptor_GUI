#include "encryptor.h"

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

void Encryptor::encrypt(QProgressBar* progressBar,std::string fileName,std::string key)
{
    std::ifstream iFile;
    std::ofstream oFile;
    std::string outFileName=fileName+".xre";
    int i=0;
    char temp;
    char *charptr=&temp;
    filePosition fullFileSize=getFileSize(fileName);
    try
    {
        iFile.open(fileName,std::ios::binary|std::ios::in);
        oFile.open(outFileName,std::ios::binary|std::ios::out|std::ios::trunc);
        if(!iFile)
            throw excep;
        while(iFile.read(charptr,1))
        {
            temp=temp^key[(i++)%key.length()];
            oFile.put(temp);
            progressBar->setValue(getProgress(iFile.tellg(),fullFileSize));
        }
        iFile.close();
        oFile.close();
    }
    catch(std::exception* ex)
    {
        QMessageBox::warning(nullptr,"ERROR","Unable to open file make sure it exists!",QMessageBox::Ok);
        return;
    }
}

void Encryptor::decrypt(QProgressBar* progressBar,std::string fileName,std::string key)
{
    std::ifstream iFile;
    std::ofstream oFile;
    std::string outFileName;
    outFileName=fileName.substr(0,fileName.length()-4);
    int i=0;
    char temp;
    char *charptr=&temp;
    filePosition fullFileSize=getFileSize(fileName);
    try
    {
        iFile.open(fileName,std::ios::binary|std::ios::in);
        oFile.open(outFileName,std::ios::binary|std::ios::out|std::ios::trunc);
        if(!iFile)
            throw excep;
        while(iFile.read(charptr,1))
        {
            temp=temp^key[(i++)%key.length()];
            oFile.put(temp);
            progressBar->setValue(getProgress(iFile.tellg(),fullFileSize));
        }
        iFile.close();
        oFile.close();
    }
    catch(std::exception* ex)
    {
        QMessageBox::warning(nullptr,"ERROR","Unable to open file make sure it exists!",QMessageBox::Ok);
        return;
    }
}
