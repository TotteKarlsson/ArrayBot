#ifndef abATDBServerSessionH
#define abATDBServerSessionH
#include "abExporter.h"
#include "abABObject.h"
#include "Poco/Data/RecordSet.h"
//---------------------------------------------------------------------------

using namespace Poco::Data;
//using std::vector;

//namespace Poco{
//	namespace Data{
//        class RecordSet;
//        class Session;
//    }
//}

using Poco::Data::RecordSet;
//!The ATDB server session class encapsulate a database session
//!with the ATDB MySQL database

enum dbKeyword {dbAscending = 0, dbDescending};
string toString(dbKeyword kw);

class AB_CORE ATDBServerSession : public ABObject
{
    public:
					        	        ATDBServerSession(const string& host="127.0.0.1", const string& user="atdb_client", const string& password="atdb123"){}
					        	        ~ATDBServerSession(){}

										//!Statements
		RecordSet* 						getBlocks(dbKeyword kw = dbDescending);
        bool							insertBlock(int userID, const string& lbl, const string& note);
		RecordSet* 						getUsers(dbKeyword kw = dbAscending);

		bool							isConnected();//{return mTheSession ? true : false;}
		bool							connect();
        bool							disConnect();

    protected:
        string					        mDataBaseName;
        string					        mHost;
        string 					        mDataBaseUser;
        string					        mDataBasePassword;
		Session*	        			mTheSession;

};
#endif
