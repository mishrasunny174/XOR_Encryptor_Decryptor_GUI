#include "encryptor.h"
#include "mainwindow.h"
#include "myexep.h"

Encryptor::Encryptor()
{
    //empty constructor
}

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

void Encryptor::encrypt(std::string fileName,std::string key)
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
            if(!(oFile.is_open()||iFile.is_open()))
                throw excep;
            //cout<<"Encrypting File... Please wait!!!"<<endl;
            while(iFile.read(charptr,1))
            {
                temp=temp^key[(i++)%key.length()];
                oFile.put(temp);
                //showProgressBar(iFile.tellg(),fullFileSize);
            }
            iFile.close();
            oFile.close();
        }
        catch(std::exception ex)
        {
            //cout<<ex.what()<<endl; to be changed
            exit(1);
        }
        //cout<<"\nFile encrypted successfully!!!"<<endl;
}

void Encryptor::decrypt(std::string fileName,std::string key)
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
            if(!(oFile.is_open()||iFile.is_open()))
                throw excep;
            // cout<<"Decrypting File... Please wait!!!"<<endl; to be changed
            while(iFile.read(charptr,1))
            {
                temp=temp^key[(i++)%key.length()];
                oFile.put(temp);
                //showProgressBar(iFile.tellg(),fullFileSize); to be changed
            }
            iFile.close();
            oFile.close();
        }
        catch(std::exception ex)
        {
            //cout<<ex.what()<<endl; to be changed
            exit(1);
        }
        // cout<<"\nFile decrypted successfully!!!"<<endl; to be changed
}
