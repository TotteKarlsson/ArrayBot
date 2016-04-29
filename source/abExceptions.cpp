#pragma hdrstop
#include "abExceptions.h"
//---------------------------------------------------------------------------
ABException::ABException(const string& desc)
:
mMessage(desc)
{}

ABException::ABException(const stringstream& msg)
:
mMessage(msg.str())
{}

ABException::~ABException() throw()
{}


const char* ABException::what() const throw()
{
    return mMessage.c_str();
}

string ABException::Message() const
{
    return mMessage;
}

