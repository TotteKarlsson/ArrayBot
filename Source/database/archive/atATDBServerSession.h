#ifndef atATDBServerSessionH
#define atATDBServerSessionH
#include "atDBExporter.h"
#include "atATObject.h"
#include "atDBUtils.h"
#include <deque>
#include "atDBConnection.h"
#include "dslStringList.h"
//---------------------------------------------------------------------------

namespace Poco
{
	namespace Data
    {
        class RecordSet;
        class Session;
    }
}
using namespace dsl;

//!The ATDB server session class encapsulate a database session
//!with the ATDB MySQL database
class AT_DB ATDBServerSession : public DBConnection
{
    public:
					        	        ATDBServerSession(const string& db, const string& host, const string& user, const string& password);
					        	        ~ATDBServerSession();

//		StringList						getTableNames();
//
//										//!Statements
//		Poco::Data::RecordSet* 	    	getBlocks(at::dbSQLKeyword kw = at::dbDescending);
//        bool							insertBlock(int userID, const string& lbl, const string& note);
//        bool							deleteBlock(int bId);
//        bool							deleteNotesForBlock(int bId);
//        bool							deleteRibbonsForBlock(int bId);
//
//		Poco::Data::RecordSet*      	getNotesForBlock(int blockID);
//		bool							addNoteForBlock(int blockID, int userID, const string& note);
//
//		bool							addNoteForRibbon(const string& ribbonID, int userID, const string& note);
//        bool							deleteNotesForRibbon(const string& bId);
//
//		bool							deleteNote(int noteID);
//		bool							updateNote(int noteID, const string& note);
//
//		Poco::Data::RecordSet* 	  		getUsers(at::dbSQLKeyword kw = at::dbAscending);
//
//										//Sensor data
//        bool							insertSensorData(int sensorID, double val1, double val2);


    protected:
};
#endif
