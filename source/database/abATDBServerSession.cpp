#pragma hdrstop
#include "abATDBServerSession.h"
#include "Poco/Data/MySQL/Connector.h"
#include "Poco/Data/MySQL/MySQLException.h"
#include "Poco/Data/Session.h"
#include "Poco/Data/SessionFactory.h"
#include "abDBUtils.h"
#include "mtkLogger.h"
//---------------------------------------------------------------------------
using namespace mtk;
using namespace ab;

using namespace Poco::Data;
using namespace Poco::Data::Keywords;

ATDBServerSession::ATDBServerSession(const string& host, const string& user, const string& password)
:
mDataBaseName("atdb"),
mHost(host),
mDataBaseUser(user),
mDataBasePassword(password),
mTheSession(NULL)
{}

ATDBServerSession::~ATDBServerSession()
{}

bool ATDBServerSession::isConnected()
{
	return mTheSession ? true : false;
}

bool ATDBServerSession::connect()
{
	try
    {
		//Register DB connector
	    MySQL::Connector::registerConnector();

    	//Create connection string
		//string str = "host=127.0.0.1;user=atdb_client;password=atdb123;db=atdb";
        stringstream c;
        c <<"host="<<mHost<<";"<<"user="<<mDataBaseUser<<";"<<"password="<<mDataBasePassword<<";"<<"db="<<mDataBaseName;
		mTheSession = new Poco::Data::Session(Poco::Data::SessionFactory::instance().create(Poco::Data::MySQL::Connector::KEY, c.str() ));

        Log(lInfo) << "Connected to "<<mHost;
        return true;
    }
  	catch (const Poco::Data::MySQL::ConnectionException& e)
    {
        Log(lError) << e.message() <<endl;
        return false;
    }
    catch(const Poco::Data::MySQL::StatementException& e)
    {
        Log(lError) << e.message() << endl;
        return false;
    }
    catch(const Poco::Data::MySQL::MySQLException& e)
    {
        Log(lError) << e.message() << endl;
        return false;
    }
}

bool ATDBServerSession::disConnect()
{
	try
    {
    	delete mTheSession;
        mTheSession = NULL;
	    MySQL::Connector::unregisterConnector();
        return true;
    }
    catch(...)
    {
    	Log(lError) << "Failed to delete db session..";
        return false;
    }
}

RecordSet* ATDBServerSession::getBlocks(dbSQLKeyword kw)
{
    if(!mTheSession)
    {
        Log(lError) << "No Session...";
        return NULL;
    }

    Statement select(*mTheSession);
    select << "SELECT * FROM block ORDER BY id " << ab::toString((dbSQLKeyword) kw);

    int nrRows = select.execute();
    return new RecordSet(select);
}

RecordSet* ATDBServerSession::getNotesForBlockWithID(int blockID)
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

bool ATDBServerSession::addNoteForBlockWithID(int blockID, int userID)
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

bool ATDBServerSession::deleteNoteWithID(int noteID)
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

bool ATDBServerSession::updateNoteWithID(int noteID, const string& note)
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

bool ATDBServerSession::insertBlock(int userID, const string& lbl, const string& note)
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


bool ATDBServerSession::deleteBlock(int bId)
{
    Session& ses = *mTheSession;

    //We need local variables for the statements..
    int bid(bId);

	Statement s(ses);
    s << "DELETE FROM block WHERE id = ?", use(bId), now;

	return true;
}


RecordSet* ATDBServerSession::getUsers(dbSQLKeyword kw)
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



