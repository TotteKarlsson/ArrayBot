#pragma hdrstop
#include "abATDBServerSession.h"
#include "mtkLogger.h"
#include "Poco/Data/RecordSet.h"

//---------------------------------------------------------------------------
using namespace mtk;


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

RecordSet ATDBServerSession::getBlocks()
{
    if(!mTheSession)
    {
        Log(lError) << "No Session...";
        return RecordSet(NULL);
    }

    Statement select(*mTheSession);
    select << "SELECT * FROM block";

    int nrRows = select.execute();
    return RecordSet(select);
}

RecordSet* ATDBServerSession::getUsers()
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



