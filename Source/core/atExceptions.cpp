#pragma hdrstop
#include "core/atExceptions.h"
//---------------------------------------------------------------------------

namespace at
{
    ATException::ATException(const string& desc)
    :
    mMessage(desc)
    {}

    ATException::ATException(const stringstream& msg)
    :
    mMessage(msg.str())
    {}

    ATException::~ATException() throw()
    {}


    const char* ATException::what() const throw()
    {
        return mMessage.c_str();
    }

    string ATException::Message() const
    {
        return mMessage;
    }

}
