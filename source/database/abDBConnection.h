#ifndef abDBConnectionH
#define abDBConnectionH
#include "abExporter.h"
#include "abABObject.h"
#include "abDBUtils.h"
#include <deque>
//#include "Poco/Data/RecordSet.h"
//#include "Poco/Data/Session.h"
//---------------------------------------------------------------------------

namespace Poco
{
	namespace Data
    {
        class Session;
        class RecordSet;
    }
}


using Poco::Data::RecordSet;
using Poco::Data::Session;

//!The ATDB server session class encapsulate a database session
//!with the ATDB MySQL database
class AB_CORE DBConnection : public ABObject
{
    public:
					        	        DBConnection(const string& host="127.0.0.1", const string& user="atdb_client", const string& password="atdb123", const string& db = "atdb");
		virtual		        	        ~DBConnection();

		bool							isConnected();
		bool							connect(const string& host="127.0.0.1", const string& user="atdb_client", const string& password="atdb123", const string& db = "atdb");
        bool							disConnect();

        								//ATDB specifics
		RecordSet*  					getNotesForBlockWithID(int blockID);

		bool							addNoteForBlockWithID(int blockID, int userID);
		bool							deleteNoteWithID(int noteID);
		bool							updateNoteWithID(int noteID, const string& note);

    protected:
        string					        mDataBase;
        string					        mHostIP;
        string 					        mDataBaseUser;
        string					        mDataBasePassword;
		Session*	        			mTheSession;
};

#endif
