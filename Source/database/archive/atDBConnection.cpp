#pragma hdrstop
#include "atATDBServerSession.h"
#include "Poco/Data/MySQL/Connector.h"
#include "Poco/Data/MySQL/MySQLException.h"
#include "Poco/Data/Session.h"
#include "Poco/Data/SessionFactory.h"
#include "Poco/Data/RecordSet.h"
#include "atDBUtils.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------
using namespace dsl;
using namespace at;

using namespace Poco::Data;
using namespace Poco::Data::Keywords;

DBConnection::DBConnection(const string& hostIP, const string& user, const string& password, const string& db)
:
mDataBase(db),
mHostIP(hostIP),
mDataBaseUser(user),
mDataBasePassword(password),
mTheSession(NULL)
{}

DBConnection::~DBConnection()
{}

bool DBConnection::isConnected()
{
	return mTheSession ? true : false;
}

bool DBConnection::connect(const string& ip, const string& user, const string& pwd, const string& db)
{
	try
    {
		//Register DB connector
	    MySQL::Connector::registerConnector();

		mDataBase 		    = db;
        mHostIP 		    = ip;
        mDataBaseUser 	    = user;
        mDataBasePassword 	= pwd;


    	//Create connection string
		//string str = "host=127.0.0.1;user=atdb_client;password=atdb123;db=atdb";
        stringstream c;
        c <<"host="<<mHostIP<<";"<<"user="<<mDataBaseUser<<";"<<"password="<<mDataBasePassword<<";"<<"db="<<mDataBase;
		mTheSession = new Poco::Data::Session(Poco::Data::SessionFactory::instance().create(Poco::Data::MySQL::Connector::KEY, c.str() ));
        Log(lInfo) << "Connected to "<<mHostIP;
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

bool DBConnection::disConnect()
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

RecordSet* DBConnection::getNotesForBlockWithID(int blockID)
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

bool DBConnection::addNoteForBlockWithID(int blockID, int userID)
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

bool DBConnection::deleteNoteWithID(int noteID)
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

bool DBConnection::updateNoteWithID(int noteID, const string& note)
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


