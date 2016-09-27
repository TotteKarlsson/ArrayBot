#ifndef abATDBServerSessionH
#define abATDBServerSessionH
//---------------------------------------------------------------------------
#include "abExporter.h"
#include "abABObject.h"
#include "Poco/Common.h"
#include "Poco/Data/MySQL/Connector.h"
#include <Poco/Data/MySQL/MySQLException.h>
#include <Poco/Data/SessionFactory.h>
#include "Poco/Data/RecordSet.h"

using namespace Poco::Data;
using std::vector;

//!The ATDB server session class encapsulate a database session
//!with the ATDB MySQL database

class AB_CORE ATDBServerSession : public ABObject
{
    public:
					        	        ATDBServerSession(const string& host="127.0.0.1", const string& user="atdb_client", const string& password="atdb123"){}
					        	        ~ATDBServerSession(){}

										//!Statements
		RecordSet 						getBlocks();
		RecordSet* 						getUsers();

		bool							isConnected();//{return mTheSession ? true : false;}
		bool							connect();
        bool							disConnect();

    protected:
        string					        mDataBaseName;
        string					        mHost;
        string 					        mDataBaseUser;
        string					        mDataBasePassword;
		Poco::Data::Session*	        mTheSession;

};
#endif
