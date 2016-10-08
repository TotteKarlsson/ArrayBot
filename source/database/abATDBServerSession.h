#ifndef abATDBServerSessionH
#define abATDBServerSessionH
#include "abExporter.h"
#include "abABObject.h"
#include "abDBUtils.h"
#include <deque>
#include "abDBConnection.h"
//---------------------------------------------------------------------------

namespace Poco
{
	namespace Data
    {
        class RecordSet;
        class Session;
    }
}


//using Poco::Data::RecordSet;
//using Poco::Data::Session;

//!The ATDB server session class encapsulate a database session
//!with the ATDB MySQL database
class AB_CORE ATDBServerSession : public DBConnection
{
    public:
					        	        ATDBServerSession(const string& db, const string& host="127.0.0.1", const string& user="atdb_client", const string& password="atdb123");
					        	        ~ATDBServerSession();

										//!Statements
		Poco::Data::RecordSet* 	    	getBlocks(ab::dbSQLKeyword kw = ab::dbDescending);
        bool							insertBlock(int userID, const string& lbl, const string& note);
        bool							deleteBlock(int bId);

		Poco::Data::RecordSet*      	getNotesForBlock(int blockID);
		bool							addNoteForBlock(int blockID, int userID, const string& note);

		bool							addNoteForRibbon(const string& ribbonID, int userID, const string& note);

		bool							deleteNote(int noteID);
		bool							updateNote(int noteID, const string& note);

		Poco::Data::RecordSet* 	  		getUsers(ab::dbSQLKeyword kw = ab::dbAscending);


    protected:
};
#endif
