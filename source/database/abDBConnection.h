#ifndef abDBConnectionH
#define abDBConnectionH
#include "abExporter.h"
#include "abABObject.h"
#include "abDBUtils.h"
#include <deque>
//#include "Poco/Data/RecordSet.h"
#include "Poco/Data/Session.h"
//---------------------------------------------------------------------------

//using Poco::Data::RecordSet;
using Poco::Data::Session;

//!The ATDB server session class encapsulate a database session
//!with the ATDB MySQL database
class AB_CORE DBConnection : public ABObject
{
    public:
					        	        DBConnection(const string& db, const string& host="127.0.0.1", const string& user="atdb_client", const string& password="atdb123");
					        	        ~DBConnection();

		bool							isConnected();
		bool							connect();
        bool							disConnect();

    protected:
        string					        mDataBase;
        string					        mHost;
        string 					        mDataBaseUser;
        string					        mDataBasePassword;
		Session*	        			mTheSession;
};

#endif
