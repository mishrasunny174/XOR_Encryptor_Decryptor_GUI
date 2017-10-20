#ifndef MYEXEP_H
#define MYEXEP_H
#include<exception>

class myExep:public std::exception
{
public:
    virtual const char* what()
    {
        return "unable to open file";
    }
};

#endif // MYEXEP_H
