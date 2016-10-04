#ifndef abATDBClientDBSessionH
#define abATDBClientDBSessionH
#include "abExporter.h"
#include "abABObject.h"
#include "abDBUtils.h"
#include <deque>
#include "Poco/Data/RecordSet.h"
//---------------------------------------------------------------------------
using Poco::Data::RecordSet;
using Poco::Data::Session;

//!The ATDB server session class encapsulate a database session
//!with the ATDB MySQL database
class AB_CORE ATDBClientDBSession : public ABObject
{
    public:
					        	        ATDBClientDBSession(const string& dbFile);
					        	        ~ATDBClientDBSession();

		RecordSet* 						getUsers(ab::dbSQLKeyword kw = ab::dbAscending);

										//!Statements
		bool							insertImageFile(const string& fName, int userID, const string& note="");
		bool							insertImageNote(int imageID, int userID, const string& note="");

        bool							insertEnvironmentalData(int id, double t, double h);


		RecordSet* 						getBlocks(ab::dbSQLKeyword kw =ab::dbDescending);

        bool							insertBlock(int userID, const string& lbl, const string& note);
        bool							deleteBlock(int bId);
		RecordSet*        				getNotesForBlockWithID(int blockID);
		bool							addNoteForBlockWithID(int blockID, int userID);
		bool							deleteNoteWithID(int noteID);
		bool							updateNoteWithID(int noteID, const string& note);

		bool							isConnected();
		bool							connect(const string& dbName = "");
        bool							disConnect();

    protected:
        string					        mDBFileName;
		Session*	        			mTheSession;
};
#endif
