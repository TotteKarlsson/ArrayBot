#pragma hdrstop
#include "abATDBClientDBSession.h"
#include "mtkLogger.h"
#include "Poco/Data/SQLite/Connector.h"
#include "Poco/Data/SessionFactory.h"
#include "Poco/Data/SQLite/SQLiteException.h"
#include "mtkFileUtils.h"


//---------------------------------------------------------------------------
using namespace mtk;
using namespace ab;
using namespace Poco::Data;
using namespace Poco::Data::Keywords;

ATDBClientDBSession::ATDBClientDBSession(const string& dbFile)
:
mDBFileName(dbFile),
mTheSession(NULL)
{}

ATDBClientDBSession::~ATDBClientDBSession()
{}

bool ATDBClientDBSession::isConnected()
{
	return mTheSession ? true : false;
}

bool ATDBClientDBSession::connect(const string& dbName)
{
	try
    {
    	if(dbName.size())
        {
            mDBFileName = dbName;
        }

        if(!fileExists(mDBFileName))
        {
            return false;
        }

		//Register DB connector
	    SQLite::Connector::registerConnector();

    	//Create connection string
		//string str = "host=127.0.0.1;user=atdb_client;password=atdb123;db=atdb";

		mTheSession = new Poco::Data::Session(Poco::Data::SessionFactory::instance().create(Poco::Data::SQLite::Connector::KEY, mDBFileName ));
        Log(lInfo) << "Opened SQLite Database: "<<mDBFileName;

        //Enable foreign key support
        int support;
        Session& ses = *mTheSession;
	   	Statement s(ses);
    	s << "PRAGMA foreign_keys", into(support), now;

        s.reset(ses);
        Log(lInfo) <<"Foreign key support:" <<support;
        s << "PRAGMA foreign_keys = ON", now;
        s.reset(ses);

    	s << "PRAGMA foreign_keys", into(support), now;
        Log(lInfo) <<"Foreign key support:" <<support;
        return true;
    }
    catch(const Poco::Data::SQLite::SQLiteException& e)
    {
        Log(lError) << e.message() << endl;
        return false;
    }
}

bool ATDBClientDBSession::disConnect()
{
	try
    {
    	delete mTheSession;
        mTheSession = NULL;
	    SQLite::Connector::unregisterConnector();
        return true;
    }
    catch(...)
    {
    	Log(lError) << "Failed to delete db session..";
        return false;
    }
}

RecordSet* ATDBClientDBSession::getBlocks(dbSQLKeyword kw)
{
    if(!mTheSession)
    {
        Log(lError) << "No Session...";
        return NULL;
    }

    Statement select(*mTheSession);
    select << "SELECT * FROM block ORDER BY id " << mtk::toString(kw);

    int nrRows = select.execute();
    return new RecordSet(select);
}

RecordSet* ATDBClientDBSession::getNotesForBlockWithID(int blockID)
{
    if(!mTheSession)
    {
        Log(lError) << "No Session...";
        return NULL;
    }

    Session& ses = *mTheSession;

    //We need local variables for the statements..
    int id(blockID);

	Statement s(ses);
    s << "SELECT * FROM note WHERE id IN (SELECT note_id FROM block_note WHERE block_id = ?)", use(id), now;
    return new RecordSet(s);
}

bool ATDBClientDBSession::addNoteForBlockWithID(int blockID, int userID)
{
    if(!mTheSession)
    {
        Log(lError) << "No Session...";
        return NULL;
    }

    Session& ses = *mTheSession;

    //We need local variables for the statements..
    int bID(blockID);
    int uID(userID);
    string note("");

	Statement s(ses);
    s << "INSERT INTO note (created_by, note) VALUES(?, ?)", use(uID), use(note), now;
    s.reset(ses);

    int noteID;
    s << "SELECT MAX(id) FROM note", into(noteID), now;
    s.reset(ses);

    s << "INSERT INTO block_note (block_id, note_id) VALUES(?, ?)", use(bID), use(noteID), now;
	return true;
}

bool ATDBClientDBSession::deleteNoteWithID(int noteID)
{
    if(!mTheSession)
    {
        Log(lError) << "No Session...";
        return NULL;
    }

    Session& ses = *mTheSession;

    //We need local variables for the statements..
    int nID(noteID);

	Statement s(ses);
    s << "DELETE FROM note WHERE id = ?", use(nID), now;
	return true;
}

bool ATDBClientDBSession::updateNoteWithID(int noteID, const string& note)
{
    if(!mTheSession)
    {
        Log(lError) << "No Session...";
        return NULL;
    }

    Session& ses = *mTheSession;

    //We need local variables for the statements..
    int nID(noteID);
    string t(note);

	Statement s(ses);
    s << "UPDATE note SET note = ? WHERE id = ?", use(t), use(nID), now;
	return true;
}

bool ATDBClientDBSession::insertEnvironmentalData(int _id, double _t, double _h)
{
    if(!mTheSession)
    {
        Log(lError) << "No Session...";
        return NULL;
    }

    Session& ses = *mTheSession;

    //We need local variables for the statements..

    int id(_id);
    double t(_t), h(_h);

	Statement s(ses);
    s << "INSERT INTO environmental_data (device_id, temperature, humidity) VALUES(?,?,?)", use(id), use(t), use(h);
    s.execute();
    s.reset(ses);
	return true;
}

bool ATDBClientDBSession::insertImageFile(const string& fName, int userID, const string& note)
{
    if(!mTheSession)
    {
        Log(lError) << "No Session...";
        return NULL;
    }

    Session& ses = *mTheSession;

    //We need local variables for the statements..

    string f(fName), n(note);

	Statement s(ses);
    s << "INSERT INTO abImage (file_name) VALUES(?)", use(f), now;
    s.reset(ses);

    int image_id;
    s << "SELECT MAX(id) FROM abImage", into(image_id), now;
    s.reset(ses);

	return insertImageNote(image_id, userID, note);
}

bool ATDBClientDBSession::insertImageNote(int imageID, int userID, const string& note)
{
    if(!mTheSession)
    {
        Log(lError) << "No Session...";
        return NULL;
    }

    Session& ses = *mTheSession;
	Statement s(ses);

    //We need local variables for the statements..
	int id(imageID);

    string n(note);
    int user_id(userID);
    s << "INSERT INTO note (created_by, note) VALUES(?, ?)", use(user_id), use(n), now;
    s.reset(ses);

    int noteID;
    s << "SELECT MAX(id) FROM note", into(noteID), now;
    s.reset(ses);

    s << "INSERT INTO abImage_note (image_id, note_id) VALUES(?, ?)", use(id), use(noteID), now;
	return true;

}


bool ATDBClientDBSession::insertBlock(int userID, const string& lbl, const string& note)
{
    if(!mTheSession)
    {
        Log(lError) << "No Session...";
        return NULL;
    }

    Session& ses = *mTheSession;

    //We need local variables for the statements..
    int id(userID);
    string l(lbl), n(note);

	Statement s(ses);
    s << "INSERT INTO block (created_by, label) VALUES(?, ?)", use(id), use(l), now;
    s.reset(ses);

    int blockID;
    s << "SELECT MAX(id) FROM block", into(blockID), now;
    s.reset(ses);

    s << "INSERT INTO note (created_by, note) VALUES(?, ?)", use(id), use(n), now;
    s.reset(ses);

    int noteID;
    s << "SELECT MAX(id) FROM note", into(noteID), now;
    s.reset(ses);

    s << "INSERT INTO block_note (block_id, note_id) VALUES(?, ?)", use(blockID), use(noteID), now;
	return true;
}


bool ATDBClientDBSession::deleteBlock(int bId)
{
    Session& ses = *mTheSession;

    //We need local variables for the statements..
    int bid(bId);

	Statement s(ses);
    s << "DELETE FROM block WHERE id = ?", use(bId), now;

	return true;
}


RecordSet* ATDBClientDBSession::getUsers(dbSQLKeyword kw)
{
    if(!mTheSession)
    {
        Log(lError) << "No Session...";
        return NULL;
    }

    Statement select(*mTheSession);
    select << "SELECT * FROM user";
    int nrRows = select.execute();

    return new RecordSet(select);
}



