#ifndef abATDBClientDBSessionH
#define abATDBClientDBSessionH
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
using Poco::Data::RecordSet;
using Poco::Data::Session;


//!The ATDB server session class encapsulate a database session
//!with the ATDB MySQL database
class AB_CORE ATDBClientDBSession : public DBConnection
{
    public:
					        	        ATDBClientDBSession(const string& db, const string& host="127.0.0.1", const string& user="atdb_client", const string& password="atdb123");
					        	        ~ATDBClientDBSession();

										//!Statements
		bool							insertImageFile(const string& fName, int userID, const string& note="");
		bool							insertImageNote(int imageID, int userID, const string& note="");

        bool							insertSensorData(int id, double t, double h);
		RecordSet* 	    				getBlocks(ab::dbSQLKeyword kw =ab::dbDescending);

        bool							insertBlock(int userID, const string& lbl, const string& note);
        bool							deleteBlock(int bId);

        								//Users
		RecordSet* 	   					getUsers(ab::dbSQLKeyword kw = ab::dbAscending);

        								//!Maintain user id from server
        bool							insertOrUpdateUser(int uid, const string& u);

    protected:
};
#endif
