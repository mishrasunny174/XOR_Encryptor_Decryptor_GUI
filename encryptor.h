#ifndef ENCRYPTOR_H
#define ENCRYPTOR_H
#include <iostream>
#include <fstream>
#include <string>

typedef long long unsigned int filePosition;

class Encryptor
{
    int getProgress(filePosition ,filePosition); //it will display progress bar
    filePosition getFileSize(std::string); //to get the complete file size to calculate progress
public:
    Encryptor();
    void encrypt(std::string ,std::string);
    void decrypt(std::string ,std::string);
};

#endif // ENCRYPTOR_H
