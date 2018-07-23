#ifndef atExceptionsH
#define atExceptionsH
#include "atCoreExporter.h"
#include "atATObject.h"
#include <exception>
#include <string>
#include <sstream>
//---------------------------------------------------------------------------
using std::string;
using std::stringstream;

namespace at
{
    class AT_CORE ATException : public std::exception, public ATObject
    {
        public:
                                                ATException(const string& desc);
                                                ATException(const stringstream& msg);
            virtual                             ~ATException() throw();
            virtual const char*                 what() const throw();
            string                              Message() const;

        protected:
                                                //ATException message
            string                              mMessage;
    };

    class AT_CORE FileSystemException : public ATException
    {
        public:
                                                FileSystemException(const string& desc) : ATException(desc){}
                                                FileSystemException(const stringstream& msg) : ATException(msg){}
    };

    class AT_CORE ATDataException : public ATException
    {
        public:
                                                ATDataException(const string& desc) : ATException(desc){}
                                                ATDataException(const stringstream& msg) : ATException(msg){}
    };


}
#endif
