#ifndef MYEXEP_H
#define MYEXEP_H
#include<exception>

class myExep:public std::exception
{
public:
    virtual const char* what()
    {
        return "File Error Has Occurred";
    }
}excep;

#endif // MYEXEP_H
