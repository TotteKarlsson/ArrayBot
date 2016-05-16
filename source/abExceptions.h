#ifndef abExceptionsH
#define abExceptionsH
#include "abExporter.h"
#include "abABObject.h"
#include <exception>
#include <string>
#include <sstream>
//---------------------------------------------------------------------------
using std::string;
using std::stringstream;

class AB_CORE ABException : public std::exception, public ABObject
{
    public:
                                            ABException(const string& desc);
                                            ABException(const stringstream& msg);
        virtual                             ~ABException() throw();
        virtual const char*                 what() const throw();
        string                              Message() const;

    protected:
                                            //ABException message
        string                              mMessage;
};

#endif
