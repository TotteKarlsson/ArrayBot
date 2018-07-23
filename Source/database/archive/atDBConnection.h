#ifndef atDBConnectionH
#define atDBConnectionH
#include "atDBExporter.h"
#include "atATObject.h"
#include "atDBUtils.h"
#include <deque>
#include "dslConstants.h"
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
using dsl::gEmptyString;

//!The ATDB server session class encapsulate a database session
//!with the ATDB MySQL database
class AT_DB DBConnection : public ATObject
{
    public:
					        	        DBConnection(const string& host = gEmptyString, const string& user = gEmptyString, const string& password = gEmptyString, const string& db = gEmptyString);
		virtual		        	        ~DBConnection();

		bool							isConnected();
		bool							connect(const string& host=gEmptyString, const string& user = gEmptyString, const string& password = gEmptyString, const string& db = gEmptyString);
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
