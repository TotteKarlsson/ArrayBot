#ifndef abATDBServerSessionH
#define abATDBServerSessionH
#include "abExporter.h"
#include "abABObject.h"
#include "abDBUtils.h"
#include <deque>
#include "abDBConnection.h"
//---------------------------------------------------------------------------

using Poco::Data::RecordSet;
using Poco::Data::Session;

//!The ATDB server session class encapsulate a database session
//!with the ATDB MySQL database
class AB_CORE ATDBServerSession : public DBConnection
{
    public:
					        	        ATDBServerSession(const string& db, const string& host="127.0.0.1", const string& user="atdb_client", const string& password="atdb123");
					        	        ~ATDBServerSession();

										//!Statements
		RecordSet* 						getBlocks(ab::dbSQLKeyword kw = ab::dbDescending);
        bool							insertBlock(int userID, const string& lbl, const string& note);
        bool							deleteBlock(int bId);
		RecordSet*        				getNotesForBlockWithID(int blockID);
		bool							addNoteForBlockWithID(int blockID, int userID);
		bool							deleteNoteWithID(int noteID);
		bool							updateNoteWithID(int noteID, const string& note);

		RecordSet* 						getUsers(ab::dbSQLKeyword kw = ab::dbAscending);

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
