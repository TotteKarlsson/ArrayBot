#pragma hdrstop
#include "abATDBServerSession.h"
#include "mtkLogger.h"
#include "Poco/Common.h"
#include "Poco/Data/MySQL/Connector.h"
#include "Poco/Data/MySQL/MySQLException.h"
#include "Poco/Data/SessionFactory.h"
#include "Poco/Data/Session.h"
#include "Poco/Data/RecordSet.h"
//---------------------------------------------------------------------------
using namespace mtk;

using namespace Poco::Data;
using namespace Poco::Data::Keywords;

string toString(dbKeyword kw)
{
	switch(kw)
    {
    	case dbKeyword::dbAscending: return "ASC";
    	case dbKeyword::dbDescending: return "DESC";
    }
    return "";
}

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

RecordSet* ATDBServerSession::getBlocks(dbKeyword kw)
{
    if(!mTheSession)
    {
        Log(lError) << "No Session...";
        return NULL;
    }

    Statement select(*mTheSession);
    select << "SELECT * FROM block ORDER BY id " << toString(kw);

    int nrRows = select.execute();
    return new RecordSet(select);
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

RecordSet* ATDBServerSession::getUsers(dbKeyword kw)
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



